#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "The_Galactic_War_functions.h"
#include "utils.h"

/* Functia de mai jos este apelata in main() si are 
rolul de a recunoaste comanda introdusa la tastatura si de
a "porni" functia aferenta acesteia. De asemenea, citeste in continuare
elementele pe care le necesita fiecare comanda in parte.
*/
void start_command (char command[], cdll_list_t *galaxy) {

	//Pentru comanda ADD
	if (strcmp(command, "ADD") == 0) {
		char name[NAME_LENGTH];
		unsigned int index, num_shields;
		scanf ("%s %d %d", name, &index, &num_shields);

		ADD(galaxy, name, index, num_shields);
		return;
	}

	//Pentru comanda SHW
	if (strcmp(command, "SHW") == 0) {
		unsigned int index;
		scanf("%d", &index);

		SHW(galaxy, index);
		return;
	}

	//Pentru comanda BLH
	if (strcmp(command, "BLH") == 0) {
		unsigned int index;
		scanf("%d", &index);

		BLH(galaxy, index);
		return;
	}

	//Pentru comanda UPG
	if (strcmp(command, "UPG") == 0) {
		unsigned int index, sh_index, value;
		scanf("%d%d%d", &index, &sh_index, &value);

		UPG(galaxy, index, sh_index, value);
		return;
	}

	//Pentru comanda EXP
	if (strcmp(command, "EXP") == 0) {
		unsigned int index, value;
		scanf("%d%d", &index, &value);

		EXP(galaxy, index, value);
		return;
	}

	//Pentru comanda RMV
	if (strcmp(command, "RMV") == 0) {
		unsigned int index, sh_index;
		scanf("%d%d", &index, &sh_index);

		RMV(galaxy, index, sh_index);
		return;
	}

	//Pentru comanda COL
	if (strcmp(command, "COL") == 0) {
		unsigned int index1, index2;
		scanf("%d%d", &index1, &index2);

		COL(galaxy, index1, index2);
		return;
	}

	if (strcmp(command, "PRINT") == 0) {
		print_galaxy(galaxy);
		return;
	}

}

/*Aceasta functie creaza o lista circulara dublu inlantuita
alocand memorie pentru aceasta si initializand camurile ei.
*/
cdll_list_t *create_list(void) {

	cdll_list_t *list = malloc(sizeof(cdll_list_t));
	DIE(list == NULL, "Memory error!\n");

	list->head = NULL;
	list->size = 0;

	return list;
}

/*Functia de mai jos creeaza lista de scuturi, dublu inlantuita
circulara, initializand toate elementele listei cu 1. De asemenea,
aceasta se creaza introducand cate un element nou la finalul
listei.
*/
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

//ADD

/*Implementata mai jos este comanda ADD, care
face verificarile de memorie necesare, apoi aloca
memorie pentru campurile pe care le necesita o planeta.
De asemenea, se fac verificarile aferente pentru indecsii introdusi
(se verifica daca exista acea pozitie in liste).
Pe urma, verifica daca trebuie introdus primul element din lista sau
un element de pe orice alta pozitie, apeland pentru fiecare
caz functia necesara.*/

