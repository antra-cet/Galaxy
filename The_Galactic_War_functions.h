#pragma once

#define NAME_LENGTH 200
#define 


/*Aici am definit o structura pentru
planetele din galaxie (nodurile din lista).
Acestea au nevoie de un nume, scuturile lor, numarul de
scuturi si cate o legatura cu planeta de dupa si cea de dinainte.
De asemenea, trebuie retinut si numarul de colliziuni
"kill-uri" cu celelalte planete.
*/
typedef struct {

	dll_planet_t *next, *prev;
	char name[NAME_LENGTH];
	unsigned int *shields;
	unsigned int shield_size;
	unsigned int num_kills;

}dll_planet_t;

/*Structura galaxy retine elementele principale ale listei
adica primul nod, retinut de head, si cate noduri, respectiv
planete contine, retinut de variabila size.
*/
typedef struct {

	dll_planet_t *head;
	unsigned int size;

}dll_galaxy_t;

