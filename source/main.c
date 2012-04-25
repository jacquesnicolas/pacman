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

/**
 * @fn int main( void )
 * @brief Entrée principale du programme.
 *
 * @return 0 si arrêt normal du programme
 */

int main( void )
{

	initialisation();
	
	jeu();

	return 0;
}