void ADD(cdll_list_t *galaxy, char name[], unsigned int n, unsigned int num_shields) {

	DIE(galaxy == NULL, "Memory error!\n");

	//Verificare index planeta
	if (n > galaxy->size || n < 0) {
		printf("Planet out of bounds!\n");
		return;
	}

	//Creare planeta noua + umplere campuri data
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

//BLH

/*In continuare, este implementata functia de BLH, care elimina
o planeta din galaxie. Aceasta initial ajunge cu ajutorul unui
nod auxiliar ( curr ), pe pozitia planetei care va fi "eaten by the vortex".
Se fac verificarile indecsilor si in cazul in care prima planeta din lista
va fi eliminata, mutam si galaxy->head.
La final, se elibereaza memoria atribuita planetei.
*/
void BLH(cdll_list_t *galaxy, unsigned int n) {

	//Declarare variabila auxiliara curr si a pointerului caruia i se va da free.
	cdll_node_t *curr = galaxy->head;
	cdll_node_t *free_pointer = NULL;

	//curr ajunge pe pozitia planetei dorite
	for (unsigned int i = 0; i < n; i++) {
		curr = curr->next;
	}
	
	//Verificare index
	if (n > galaxy->size || n < 0) {
		printf("Planet out of bounds!\n");
		return;
	}

	//Mutare head in cazul primei planete
	if (n == 0)
		galaxy->head = curr->next;
	
	//Schimbare legaturi ale planetei
	free_pointer = curr;
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;

	printf("The planet %s has been eaten by the vortex.\n", ((planet_t *)curr->data)->name);

	//Eliberare memorie
	free_shields(&((planet_t *)free_pointer->data)->shields);
	free(free_pointer->data);
	free(free_pointer);

	//Modificarea numarului de planete din galaxie
	galaxy->size--;
}

//UPG

/*Functia UPG modifica unul dintre scuturile unei planete. Aceasta necesita
Indexul planetei din galaxie, al scutului care trebuie modificat si valoarea
scutului dupa modificare. 
*/

void UPG(cdll_list_t *galaxy, unsigned int n, unsigned int sh_index, unsigned int value) {


	if (n >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	cdll_node_t *curr;

	curr = galaxy->head;
	for (unsigned int i = 0; i < n; i++) {
		curr = curr->next;
	}

	if (sh_index >= ((planet_t *)curr->data)->shields->size) {
		printf("Shield out of bounds!\n");
		return;
	}

	cdll_node_t *curr_shield = upgrade_shield(((planet_t *)curr->data)->shields, sh_index);
	memcpy(curr_shield->data, &value, sizeof(unsigned int));
}

cdll_node_t *upgrade_shield(cdll_list_t *shields, unsigned int sh_index) {

	cdll_node_t *curr;
	curr = shields->head;

	for (unsigned int i = 0; i < sh_index; i++) {
		curr = curr->next;
	}

	return curr;
}
void EXP(cdll_list_t *galaxy, unsigned int n, unsigned int value) {

	if (n > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	cdll_node_t *curr = galaxy->head;
	for (unsigned int i = 0; i < n; i++) {
		curr = curr->next;
	}
	add_shield(((planet_t *)curr->data)->shields, value);

}
void add_shield(cdll_list_t *shields, unsigned int value) {
	cdll_node_t *new_shield = malloc(sizeof(cdll_node_t));
	DIE(new_shield == NULL, "Memory error!\n");

	new_shield->data = malloc(sizeof(unsigned int));
	DIE(new_shield->data == NULL, "Memory error!\n");

	memcpy(new_shield->data, &value, sizeof(unsigned int));

	if (shields->size == 0) {
		shields->head = new_shield;
		new_shield->next = new_shield;
		new_shield->prev = new_shield;

		shields->size++;
		return;
	}

	new_shield->next = shields->head;
	new_shield->prev = shields->head->prev;
	shields->head->prev->next = new_shield;
	shields->head->prev = new_shield;

	shields->size++;
}
void RMV(cdll_list_t *galaxy, unsigned int n, unsigned int sh_index) {

	if (n > galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	cdll_node_t *curr = galaxy->head;
	for (unsigned int i = 0; i < n; i++) {
		curr = curr->next;
	}

	if (sh_index > ((planet_t *)curr->data)->shields->size) {
		printf("Shield out of bounds!\n");
		return;
	}

	if (((planet_t *)curr->data)->shields->size <= 4) {
		printf("A planet cannot have less than 4 shields!\n");
		return;
	}

	remove_shield(((planet_t *)curr->data)->shields, sh_index);

}
void remove_shield(cdll_list_t *shields, unsigned int sh_index) {

	cdll_node_t *curr = shields->head;
	if (sh_index == 0) {
		shields->head = curr->next;
	}

	for (unsigned int i = 0; i < sh_index; i++) {
		curr = curr->next;
	}

	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;

	free(curr->data);
	free(curr);

	shields->size--;
}
void COL(cdll_list_t *galaxy, unsigned int index1, unsigned int index2) {
	
	if (index1 >= galaxy->size || index2 >= galaxy->size) {
		printf("Planet out of bounds!\n");
		return;
	}

	cdll_node_t *planet1 = galaxy->head;
	for (unsigned int i = 0; i < index1; i++) {
		planet1 = planet1->next;
	}

	cdll_node_t *planet2 = planet1->next;
	cdll_node_t *curr;
	unsigned int impl1, impl2;
	impl1 = 0;
	impl2 = 0;

	curr = collision_node(((planet_t *)planet1->data)->shields, ((planet_t *)planet1->data)->shields->size / 4);
	if ((*(unsigned int *)curr->data) == 0) {
		printf("The planet %s has imploded.\n", ((planet_t *)planet1->data)->name);
		if (index1 == 0) {
			galaxy->head = planet1->next;
		}

		remove_planet(galaxy, planet1);
		impl1 = 1;
	}

	curr = collision_node(((planet_t *)planet2->data)->shields, (((planet_t *)planet2->data)->shields->size / 4) * 3);
	if ((*(unsigned int *)curr->data) == 0) {
		printf("The planet %s has imploded.\n", ((planet_t *)planet2->data)->name);
		if (index2 == 0) {
			galaxy->head = planet2->next;
		}

		remove_planet(galaxy, planet2);
		impl2 = 1;
	}

	if (impl1 == 0 && impl2 == 1) {
		((planet_t *)planet1->data)->num_kills++;
	} else
		if (impl2 == 0 && impl1 == 1) {
			((planet_t *)planet2->data)->num_kills++;
		}
}

void remove_planet(cdll_list_t *galaxy, cdll_node_t *planet) {
	
	cdll_node_t *free_pointer = planet;
	planet->prev->next = planet->next;
	planet->next->prev = planet->prev;

	free_shields(&((planet_t *)free_pointer->data)->shields);
	free(free_pointer->data);
	free(free_pointer);

	galaxy->size--;
}

cdll_node_t *collision_node(cdll_list_t *shields, unsigned int sh_index) {

	cdll_node_t *curr = shields->head;
	for (unsigned int i = 0; i < sh_index; i++) {
		curr = curr->next;
	}

	(*(unsigned int *)curr->data)--;
	return curr;
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
		free(free_pointer->data);
		free(free_pointer);
	}

	free(*galaxy);
}