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

}



/*  *********************************                     ********************************* */
/*                                       Partie JezzBall                                    */
/*  *********************************                     ********************************* */





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