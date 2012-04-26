/**
 * @file main.c
 * @brief Projet Polytech Pacman sur Nintendo DS
 * @author Lendry CELERON & Nicolas JACQUES
 * @version 1.0
 * @date 23 avril 2012
 *
 * Pacman adapté sur plateforme Nintendo DS.
 *
 */
#include "procedures.h"

tabInfo tab[22][16];

// Grille mesGrilles;
int mesGrilles[22][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2},
	{2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2},
	{3, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 3},
	{2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2},
	{2, 2, 2, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2, 2, 2, 2},
	{1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1},
	{1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1},
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
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};



// /**
 // * Variable globale de type balleInfo (Structure)
 // *
 // * Tableau de structure utilisé pour les balles.
 // * Taille NBBALLES déclaré en #define
 // */
// balleInfo balle[NBBALLES];

// u8 balle_en_cours;



/**
 * Variable globale de type u8
 *
 * On définit des intervalles dans lesquels les sprites vont se créer.
 * La zone de 0 à 12 est réservée aux balles,
 * La zone de 12 à 30 est réservée aux murs en construction,
 * La zone de 30 à 128 est réservée aux murs fixes.
 */
u8 sprite_pacman = 0;
u8 sprite_ghost = 1;
u8 sprite_bonus = 6;
u8 sprite_mur = 31;

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
 * @fn void chargement_fond_ecran ()
 * @brief Fonction qui charge les fonds d'écran.
 */
void chargement_fond_ecran ()
{
/*
    PA_Init16bitBg(0, 3);
	PA_Load16bitBitmap(0, grilleJezzball_Bitmap);
	*/
}


/**
 * @fn void init_tab ()
 * @brief Fonction qui créé le tableau selon la structure déclarée.
 *
 * Cette fonction sert de constructeur, et aussi initialise les contours de la maquette.
 */
void init_tab ()
{
	
	 u8 i, j;

    for ( i = 0; i < 22; ++i )
        for ( j = 0; j < 16; ++j )
        {
            tab[i][j].value = 0;
            tab[i][j].numero_sprite = -1;
            tab[i][j].type_sprite = -1;
            tab[i][j].flag = 0;
        }
		
	PA_LoadDefaultText(1, // Top screen
	                   2); // Background #2

		
    for ( i = 0; i < 22; ++i )
        for ( j = 0; j < 16; ++j )
		{
            tab[i][j].value = mesGrilles[i][j];
			// PA_OutputText(1, j, i, "%d", tab[i][j].value); // affichage de la matrice
		}
		
	affichage_map();
            
	
}



/*  *********************************                     ********************************* */
/*                                       Partie JezzBall                                    */
/*  *********************************                     ********************************* */

/**
 * @fn void affichage_mur ()
 * @brief Fonction qui affiche les murs après chaque construction.
 *
 * On construit aussi bien les contours du plateau que les murs au fur et à mesure, que les zones grisées.
 *
 * Utilisation de la fonction PA_CreateSprite(u8 screen, u8 obj_number, void* obj_data, u8 obj_shape, u8 obj_size, u8 color_mode, u8 palette, s16 x, s16 y)
 */
