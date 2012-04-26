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

 #ifndef PROCEDURES_H_INCLUDED
#define PROCEDURES_H_INCLUDED

#include <PA9.h>
#include "all_gfx.h"


// typedef struct
// {
	// int difficulte;
	// int g[22][16];
// } Grille;



/**
 * @struct pacmanInfo
 * @brief Objet pacman
 *
 * La structure pacmanInfo nous servira à mettre à jour
 * les coordonnées et les vitesses de pacman.
 */
typedef struct{
	s16 x,y;        /*!< Coordonnées de position X & Y. */
	s16 vx, vy;     /*!< Vitesse de la pacman suivant les axes X & Y. */
	s16 numero_sprite;
}pacmanInfo;



/**
 * @struct tabInfo
 * @brief Objet Tableau
 *
 * La structure tabInfo nous servira à mettre à jour
 * le contenu des cases.
 */
typedef struct{
    s16 value;
    s16 numero_sprite;
    u8 type_sprite;
	s16 flag;
}tabInfo;




void initialisation ();

void init_PAlib ();

void init_start ();

void chargement_palettes ();

void init_menu_principal ();

// void init_menu_jouer ();

void init_tab ();



void jeu();

void affichage_map();

void pause();

void reboot();

void deplacement_pacman();


#endif // PROCEDURES_H_INCLUDED