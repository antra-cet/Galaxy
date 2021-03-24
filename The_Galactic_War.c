#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "The_Galactic_War_functions.h"

#define COMMAND_LENGTH 100

int main() {
    
    /*Declar variabila care retine comanda data de la tastatura,
    numarul de comenzi M si lista galaxiei .
    */
    char command[COMMAND_LENGTH];
    unsigned int M;
    cdll_list_t *galaxy = create_list();

    scanf("%u", &M);
    for (unsigned int i = 0; i < M; i++) {
        scanf("%s", command);

        /*Se apeleaza functia start command
        care apeleaza functia care se doreste sa fie
        folosita.*/
        start_command(command, galaxy);
    }

    /*eliberam lista galaxiei in cazul
    in care a fost folosita.*/
    if (galaxy != NULL) {
        free_galaxy(&galaxy);
    }

    return 0;
}