/**
 * @file main.c
 * @brief Projet Polytech Pacman sur Nintendo DS
 * @author Landry SELLERON & Nicolas JACQUES
 * @version 1.0
 * @date 23 avril 2012
 *
 * Pacman adapté sur plateforme Nintendo DS.
 *
 */
#include "procedures.h"

#define rayon_pacman 8

tabInfo tab1[10][16];
tabInfo tab2[12][16];

// Grille mesGrilles;
int mesGrilles1[10][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2},
	{3, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 3},
	{2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2},
	{2, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 2, 2},
	{1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
	{1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1}
};
int mesGrilles2[12][16] = {
	{1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1},
	{0, 0, 0, 2, 0, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0},
	{1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1},
	{1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1},
	{1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2},
	{3, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 3},
	{1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1},
	{2, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 2, 2},
	{2, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};



/**
 * Variable globale de type pacman (Structure)
 *
 * Tableau de structure utilisé pour pacman.
 * Taille pacman déclaré en #define
 */
pacmanInfo pacman;



/**
 * Variable globale de type u8
 *
 * On définit des intervalles dans lesquels les sprites vont se créer.
 * La zone de 0 à 1 est réservée a Pacman,
 * La zone de 2 à 5 est réservée aux fantômes,
 * La zone de 6 à 30 est réservée aux bonnus,
 * La zone de 31 à 158 est réservée aux murs sur la map pour l'écran du haut,
 * La zone de 159 à 256 est réservée aux murs sur la map pour l'écran du bas.
 */
u8 sprite_pacman = 0;
u8 sprite_ghost = 1;
u8 sprite_bonus = 6;
u8 sprite_mur = 31;
u8 sprite_mur_bas = 159;

/*  *********************************                     ********************************* */
/*                                   Partie Initialisation                                  */
/*  *********************************                     ********************************* */

/**
 * @fn void init_PAlib ()
 * @brief Fonction d'initialisation, principalement pour les librairies PAlib.
 */
void init_PAlib ()
{
	PA_Init();
	PA_InitVBL();
	PA_VBLCounterStart(0);
	PA_InitRand();
}

/**
 * @fn void init_start ()
 * @brief Fonction qui affiche les 2 premiers fonds d'écran.
 *
 * Pour garder afficher à l'écran, on fait une boucle dans laquel on attend.
 * Ne pas oublier de les supprimer à la fin.
 */
void init_start ()
{
    u8 i;

    PA_Init16bitBg(0, 3);   /*!< Profondeur 1 */
	PA_Init16bitBg(1, 3);   /*!< Profondeur 1 */

	PA_Load16bitBitmap(1, demarrage_haut_Bitmap);
	PA_Load16bitBitmap(0, demarrage_bas_Bitmap);

    /*!< Boucle d'affichage de 150s */
	for (i = 0; i < 150; i++)
	{
        PA_WaitForVBL();
	}

    /*!< On delete les 2 fonds d'écran */
    PA_DeleteBg(1,3);
	PA_DeleteBg(0,3);
}

/**
 * @fn void chargement_palettes ()
 * @brief Fonction qui charge la palette des sprites des murs et des points.
 *
 *La fonction utilisée (PA_LoadSpritePal) prend en paramètre l'écran, le numéro de palette et le nom de palette.
 */
void chargement_palettes ()
{
	
	PA_DualLoadSpritePal(0, (void*)pacman_Pal);
	PA_DualLoadSpritePal(1, (void*)sprite_00_Pal);
	PA_DualLoadSpritePal(2, (void*)sprite_01_Pal);
	PA_DualLoadSpritePal(3, (void*)sprite_02_Pal);
	PA_DualLoadSpritePal(4, (void*)sprite_03_Pal);
	PA_DualLoadSpritePal(5, (void*)sprite_10_Pal);
	PA_DualLoadSpritePal(6, (void*)sprite_11_Pal);
	PA_DualLoadSpritePal(7, (void*)sprite_12_Pal);
	PA_DualLoadSpritePal(8, (void*)sprite_13_Pal);
	PA_DualLoadSpritePal(9, (void*)sprite_20_Pal);
	PA_DualLoadSpritePal(10, (void*)sprite_21_Pal);
	PA_DualLoadSpritePal(11, (void*)sprite_22_Pal);
	PA_DualLoadSpritePal(12, (void*)sprite_23_Pal);
	PA_DualLoadSpritePal(13, (void*)sprite_30_Pal);
	PA_DualLoadSpritePal(14, (void*)sprite_31_Pal);
	PA_DualLoadSpritePal(15, (void*)sprite_32_Pal);
	
}


/**
 * @fn void init_menu_principal ()
 * @brief Fonction qui créé le menu principal du jeu
 *
 * Cette fonction sert à afficher le menu principal.
 */
 void init_menu_principal ()
 {
    u8 i;
    //Petit jeu de lumière.
	PA_SetBrightness(0, -31);
	PA_SetBrightness(1, -31);

    for (i = 0; i < 40; i++)
	{
        PA_WaitForVBL();
	}
    PA_SetBrightness(0, 0);
	PA_SetBrightness(1, 0);

    u8 choix = 0;

    PA_Init16bitBg(0, 3);   /*!< Profondeur 3 */
	PA_Init16bitBg(1, 3);   /*!< Profondeur 3 */

	PA_Load16bitBitmap(0, jeux_bas_Bitmap);
	PA_Load16bitBitmap(1, jeux_haut_Bitmap);

    while (choix == 0)
    {
        if (Stylus.Released)
        {
            if ((Stylus.X > 50) && (Stylus.X < 200) && (Stylus.Y > 20) && (Stylus.Y < 60))// cas = 1;
            {
				//Petit jeu de lumière.
				PA_SetBrightness(0, -31);
				PA_SetBrightness(1, -31);

				for (i = 0; i < 40; i++)
				{
					PA_WaitForVBL();
				}
				PA_SetBrightness(0, 0);
				PA_SetBrightness(1, 0);
				
                choix = 10;
            }
            else if ((Stylus.X > 70) && (Stylus.X < 180) && (Stylus.Y > 80) && (Stylus.Y < 110))// cas = 2;
            {
                PA_Load16bitBitmap(1, controls_Bitmap);
            }
            else if ((Stylus.X > 90) && (Stylus.X < 165) && (Stylus.Y > 125) && (Stylus.Y < 160))// cas = 3;
            {
                PA_Load16bitBitmap(1, about_Bitmap);
            }
			else
			{
				PA_Load16bitBitmap(1, jeux_haut_Bitmap);
			}
        }
        PA_WaitForVBL();
    }
    /*!< On delete les 2 fonds d'écran */
	PA_DeleteBg(1,3);
	PA_DeleteBg(0,3);

 }


/**
 * @fn void init_tab ()
 * @brief Fonction qui créé le tableau selon la structure déclarée.
 *
 * Cette fonction sert de constructeur.
 */
void init_tab ()
{
	
	 u8 i, j;

    for ( i = 0; i < 10; ++i )
        for ( j = 0; j < 16; ++j )
        {
            tab1[i][j].value = 0;
            tab1[i][j].numero_sprite = -1;
            tab1[i][j].type_sprite = -1;
            tab1[i][j].flag = 0;
        }
		
	for ( i = 0; i < 12; ++i )
        for ( j = 0; j < 16; ++j )
        {
            tab2[i][j].value = 0;
            tab2[i][j].numero_sprite = -1;
            tab2[i][j].type_sprite = -1;
            tab2[i][j].flag = 0;
        }

	// affichage matrice
	PA_InitText( 1,1);

    for ( i = 0; i < 10; ++i )
        for ( j = 0; j < 16; ++j )
		{
            tab1[i][j].value = mesGrilles1[i][j];
			//PA_OutputText(1, j * 2, (i + 2) * 2, "%d", tab1[i][j].value); // affichage de la matrice
		}


	PA_InitText( 0,1);

    for ( i = 0; i < 12; ++i )
        for ( j = 0; j < 16; ++j )
		{
            tab2[i][j].value = mesGrilles2[i][j];
			//PA_OutputText(0, j * 2, (i + 0) * 2, "%d", tab2[i][j].value); // affichage de la matrice
		}
			
	// fin affichage matrice
	
	affichage_map();
            
	
}



/*  *********************************                     ********************************* */
/*                                       Partie Pacman                                      */
/*  *********************************                     ********************************* */

/**
 * @fn void affichage_map ()
 * @brief Fonction qui affiche les murs et points.
 *
 * On construit au fure et à mesure des mises à jours.
 *
 * Utilisation de la fonction PA_CreateSprite(u8 screen, u8 obj_number, void* obj_data, u8 obj_shape, u8 obj_size, u8 color_mode, u8 palette, s16 x, s16 y)
 */
void affichage_map ()
{

    u8 i;
    u8 j;
    // u8 k;
    // u8 l;

    for ( j = 0; j < 15; j+=2 )
	{
        for ( i = 0; i < 10; i++ )
        {
			if (tab1[i][j].value == 0 && tab1[i][j+1].value == 0 && tab1[i][j].type_sprite != 00)
				{
					if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 0;
						tab1[i][j+1].value = 0;
						tab1[i][j].type_sprite = 00;
				}
			else if (tab1[i][j].value == 0 && tab1[i][j+1].value == 1 && tab1[i][j].type_sprite != 01)
				{
					if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_01_Sprite, OBJ_SIZE_32X16, 1, 2, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_01_Sprite, OBJ_SIZE_32X16, 1, 2, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 0;
						tab1[i][j+1].value = 1;
						tab1[i][j].type_sprite = 01;
				}
			else if (tab1[i][j].value == 0 && tab1[i][j+1].value == 2 && tab1[i][j].type_sprite != 02)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_02_Sprite, OBJ_SIZE_32X16, 1, 3, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_02_Sprite, OBJ_SIZE_32X16, 1, 3, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 0;
						tab1[i][j+1].value = 2;
						tab1[i][j].type_sprite = 02;
			}
			else if (tab1[i][j].value == 0 && tab1[i][j+1].value == 3 && tab1[i][j].type_sprite != 03)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_03_Sprite, OBJ_SIZE_32X16, 1, 4, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_03_Sprite, OBJ_SIZE_32X16, 1, 4, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 0;
						tab1[i][j+1].value = 3;
						tab1[i][j].type_sprite = 03;
			}
			else if (tab1[i][j].value == 1 && tab1[i][j+1].value == 0 && tab1[i][j].type_sprite != 10)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_10_Sprite, OBJ_SIZE_32X16, 1, 5, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_10_Sprite, OBJ_SIZE_32X16, 1, 5, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 1;
						tab1[i][j+1].value = 0;
						tab1[i][j].type_sprite = 10;
			}
			else if (tab1[i][j].value == 1 && tab1[i][j+1].value == 1 && tab1[i][j].type_sprite != 11)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_11_Sprite, OBJ_SIZE_32X16, 1, 6, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_11_Sprite, OBJ_SIZE_32X16, 1, 6, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 1;
						tab1[i][j+1].value = 1;
						tab1[i][j].type_sprite = 11;
			}
			else if (tab1[i][j].value == 1 && tab1[i][j+1].value == 2 && tab1[i][j].type_sprite != 12)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_12_Sprite, OBJ_SIZE_32X16, 1, 7, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_12_Sprite, OBJ_SIZE_32X16, 1, 7, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 1;
						tab1[i][j+1].value = 2;
						tab1[i][j].type_sprite = 12;
			}
			else if (tab1[i][j].value == 1 && tab1[i][j+1].value == 3 && tab1[i][j].type_sprite != 13)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_13_Sprite, OBJ_SIZE_32X16, 1, 8, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_13_Sprite, OBJ_SIZE_32X16, 1, 8, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 1;
						tab1[i][j+1].value = 3;
						tab1[i][j].type_sprite = 13;
			}
			else if (tab1[i][j].value == 2 && tab1[i][j+1].value == 0 && tab1[i][j].type_sprite != 20)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_20_Sprite, OBJ_SIZE_32X16, 1, 9, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_20_Sprite, OBJ_SIZE_32X16, 1, 9, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 2;
						tab1[i][j+1].value = 0;
						tab1[i][j].type_sprite = 20;
			}
			else if (tab1[i][j].value == 2 && tab1[i][j+1].value == 1 && tab1[i][j].type_sprite != 21)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_21_Sprite, OBJ_SIZE_32X16, 1, 10, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_21_Sprite, OBJ_SIZE_32X16, 1, 10, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 2;
						tab1[i][j+1].value = 1;
						tab1[i][j].type_sprite = 21;
			}
			else if (tab1[i][j].value == 2 && tab1[i][j+1].value == 2 && tab1[i][j].type_sprite != 22)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_22_Sprite, OBJ_SIZE_32X16, 1, 11, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_22_Sprite, OBJ_SIZE_32X16, 1, 11, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 2;
						tab1[i][j+1].value = 2;
						tab1[i][j].type_sprite = 22;
			}
			else if (tab1[i][j].value == 2 && tab1[i][j+1].value == 3 && tab1[i][j].type_sprite != 23)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_23_Sprite, OBJ_SIZE_32X16, 1, 12, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_23_Sprite, OBJ_SIZE_32X16, 1, 12, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 2;
						tab1[i][j+1].value = 3;
						tab1[i][j].type_sprite = 23;
			}
			else if (tab1[i][j].value == 3 && tab1[i][j+1].value == 0 && tab1[i][j].type_sprite != 30)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_30_Sprite, OBJ_SIZE_32X16, 1, 13, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_30_Sprite, OBJ_SIZE_32X16, 1, 13, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 3;
						tab1[i][j+1].value = 0;
						tab1[i][j].type_sprite = 30;
			}
			else if (tab1[i][j].value == 3 && tab1[i][j+1].value == 1 && tab1[i][j].type_sprite != 31)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_31_Sprite, OBJ_SIZE_32X16, 1, 14, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_31_Sprite, OBJ_SIZE_32X16, 1, 14, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 3;
						tab1[i][j+1].value = 1;
						tab1[i][j].type_sprite = 31;
			}
			else if (tab1[i][j].value == 3 && tab1[i][j+1].value == 2 && tab1[i][j].type_sprite != 32)
			{
				if (tab1[i][j].numero_sprite = -1)
						{
							PA_CreateSprite(1, sprite_mur, (void*)sprite_32_Sprite, OBJ_SIZE_32X16, 1, 15, 16 * j, (16 * i) + 32);
							tab1[i][j].numero_sprite = sprite_mur;
							tab1[i][j+1].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab1[i][j].numero_sprite != -1)
							{
								PA_CreateSprite(1, tab1[i][j].numero_sprite, (void*)sprite_32_Sprite, OBJ_SIZE_32X16, 1, 15, 16 * j, (16 * i) + 32);
							}
						tab1[i][j].value = 3;
						tab1[i][j+1].value = 2;
						tab1[i][j].type_sprite = 32;
			}

        }
	}
		
		
		/* Pour écran du bas */
		
	/*for ( j = 0; j < 15; j+=2 )
	{
		for (i = 0 ; i < 12 ; i++ )
		{
			if (tab2[i][j].value == 0 && tab2[i][j+1].value == 0 && tab2[i][j].type_sprite != 00)
				{
					if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite( tab2[i][j].numero_sprite, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 0;
						tab2[i][j+1].value = 0;
						tab2[i][j].type_sprite = 00;
				}
			else if (tab2[i][j].value == 0 && tab2[i][j+1].value == 1 && tab2[i][j].type_sprite != 01)
				{
					if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_01_Sprite, OBJ_SIZE_32X16, 1, 2, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_01_Sprite, OBJ_SIZE_32X16, 1, 2, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 0;
						tab2[i][j+1].value = 1;
						tab2[i][j].type_sprite = 01;
				}
			else if (tab2[i][j].value == 0 && tab2[i][j+1].value == 2 && tab2[i][j].type_sprite != 02)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_02_Sprite, OBJ_SIZE_32X16, 1, 3, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_02_Sprite, OBJ_SIZE_32X16, 1, 3, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 0;
						tab2[i][j+1].value = 2;
						tab2[i][j].type_sprite = 02;
			}
			else if (tab2[i][j].value == 0 && tab2[i][j+1].value == 3 && tab2[i][j].type_sprite != 03)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_03_Sprite, OBJ_SIZE_32X16, 1, 4, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_03_Sprite, OBJ_SIZE_32X16, 1, 4, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 0;
						tab2[i][j+1].value = 3;
						tab2[i][j].type_sprite = 03;
			}
			else if (tab2[i][j].value == 1 && tab2[i][j+1].value == 0 && tab2[i][j].type_sprite != 10)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_10_Sprite, OBJ_SIZE_32X16, 1, 5, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_10_Sprite, OBJ_SIZE_32X16, 1, 5, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 1;
						tab2[i][j+1].value = 0;
						tab2[i][j].type_sprite = 10;
			}
			else if (tab2[i][j].value == 1 && tab2[i][j+1].value == 1 && tab2[i][j].type_sprite != 11)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_11_Sprite, OBJ_SIZE_32X16, 1, 6, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_11_Sprite, OBJ_SIZE_32X16, 1, 6, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 1;
						tab2[i][j+1].value = 1;
						tab2[i][j].type_sprite = 11;
			}
			else if (tab2[i][j].value == 1 && tab2[i][j+1].value == 2 && tab2[i][j].type_sprite != 12)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_12_Sprite, OBJ_SIZE_32X16, 1, 7, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_12_Sprite, OBJ_SIZE_32X16, 1, 7, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 1;
						tab2[i][j+1].value = 2;
						tab2[i][j].type_sprite = 12;
			}
			else if (tab2[i][j].value == 1 && tab2[i][j+1].value == 3 && tab2[i][j].type_sprite != 13)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_13_Sprite, OBJ_SIZE_32X16, 1, 8, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_13_Sprite, OBJ_SIZE_32X16, 1, 8, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 1;
						tab2[i][j+1].value = 3;
						tab2[i][j].type_sprite = 13;
			}
			else if (tab2[i][j].value == 2 && tab2[i][j+1].value == 0 && tab2[i][j].type_sprite != 20)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_20_Sprite, OBJ_SIZE_32X16, 1, 9, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_20_Sprite, OBJ_SIZE_32X16, 1, 9, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 2;
						tab2[i][j+1].value = 0;
						tab2[i][j].type_sprite = 20;
			}
			else if (tab2[i][j].value == 2 && tab2[i][j+1].value == 1 && tab2[i][j].type_sprite != 21)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_21_Sprite, OBJ_SIZE_32X16, 1, 10, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_21_Sprite, OBJ_SIZE_32X16, 1, 10, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 2;
						tab2[i][j+1].value = 1;
						tab2[i][j].type_sprite = 21;
			}
			else if (tab2[i][j].value == 2 && tab2[i][j+1].value == 2 && tab2[i][j].type_sprite != 22)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_22_Sprite, OBJ_SIZE_32X16, 1, 11, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_22_Sprite, OBJ_SIZE_32X16, 1, 11, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 2;
						tab2[i][j+1].value = 2;
						tab2[i][j].type_sprite = 22;
			}
			else if (tab2[i][j].value == 2 && tab2[i][j+1].value == 3 && tab2[i][j].type_sprite != 23)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_23_Sprite, OBJ_SIZE_32X16, 1, 12, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_23_Sprite, OBJ_SIZE_32X16, 1, 12, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 2;
						tab2[i][j+1].value = 3;
						tab2[i][j].type_sprite = 23;
			}
			else if (tab2[i][j].value == 3 && tab2[i][j+1].value == 0 && tab2[i][j].type_sprite != 30)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_30_Sprite, OBJ_SIZE_32X16, 1, 13, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_30_Sprite, OBJ_SIZE_32X16, 1, 13, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 3;
						tab2[i][j+1].value = 0;
						tab2[i][j].type_sprite = 30;
			}
			else if (tab2[i][j].value == 3 && tab2[i][j+1].value == 1 && tab2[i][j].type_sprite != 31)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_31_Sprite, OBJ_SIZE_32X16, 1, 14, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_31_Sprite, OBJ_SIZE_32X16, 1, 14, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 3;
						tab2[i][j+1].value = 1;
						tab2[i][j].type_sprite = 31;
			}
			else if (tab2[i][j].value == 3 && tab2[i][j+1].value == 2 && tab2[i][j].type_sprite != 32)
			{
				if (tab2[i][j].numero_sprite = -1)
						{
							PA_DualCreateSprite(sprite_mur_bas, (void*)sprite_32_Sprite, OBJ_SIZE_32X16, 1, 15, 16 * j, (16 * i) + (240));
							tab2[i][j].numero_sprite = sprite_mur_bas;
							tab2[i][j+1].numero_sprite = sprite_mur_bas;
							sprite_mur_bas++;
						}
						else if (tab2[i][j].numero_sprite != -1)
							{
								PA_DualCreateSprite(tab2[i][j].numero_sprite, (void*)sprite_32_Sprite, OBJ_SIZE_32X16, 1, 15, 16 * j, (16 * i) + (240));
							}
						tab2[i][j].value = 3;
						tab2[i][j+1].value = 2;
						tab2[i][j].type_sprite = 32;
			}
		}
	}*/
		
		
		

    // for ( l = 0; l < 30; l++ )
        // {
            // PA_DeleteSprite(0,l);
        // }

    // for ( k = 0; k < 16; k++ )
    // {
        // for ( l = 0; l < 12; l++ )
        // {
            // tab1[k][l].flag = 0;
        // }
    // }
}



