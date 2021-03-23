#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "The_Galactic_War_functions.h"
#include "utils.h"


dll_galaxy_t *create_galaxy(void) {

	dll_galaxy_t *galaxy = malloc(sizeof(dll_galaxy_t));
	DIE(galaxy == NULL, "Memory error!\n");

	galaxy->head = NULL;
	galaxy->size = 0;

	return galaxy;
}

/*Implementata mai jos este comanda ADD, care
face verificarile de memorie necesare, apoi aloca
memorie pentru campurile pe care le necesita o planeta.
Pe urma, verifica daca trebuie introdus primul element din lista sau
un element de pe orice alta pozitie, apeland pentru fiecare
caz functia necesara.*/

void ADD(dll_galaxy_t * galaxy, char name[], unsigned int n, unsigned int num_shields) {

	DIE(galaxy == NULL, "memory error!\n");

	if (n > galaxy->size) {
		printf("Planet out of bounds!\n");
	}

	dll_planet_t *new_planet = malloc(sizeof(dll_planet_t));
	DIE(new_planet == NULL, "Memory error!\n");

	//???????????????????????????
	memcpy(new_planet->name, name, strlen(name) * sizeof(char));
	DIE(new_planet->name == NULL, "Memory error!\n");

	memcpy(new_planet->shield_size, num_shields, sizeof(unsigned int));
	DIE(new_planet->shield_size == NULL, "Memory error!\n");

	if (galaxy->size == 0) {

		/*introduce primul element din lista, creand
		bazele listei circulare dublu inlantuita*/
		add_first_planet(galaxy, new_planet);

	} else {

		//adauga un element pe pozitia "n" in lista
		add_nth_planet(galaxy, new_planet, n);
	}

	printf("The planet %s has joined the galaxy.\n", new_planet->name);
}

/*Cele doua functi de mai jos creaza lista dublu inlantuita
circulara introducand un nod nou (o planeta noua) pe pozitia dorita.*/

void add_nth_planet(dll_galaxy_t *galaxy, dll_planet_t *new_planet, unsigned int n) {
	dll_planet_t *curr;
	curr = galaxy->head;

	
}

void add_first_planet(dll_galaxy_t *galaxy, dll_planet_t *new_planet) {

	galaxy->head = new_planet;
	new_planet->next = new_planet;
	new_planet->prev = new_planet;
}


void BLH() {

}
void remove_planet() {

}

void UPG() {

}
void upgrade_shield() {

}
void EXP() {

}
void add_shield() {

}
void RMV() {

}
void remove_shield() {

}
void COL() {

}
void planet_collision() {

}

void ROT() {

}
void planet_rotation() {

}
void SHW() {

}
void planet_information() {

}