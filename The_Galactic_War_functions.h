#pragma once

#define NAME_LENGTH 200


/* Structura de tip nod de mai jos retine pozitia nodului
de dinaintea sa si de dupa din lista circulara dublu inlantuita.
Campul de data poate sa retine o variabila de tip planet_t
(care defineste planetele din lista galaxie), sau un numar intreg
(caracterizand scuturile fiecarei planete).
*/
typedef struct cdll_node_t cdll_node_t;
struct cdll_node_t {

	cdll_node_t *next, *prev;
	void *data;
};

/*Structura lista retine elementele principale ale listei
adica primul nod, retinut de head, si cate noduri, respectiv
planete sau scuturi, contine, retinut de variabila size.
*/
typedef struct {

	cdll_node_t *head;
	unsigned int size;

}cdll_list_t;

/*Aici am definit o structura pentru
planetele din galaxie.
Acestea au nevoie de un nume, scuturile lor.
De asemenea, trebuie retinut si numarul de coliziuni,
"kill-uri" cu celelalte planete.*/

typedef struct {

	char name[NAME_LENGTH];
	cdll_list_t *shields;
	unsigned int num_kills;

}planet_t;


void start_command (char command[], cdll_list_t *galaxy);
cdll_list_t *create_list(void);

void ADD(cdll_list_t *galaxy, char name[], unsigned int n, unsigned int num_shields);
void add_nth_planet(cdll_list_t *galaxy, cdll_node_t *new_planet, unsigned int n);
void add_first_planet(cdll_list_t *galaxy, cdll_node_t *new_planet);

void BLH();
void remove_planet();
void UPG();
void upgrade_shield();
void EXP();
void add_shield();
void RMV();
void remove_shield();
void COL();
void planet_collision();
void ROT();
void planet_rotation();
void SHW();
void planet_information();
void print_galaxy (cdll_list_t *galaxy);
void free_shields(cdll_list_t **shields);
void free_galaxy(cdll_list_t **galaxy);