void pause ()
{
	bool fin = false;

	while(fin==false)// attend la pression du bouton start
	{
		PA_WaitForVBL();
		if(Pad.Newpress.Start) 
			fin=true;
	}
}

void reboot ()
{
	u8 i;

	for ( i=0; i < 128; i++)
	{
	    PA_DeleteSprite(1, i);
	    PA_DeleteSprite(0, i);
	}

    initialisation();
}


/**
 * @fn void creation_pacman ()
 * @brief Fonction de création de pacman.
 */
void creation_pacman ()
{

		/*!< On met des coordonnées dans la structure pacman. */
        pacman.x = 120;
		pacman.y = 176;


		/*!< On donne une vitesse de départ à chaque pacman. */
		do
		{
            pacman.vx = 0;
            pacman.vy = 0;
		} while (pacman.vx != 0 && pacman.vy != 0);

		/*!< On sauvegarde le numéro de sprite attribué. */
		pacman.numero_sprite = sprite_pacman;

		/*!< Création du sprite. */
		PA_DualCreateSprite(sprite_pacman,(void*)pacman_Sprite, OBJ_SIZE_16X16,1, 0, pacman.x, pacman.y); // Pas besoin de choisir l'écran

}


/**
 * @fn void maj_coord_pacman ()
 * @brief Fonction qui met à jour les coordonnées de la pacman suivant sa vitesse.
 *
 * La mise à jour des nouvelles coordonnées de position se fait en aditionnant la position actuelle et la vitesse suivant les axes.
 */
