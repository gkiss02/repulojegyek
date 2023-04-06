#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "menu.h"
#include "admin.h"
#include "utas.h"
#include "segedFuggvenyek.h"
#include "debugmalloc.h"


void menu() {
    char bekerMenu[100];
    int bekerMenuInt;
    printf("\t(1) Kereses jaratszám alapjan\n");
    printf("\t(2) Kereses indulasi/erkezési hely alapjan\n");
    printf("\t(3) Meglevo foglalas kezelese\n");
    printf("\t(4) Kilepes\n");
    printf("\tAdjon meg egy szamot: ");
    scanf("%s", bekerMenu);
    getchar();

    if (strlen(bekerMenu) == 1 && isdigit(bekerMenu[0]) != 0) {
        bekerMenuInt = atoi(&bekerMenu[0]);
        menuPontok(bekerMenuInt);
    } else if (strcmp(bekerMenu, "/OADMIN") == 0) {
        adminMode();
    } else {
        menu();
    }
}

void menuPontok (int bekerMenu) {
    switch (bekerMenu) {
        case 1:
            keresJaratSz();
            break;
        case 2:
            keresIndErk();
            break;
        case 3:
            printf("Modositas elott kerem jelentekezzen be\n");
            char *jaratSzam, *nevDin, nev[100], jelszoUtas[100], fileName[100];
            jaratSzam = visszaJarat();
            fomenuBack(jaratSzam);

            strcpy(fileName, jaratSzam);
            strcat(fileName, ".txt");
            free(jaratSzam);
            utasBeolvas(fileName);

            bool b;
            do {
                printf("Nev: ");
                nevDin = hosszuSorVisszaad();
                strcpy(nev, nevDin);
                free(nevDin);
                printf("Jelszó: ");
                scanf("%s", jelszoUtas);
                getchar();
                b = vanEIlyenUtas(utasListaEleje, nev, jelszoUtas);
                if (!b) printf("Nincs ilyen utas\n");
            } while (!b);
            utasModosit(nev, fileName);
            break;

        case 4:
            utasFelszabadit(utasListaEleje);
            jaratFelszabadit(jaratListaEleje);
            exit(0);

        default:
            menu();
            break;
    }
}