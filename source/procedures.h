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
	//rajouter un attribue pour gérer l'air du pacmen sur le sprite
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

void creation_pacman ();

void deplacement_pacman();

void maj_coord_pacman ();

void gestion_collision_murs ();


#endif // PROCEDURES_H_INCLUDED