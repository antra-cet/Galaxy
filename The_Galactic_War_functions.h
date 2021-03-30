// Copyright 2021 <Copyright Bivolaru Andra>
#ifndef THE_GALACTIC_WAR_FUNCTIONS_H_
#define THE_GALACTIC_WAR_FUNCTIONS_H_

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

// Functii apelate din main()
void start_command(char command[], cdll_list_t *galaxy);
cdll_list_t *create_list(void);

// Functiile necesare comenzii ADD
void ADD(cdll_list_t *galaxy, char name[], unsigned int n,
		 unsigned int num_shields);
void add_nth_planet(cdll_list_t *galaxy,
					cdll_node_t *new_planet, unsigned int n);
void add_first_planet(cdll_list_t *galaxy, cdll_node_t *new_planet);

// Functiile necesare comenzii UPG
void UPG(cdll_list_t *galaxy, unsigned int n,
		 unsigned int sh_index, unsigned int value);
cdll_node_t *upgrade_shield(cdll_list_t *shields, unsigned int sh_index);

// Functiile necesare comenzii BLH
void BLH(cdll_list_t *galaxy, unsigned int n);

// Functiile necesare comenzii EXP
void EXP(cdll_list_t *galaxy, unsigned int n, unsigned int value);
void add_shield(cdll_list_t *shields, unsigned int value);

// Functiile necesare comenzii RMV
void RMV(cdll_list_t *galaxy, unsigned int n, unsigned int sh_index);
cdll_node_t *remove_nth_shield(cdll_list_t *shields, unsigned int sh_index);

// Functiile necesare comenzii COL
void COL(cdll_list_t *galaxy, unsigned int index1, unsigned int index2);
cdll_node_t *collision_node(cdll_list_t *shields, unsigned int sh_index);
void remove_planet(cdll_list_t *galaxy, cdll_node_t *planet);

// Functiile necesare comenzii ROT
void ROT(cdll_list_t *galaxy, unsigned int n,
		 char direction, unsigned int units);
void planet_rotation_c(cdll_list_t *shields, unsigned int units);
void planet_rotation_t(cdll_list_t *shields, unsigned int units);

// Functiile necesare comenzii SHW
void SHW(cdll_list_t *galaxy, unsigned int n);
void print_shields(cdll_list_t *shields);

// Functii de eliberare a memoriei
void free_shields(cdll_list_t **shields);
void free_galaxy(cdll_list_t **galaxy);

#endif  // THE_GALACTIC_WAR_FUNCTIONS_H_