void affichage_map ()
{
    u8 i;
    u8 j;
    u8 k;
    u8 l;

    // PA_OutputText(1,15,15,"%d ", tab[11][5].numero_sprite);
    for ( j = 0; j < 15; j+=2 )
	{
        for ( i = 0; i < 10; i++ )
        {
		
			if (tab[j][i].value == 0 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 00)
			{
				if (tab[j][i].numero_sprite = -1)
                    {
                        PA_CreateSprite(1, sprite_mur, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1,16*j,(16*i)+32);
                        tab[j][i].numero_sprite = sprite_mur;
                        tab[j+1][i].numero_sprite = sprite_mur;
						tab[j][i].value = 0;
						tab[j+1][i].value = 0;
						tab[j][i].type_sprite = 00;
                        sprite_mur++;
                    }
                    else if (tab[j][i].numero_sprite != -1)
						{
							PA_CreateSprite(1, tab[j][i].numero_sprite, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1,16*j,16*i);
						}
                    tab[j][i].value = 0;
                    tab[j+1][i].value = 0;
                    tab[j][i].type_sprite = 00;
			}
			else if (tab[j][i].value == 0 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 01){}
			else if (tab[j][i].value == 0 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 02){}
			else if (tab[j][i].value == 0 && tab[j+1][i].value == 3 && tab[j][i].type_sprite != 03){}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 10){}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 11){}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 12){}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 3 && tab[j][i].type_sprite != 13){}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 20){}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 21){}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 22){}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 3 && tab[j][i].type_sprite != 23){}
			else if (tab[j][i].value == 3 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 30){}
			else if (tab[j][i].value == 3 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 31){}
			else if (tab[j][i].value == 3 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 32){}

        }
		
		for (i = 10 ; i < 22 ; i++ )
		{
			if (tab[j][i].value == 0 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 00)
				{
					if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_00_Sprite, OBJ_SIZE_32X16, 1, 1,16*j,16*i);
							}
						tab[j][i].value = 0;
						tab[j+1][i].value = 0;
						tab[j][i].type_sprite = 00;
				}
			else if (tab[j][i].value == 0 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 01)
				{
					if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_01_Sprite, OBJ_SIZE_32X16, 1, 2,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_01_Sprite, OBJ_SIZE_32X16, 1, 2,16*j,16*i);
							}
						tab[j][i].value = 0;
						tab[j+1][i].value = 1;
						tab[j][i].type_sprite = 01;
				}
			else if (tab[j][i].value == 0 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 02)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_02_Sprite, OBJ_SIZE_32X16, 1, 3,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_02_Sprite, OBJ_SIZE_32X16, 1, 3,16*j,16*i);
							}
						tab[j][i].value = 0;
						tab[j+1][i].value = 2;
						tab[j][i].type_sprite = 02;
			}
			else if (tab[j][i].value == 0 && tab[j+1][i].value == 3 && tab[j][i].type_sprite != 03)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_03_Sprite, OBJ_SIZE_32X16, 1, 4,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_03_Sprite, OBJ_SIZE_32X16, 1, 4,16*j,16*i);
							}
						tab[j][i].value = 0;
						tab[j+1][i].value = 3;
						tab[j][i].type_sprite = 03;
			}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 10)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_10_Sprite, OBJ_SIZE_32X16, 1, 5,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_10_Sprite, OBJ_SIZE_32X16, 1, 5,16*j,16*i);
							}
						tab[j][i].value = 1;
						tab[j+1][i].value = 0;
						tab[j][i].type_sprite = 10;
			}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 11)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_11_Sprite, OBJ_SIZE_32X16, 1, 6,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_11_Sprite, OBJ_SIZE_32X16, 1, 6,16*j,16*i);
							}
						tab[j][i].value = 1;
						tab[j+1][i].value = 1;
						tab[j][i].type_sprite = 11;
			}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 12)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_12_Sprite, OBJ_SIZE_32X16, 1, 7,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_12_Sprite, OBJ_SIZE_32X16, 1, 7,16*j,16*i);
							}
						tab[j][i].value = 1;
						tab[j+1][i].value = 2;
						tab[j][i].type_sprite = 12;
			}
			else if (tab[j][i].value == 1 && tab[j+1][i].value == 3 && tab[j][i].type_sprite != 13)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_13_Sprite, OBJ_SIZE_32X16, 1, 8,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_13_Sprite, OBJ_SIZE_32X16, 1, 8,16*j,16*i);
							}
						tab[j][i].value = 1;
						tab[j+1][i].value = 3;
						tab[j][i].type_sprite = 13;
			}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 20)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_20_Sprite, OBJ_SIZE_32X16, 1, 9,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_20_Sprite, OBJ_SIZE_32X16, 1, 9,16*j,16*i);
							}
						tab[j][i].value = 2;
						tab[j+1][i].value = 0;
						tab[j][i].type_sprite = 20;
			}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 21)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_21_Sprite, OBJ_SIZE_32X16, 1, 10,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_21_Sprite, OBJ_SIZE_32X16, 1, 10,16*j,16*i);
							}
						tab[j][i].value = 2;
						tab[j+1][i].value = 1;
						tab[j][i].type_sprite = 21;
			}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 22)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_22_Sprite, OBJ_SIZE_32X16, 1, 11,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_22_Sprite, OBJ_SIZE_32X16, 1, 11,16*j,16*i);
							}
						tab[j][i].value = 2;
						tab[j+1][i].value = 2;
						tab[j][i].type_sprite = 22;
			}
			else if (tab[j][i].value == 2 && tab[j+1][i].value == 3 && tab[j][i].type_sprite != 23)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_23_Sprite, OBJ_SIZE_32X16, 1, 12,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_23_Sprite, OBJ_SIZE_32X16, 1, 12,16*j,16*i);
							}
						tab[j][i].value = 2;
						tab[j+1][i].value = 3;
						tab[j][i].type_sprite = 23;
			}
			else if (tab[j][i].value == 3 && tab[j+1][i].value == 0 && tab[j][i].type_sprite != 30)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_30_Sprite, OBJ_SIZE_32X16, 1, 13,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_30_Sprite, OBJ_SIZE_32X16, 1, 13,16*j,16*i);
							}
						tab[j][i].value = 3;
						tab[j+1][i].value = 0;
						tab[j][i].type_sprite = 30;
			}
			else if (tab[j][i].value == 3 && tab[j+1][i].value == 1 && tab[j][i].type_sprite != 31)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_31_Sprite, OBJ_SIZE_32X16, 1, 14,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_31_Sprite, OBJ_SIZE_32X16, 1, 14,16*j,16*i);
							}
						tab[j][i].value = 3;
						tab[j+1][i].value = 1;
						tab[j][i].type_sprite = 31;
			}
			else if (tab[j][i].value == 3 && tab[j+1][i].value == 2 && tab[j][i].type_sprite != 32)
			{
				if (tab[j][i].numero_sprite = -1)
						{
							PA_CreateSprite(0, sprite_mur, (void*)sprite_32_Sprite, OBJ_SIZE_32X16, 1, 15,16*j,16*i);
							tab[j][i].numero_sprite = sprite_mur;
							tab[j+1][i].numero_sprite = sprite_mur;
							sprite_mur++;
						}
						else if (tab[j][i].numero_sprite != -1)
							{
								PA_CreateSprite(0, tab[j][i].numero_sprite, (void*)sprite_32_Sprite, OBJ_SIZE_32X16, 1, 15,16*j,16*i);
							}
						tab[j][i].value = 3;
						tab[j+1][i].value = 2;
						tab[j][i].type_sprite = 32;
			}
		}
	}
		
		
		

    for ( l = 0; l < 30; l++ )
        {
            PA_DeleteSprite(0,l);
        }

    for ( k = 0; k < 16; k++ )
    {
        for ( l = 0; l < 12; l++ )
        {
            tab[k][l].flag = 0;
        }
    }
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