void maj_coord_pacman ()
{
	pacman.x += (pacman.vx);
    pacman.y += (pacman.vy);

	//PA_OutputText(1,1,1,"%d  ", pacman.x);
    //PA_OutputText(1,5,1,"%d  ", pacman.y);
}


/**
 * @fn void gestion_collision_murs ()
 * @brief Fonction qui gère la collision entre pacman et un mur.
 *
 * COLLISION AXE DES ABCISSES
 * Si la coordonnée en x de pacman i est inférieure ou égale à 7 (on prend en compte la taille de la bordure) et si sa vitesse en x
 * est inférieure à 0 (c'est à dire que pacman se déplace vers la gauche) alors on inverse siplement sa vitesse en x.
 * Idem pour l'autre côté, en tenant compte de la bordure et en vérifiant que la vitesse en x est positive.
 *
 * COLLISION AXE DES ORDONNEES
 * Même raisonnement.
 */
void gestion_collision_murs ()
{
    // int coef = 0;

    // /*!< On cherche l'orientation suivant l'axe des X */
    // if (pacman.vx > 0)
    // {
        // coef = rayon_pacman;
    // }
    // else if (pacman.vx < 0)
    // {
        // coef = -rayon_pacman;
    // }

    // int test_x = (pacman.x + pacman.vx + coef) / 16;


    // /*!< On cherche l'orientation suivant l'axe des Y */
    // if (pacman.vy > 0)
    // {
        // coef = rayon_pacman;
    // }
    // else if (pacman.vy < 0)
    // {
        // coef = -rayon_pacman;
    // }

    // int test_y = (pacman.y + pacman.vy + coef) / 16;

	// PA_OutputText(1,1,2,"%d  ", test_x);
    // PA_OutputText(1,5,2,"%d  ", test_y);
	// PA_OutputText(1,10,2,"val : %d  ", tab1[test_x][test_y].value);

    // /*!< Traitement EN COURS */
	
    // if (tab1[test_y][test_x].value == 1 || tab2[test_y][test_x].value == 1)
    // {
       // pacman.vx = 0;
	   // pacman.vy = 0;
    // }
	
}


