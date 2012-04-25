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

 #ifndef PROCEDURES_H_INCLUDED
#define PROCEDURES_H_INCLUDED

#include <PA9.h>
#include "all_gfx.h"

void initialisation ();

void init_PAlib ();

void init_start ();

void chargement_palettes ();

// void init_menu_principal ();

// void init_menu_jouer ();

void chargement_fond_ecran ();

void init_tab ();

// void affichage_mur ();



void jeu();

void pause();

void reboot();


#endif // PROCEDURES_H_INCLUDED