void deplacement_pacman()
{
	
	s32 x = 16*7;    s32 y = 16*16; // sprite position...
	
	/*!< Déplacement du pacman >*/
		PA_LoadDefaultText(0,0);
	
		PA_LoadSpritePal(0, // Screen
						0, // Palette number
						(void*)pacman_Pal);	// Palette name
		
		//Create the sprite
		PA_DualCreateSprite(0,(void*)pacman_Sprite, OBJ_SIZE_16X16,1, 0, 64-16, 64); // No need to choose the screen
		
		
		while(1){ // Main loop
			
			if (Pad.Held.Right) PA_SetSpriteAnim(0, 0, 0); // screen, sprite, frame	
			if (Pad.Held.Right) PA_SetSpriteAnim(1, 0, 0); // screen, sprite, frame
			if (Pad.Held.Up) PA_SetSpriteAnim(0, 0, 1); // screen, sprite, frame
			if (Pad.Held.Up) PA_SetSpriteAnim(1, 0, 1); // screen, sprite, frame
			if (Pad.Held.Down) PA_SetSpriteAnim(0, 0, 2); // screen, sprite, frame
			if (Pad.Held.Down) PA_SetSpriteAnim(1, 0, 2); // screen, sprite, frame
			if (Pad.Held.Left) PA_SetSpriteAnim(0, 0, 3); // screen, sprite, frame
			if (Pad.Held.Left) PA_SetSpriteAnim(1, 0, 3); // screen, sprite, frame
				
			
			// Update the position according to the keypad...
			x += Pad.Held.Right - Pad.Held.Left;
			y += Pad.Held.Down - Pad.Held.Up;
			
			// Set the sprite's position
			PA_DualSetSpriteXY(0, // sprite
							   x, // x position
							   y); // y...
						   
			PA_WaitForVBL();
		}
	
}


void jeu()
{
	
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

    // init_menu_principal ();

    // init_menu_jouer ();

    chargement_fond_ecran ();

    init_tab ();

    // affichage_mur ();
}