void deplacement_pacman()
{	

	if (Pad.Held.A)
	{
		pacman.vx = 0;
		pacman.vy = 0;
	}
	else if (Pad.Held.B)
	{
		pacman.vx = 0;
		pacman.vy = 0;
		pacman.x = 120;
		pacman.y = 176;
	}
	else if (Pad.Held.Right)
	{
		PA_SetSpriteAnim(0, 0, 0); // screen, sprite, frame
		PA_SetSpriteAnim(1, 0, 0); 

		if (pacman.vx == 0 && pacman.vy == 0)
		{
			pacman.vx = 1.5;
		}
		else if (pacman.vx < 0)
		{
			pacman.vx = -pacman.vx;
			pacman.vy = 0;
		}
		else if (pacman.vx > 0) {}
		else if (pacman.vy > 0)
		{
			pacman.vx = pacman.vy;
			pacman.vy = 0;
		}
		else if (pacman.vy < 0)
		{
			pacman.vx = -pacman.vy;
			pacman.vy = 0;
		}
	}
	else if (Pad.Held.Left)
	{
		PA_SetSpriteAnim(0, 0, 3);
		PA_SetSpriteAnim(1, 0, 3);

		if (pacman.vx == 0 && pacman.vy == 0)
		{
			pacman.vx = -1.5;
		}
		else if (pacman.vx < 0) {}
		else if (pacman.vx > 0)
		{
			pacman.vx = -pacman.vx;
			pacman.vy = 0;
		}
		else if (pacman.vy > 0)
		{
			pacman.vx = pacman.vy;
			pacman.vy = 0;
		}
		else if (pacman.vy < 0)
		{
			pacman.vx = -pacman.vy;
			pacman.vy = 0;
		}
	}
	else if (Pad.Held.Up)
	{
		PA_SetSpriteAnim(0, 0, 1); 
		PA_SetSpriteAnim(1, 0, 1);

		if (pacman.vx == 0 && pacman.vy == 0)
		{
			pacman.vy = 1.5;
		}
		else if (pacman.vx < 0)
		{
			pacman.vy = -pacman.vx;
			pacman.vx = 0;
		}
		else if (pacman.vx > 0)
		{
			pacman.vy = -pacman.vx;
			pacman.vx = 0;
		}
		else if (pacman.vy > 0)
		{
			pacman.vy = -pacman.vy;
			pacman.vx = 0;
		}
		else if (pacman.vy < 0) {}

	}
	else if (Pad.Held.Down)
	{
		PA_SetSpriteAnim(0, 0, 2);
		PA_SetSpriteAnim(1, 0, 2);

		if (pacman.vx == 0 && pacman.vy == 0)
		{
			pacman.vy = -1.5;
		}
		else if (pacman.vx < 0)
		{
			pacman.vy = -pacman.vx;
			pacman.vx = 0;
		}
		else if (pacman.vx > 0)
		{
			pacman.vy = -pacman.vx;
			pacman.vx = 0;
		}
		else if (pacman.vy > 0) {}
		else if (pacman.vy < 0)
		{
			pacman.vy = -pacman.vy;
			pacman.vx = 0;
		}
	}


	maj_coord_pacman ();

	gestion_collision_murs ();

	// Set the sprite's position
	PA_DualSetSpriteXY(sprite_pacman, pacman.x, pacman.y);

}



void jeu()
{
	
	creation_pacman ();
	
	PA_Init16bitBg(1, 3);   /*!< Profondeur 1 */

	PA_Load16bitBitmap(1, Entete_Bitmap);
	
	/*!< Boucle infinie pour le déroulement du jeu >*/
	while(1)
	{
	    if(Pad.Newpress.Start) pause();

	    if(Pad.Newpress.Select) reboot();
		
		deplacement_pacman();

        PA_WaitForVBL();
	}

}


/**
 * @fn void initialisation ()
 * @brief Fonction qui initialise le jeu, aussi bien les librairies que l'affichage initial.
 */
void initialisation ()
{
    init_PAlib ();

    init_start ();

    chargement_palettes ();

    init_menu_principal ();

    // init_menu_jouer ();

    init_tab ();
}