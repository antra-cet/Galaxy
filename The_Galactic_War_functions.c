#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "The_Galactic_War_functions.h"
#include "utils.h"

void start_command (char command[], cdll_list_t *galaxy) {

	if (strcmp(command, "ADD") == 0) {
		char name[NAME_LENGTH];
		unsigned int index, num_shields;
		scanf ("%s %d %d", name, &index, &num_shields);

		ADD(galaxy, name, index, num_shields);
		return;
	}

	if (strcmp(command, "SHW") == 0) {
		unsigned int index;
		scanf("%d", &index);

		SHW(galaxy, index);
		return;
	}

	if (strcmp(command, "BLH") == 0) {
		unsigned int index;
		scanf("%d", &index);

		BLH(galaxy, index);
		return;
	}

	if (strcmp(command, "PRINT") == 0) {
		print_galaxy(galaxy);
		return;
	}

}

cdll_list_t *create_list(void) {

	cdll_list_t *list = malloc(sizeof(cdll_list_t));
	DIE(list == NULL, "Memory error!\n");

	list->head = NULL;
	list->size = 0;

	return list;
}

void fill_shield_list(cdll_list_t *shields) {

	for (unsigned int i = 0; i < shields->size; i++) {
		cdll_node_t *new_shield = malloc(sizeof(cdll_node_t));
		DIE(new_shield == NULL, "Memory error!\n");


		if (i == 0) {
			shields->head = new_shield;
			new_shield->next = new_shield;
			new_shield->prev = new_shield;
		} else {
			new_shield->next = shields->head;
			new_shield->prev = shields->head->prev;
			shields->head->prev->next = new_shield;
			shields->head->prev = new_shield;
		}
		new_shield->data = malloc(sizeof(unsigned int));
		DIE(new_shield->data == NULL, "Memory error!\n");

		unsigned int data = 1;
		memcpy(new_shield->data, &data, sizeof(unsigned int));
	}
}


/*Implementata mai jos este comanda ADD, care
face verificarile de memorie necesare, apoi aloca
memorie pentru campurile pe care le necesita o planeta.
Pe urma, verifica daca trebuie introdus primul element din lista sau
un element de pe orice alta pozitie, apeland pentru fiecare
caz functia necesara.*/

void ADD(cdll_list_t *galaxy, char name[], unsigned int n, unsigned int num_shields) {

	DIE(galaxy == NULL, "Memory error!\n");

	if (n > galaxy->size || n < 0) {
		printf("Planet out of bounds!\n");
		return;
	}

	cdll_node_t *new_planet = malloc(sizeof(cdll_node_t));
	DIE(new_planet == NULL, "Memory error!\n");

	new_planet->data = malloc(sizeof(planet_t));
	DIE(new_planet->data == NULL, "memory error!\n");

	strcpy(((planet_t *)new_planet->data)->name, name);

	((planet_t *)new_planet->data)->shields = create_list();
	DIE(((planet_t *)new_planet->data)->shields == NULL, "Memory error!\n");

	((planet_t *)new_planet->data)->shields->size = num_shields;
	fill_shield_list(((planet_t *)new_planet->data)->shields);

	((planet_t *)new_planet->data)->num_kills = 0;

	if (galaxy->size == 0) {
		/*introduce primul element din lista, creand
		bazele listei circulare dublu inlantuita*/
		add_first_planet(galaxy, new_planet);

	} else {
		//adauga un element pe pozitia "n" in lista
		add_nth_planet(galaxy, new_planet, n);
	}

	galaxy->size++;
	printf("The planet %s has joined the galaxy.\n", ((planet_t *)new_planet->data)->name);
}

/*Cele doua functi de mai jos creaza lista dublu inlantuita
circulara introducand un nod nou (o planeta noua) pe pozitia dorita.*/

void add_nth_planet(cdll_list_t*galaxy, cdll_node_t *new_planet, unsigned int n) {
	cdll_node_t *curr;
	curr = galaxy->head;

	for (int i = 0; i < n; i++)
		curr = curr->next;
	
	new_planet->next = curr;
	new_planet->prev = curr->prev;

	curr->prev->next = new_planet;
	curr->prev = new_planet;

	if (n == 0)
		galaxy->head = new_planet;
	
}

void add_first_planet(cdll_list_t *galaxy, cdll_node_t *new_planet) {

	galaxy->head = new_planet;
	new_planet->next = new_planet;
	new_planet->prev = new_planet;
}


void BLH(cdll_list_t *galaxy, unsigned int n) {
	cdll_node_t *curr, *free_pointer;
	curr = galaxy->head;

	for (unsigned int i = 0; i < n; i++)
		curr = curr->next;
	
	if (n > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	if (n == 0)
		galaxy->head = curr->next;
	
	free_pointer = curr;
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;

	printf("The planet %s has been eaten by the vortex.\n", ((planet_t *)curr->data)->name);

	free_shields(&((planet_t *)free_pointer->data)->shields);
	free(free_pointer->data);
	free(free_pointer);

	galaxy->size--;
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

void print_shields(cdll_list_t *shields) {
	cdll_node_t *curr;
	curr = shields->head;

	for (unsigned int i = 0; i < shields->size; i++) {
		printf("%d ", *((unsigned int *)curr->data));
		curr = curr->next;
	}

	printf("\n");
}

void SHW(cdll_list_t *galaxy, unsigned int n) {

	if (galaxy->head == NULL) {
		return;
	}

	cdll_node_t *curr;
	curr = galaxy->head;

	for (unsigned int i = 0; i < n; i++) {
		curr = curr->next;
	}

	printf("NAME: %s\n", ((planet_t *)curr->data)->name);
	if (galaxy->size == 1) {
		printf("CLOSEST: none\n");
	} else
		if (galaxy->size == 2) {
			printf("CLOSEST: %s\n", ((planet_t *)curr->next->data)->name);
		} else {
			printf("CLOSEST: %s and %s\n", ((planet_t *)curr->prev->data)->name, ((planet_t *)curr->next->data)->name);
		}
	
	printf("SHIELDS: ");
	print_shields(((planet_t *)curr->data)->shields);

	printf("KILLED: %d\n", ((planet_t *)curr->next->data)->num_kills);
}

void planet_information() {

}
void print_galaxy (cdll_list_t *galaxy) {
	cdll_node_t *curr;
	curr = galaxy->head;

	printf("%d\n", galaxy->size);
	for (unsigned int i = 0;i < galaxy->size; i++) {
		printf("%s ", (char *)curr->data);
		curr = curr->next;
	}
	printf("\n");
}

void free_shields(cdll_list_t **shields) {
	cdll_node_t *curr, *free_pointer;
	curr = (*shields)->head;

	for (unsigned int i = 0; i < (*shields)->size; i++) {
		free_pointer = curr;
		curr = curr->next;

		free(free_pointer->data);
		free(free_pointer);
	}

	free(*shields);
}

void free_galaxy(cdll_list_t **galaxy) {

	cdll_node_t *curr, *free_pointer;
	curr = (*galaxy)->head;

	for (unsigned int i = 0; i < (*galaxy)->size; i++) {
		free_pointer = curr;
		curr = curr->next;

		free_shields(&((planet_t *)free_pointer->data)->shields);
		free(free_pointer);
	}

	free(*galaxy);
}