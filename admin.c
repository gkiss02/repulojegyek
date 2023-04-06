#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "admin.h"
#include "jarat.h"
#include "menu.h"
#include "utas.h"
#include "segedFuggvenyek.h"
#include "debugmalloc.h"

void adminMode () {
    char adminNev[] = "admin", jelszo[] = "tItok321", bekerNev[100], bekerJelszo[100];
    printf("Felhasznalo nev: ");
    scanf("%s", bekerNev);
    fomenubeLepes(bekerNev);
    printf("Beker jelszo: ");
    scanf("%s", bekerJelszo);
    fomenubeLepes(bekerJelszo);
    if (strcmp(adminNev,bekerNev) == 0 && strcmp(jelszo,bekerJelszo) == 0) {
        adminMenu();
    } else {
        printf("Hibas jelszo\n");
        adminMode();
    }
}

void adminMenu() {
    char bekerMenu[100];
    int bekerMenuInt;
    printf("Admin mode aktiv\n");
    printf("\t(1) Adatok lekérdezése jaratszam alapjan\n");
    printf("\t(2) Jarat hozzáadása\n");
    printf("\t(3) Jarat módosítása\n");
    printf("\t(4) Jarat törlése\n");

    printf("\tAdjon meg egy szamot: ");
    scanf("%s",bekerMenu);
    fomenubeLepes(bekerMenu);
    getchar();

    if (strlen(bekerMenu) == 1 && isdigit(bekerMenu[0]) != 0) {
        bekerMenuInt = atoi(&bekerMenu[0]);
        adminMenuPontok(bekerMenuInt);
    } else if (strlen(bekerMenu) == 1 && (bekerMenu[0] == 'M' || bekerMenu[0] == 'B')) {
        menu();
    } else adminMenu();
}

void adminMenuPontok(int bekerMenu) {
    switch (bekerMenu) {
        case 1:
            adatokLekerdezese();
            break;

        case 2:
            jaratHozzafuz();
            break;

        case 3:
            jaratModositasa();
            break;

        case 4:
            printf("");
            char *jarat = visszaJarat();
            adminMenubeLepes(jarat);

            printf("Biztosan torli a jaratot?");
            char c[100];
            scanf("%s", c);
            getchar();
            fomenubeLepes(c);
            adminMenubeLepes(c);
            char txt[100];
            if (strlen(c) == 1 && c[0] == 'Y') {
                jaratListaEleje = jaratTorlese(jaratListaEleje, jarat);
                jaratFileUjrair(jaratListaEleje);
                strcpy(txt, jarat);
                strcat(txt, ".txt");
                remove(txt);
            }
            free(jarat);
            adminMenu();
            break;

        default:
            adminMode();
            break;
    }
}

void jaratHozzafuz() {
    char jaratszam[100], *indulasiHely, *erkezesiHely, *indulasDatum, *indulasiIdo, *erkezesiDatum, *erkezesiIdo;
    printf("Jaratszam: ");
    scanf("%s", jaratszam);
    getchar();
    adminMenubeLepes(jaratszam);

    printf("Indulasi hely: ");
    indulasiHely = hosszuSorVisszaad();
    adminMenubeLepes(indulasiHely);

    printf("Erkezesi hely: ");
    erkezesiHely = hosszuSorVisszaad();
    adminMenubeLepes(erkezesiHely);

    printf("Indulas dátuma [EEEE.HH.NN.]: ");
    indulasDatum = visszaDatum();
    adminMenubeLepes(indulasDatum);

    printf("Indulas ideje [OO:PP]: ");
    indulasiIdo = visszaIdo();
    adminMenubeLepes(indulasiIdo);

    printf("Erkezés datuma [EEEE.HH.NN.]: ");
    erkezesiDatum = visszaDatum();
    adminMenubeLepes(erkezesiDatum);

    printf("Erkezés ideje [OO:PP]: ");
    erkezesiIdo = visszaIdo();
    adminMenubeLepes(erkezesiIdo);

    FILE *fp;
    fp = fopen("jaratok.txt", "a");
    fprintf(fp, "%s;%s;%s;%s;%s;%s;%s\n", jaratszam, indulasiHely, erkezesiHely, indulasDatum, indulasiIdo,
            erkezesiDatum, erkezesiIdo);
    fclose(fp);
    jaratBeolvas();

    free(indulasiHely);
    free(erkezesiHely);
    free(indulasDatum);
    free(indulasiIdo);
    free(erkezesiDatum);
    free(erkezesiIdo);

    printf("Kilep? [Y][N]");
    char out;
    scanf("%s", &out);
    fomenubeLepes(&out);
    adminMenubeLepes(&out);
    if (out == 'Y') adminMenu();
    else jaratHozzafuz();
}

void jaratModositasa () {
    char beker[100];
    int bekerInt = 0;
    printf("Mit szeretene módosítani? ");
    printf("\n(1) Jaratszámot");
    printf("\n(2) Indulasi helyet");
    printf("\n(3) Erkezési helyet");
    printf("\n(4) Indulasi idot");
    printf("\n(5) Erkezési idot");
    printf("\nValasz: ");
    scanf("%s", beker);
    getchar();

    if (strlen(beker) == 1) {
        if (isdigit(beker[0]) != 0) bekerInt = atoi(beker);
        else if (beker[0] == 'M') menu();
        else if (beker[0] == 'B') adminMenu();
    } else jaratModositasa();

    switch (bekerInt) {
        case 1:
            adminJaratszam();
            break;
        case 2:
            adminIndulasiHely();
            break;
        case 3:
            adminErkezesiHely();
            break;
        case 4:
            adminIndulasiIdo();
            break;
        case 5:
            adminErkezesiIdo();
            break;
        default:
            jaratModositasa();
            break;
    }
}

void adminJaratszam() {
    char txtU[100], txtR[100];
    char *regiJaratszam = visszaJarat();
    adminMenubeLepes(regiJaratszam);

    printf("Uj jaratszam: ");
    char ujJaratszam[100];
    scanf("%s", ujJaratszam);
    adminMenubeLepes(ujJaratszam);
    fomenubeLepes(ujJaratszam);

    modositJaratszam(jaratListaEleje, ujJaratszam,regiJaratszam);
    jaratFileUjrair(jaratListaEleje);
    strcpy(txtR, regiJaratszam);
    strcpy(txtU, ujJaratszam);
    strcat(txtR, ".txt");
    strcat(txtU, ".txt");
    rename(txtR, txtU);
    free(regiJaratszam);
    adminMenu();
}

void adminIndulasiHely() {
    char *jaratszam = visszaJarat();
    adminMenubeLepes(jaratszam);

    printf("Indulasi hely: ");
    char *indulasiHely = hosszuSorVisszaad();
    adminMenubeLepes(indulasiHely);
    modositIndulasihely(jaratListaEleje, jaratszam, indulasiHely);
    jaratFileUjrair(jaratListaEleje);
    free(jaratszam);
    free(indulasiHely);
    adminMenu();
}

void adminErkezesiHely() {
    char *jaratszam = visszaJarat();
    adminMenubeLepes(jaratszam);

    printf("Erkezesi hely: ");
    char *erkezesiHely = hosszuSorVisszaad();
    adminMenubeLepes(erkezesiHely);
    modositErkezesihely(jaratListaEleje, jaratszam, erkezesiHely);
    jaratFileUjrair(jaratListaEleje);
    free(jaratszam);
    free(erkezesiHely);
    adminMenu();
}

void adminIndulasiIdo() {
    char *jaratszam = visszaJarat();
    adminMenubeLepes(jaratszam);

    printf("Indulas dátuma [EEEE.HH.NN.]: ");
    char *indulasiDatum = visszaDatum();
    adminMenubeLepes(indulasiDatum);

    printf("Indulas ideje [OO:PP]: ");
    char *indulasiIdo = visszaIdo();
    adminMenubeLepes(indulasiIdo);

    modositIndulasiIdo(jaratListaEleje, jaratszam, indulasiDatum, indulasiIdo);
    jaratFileUjrair(jaratListaEleje);
    free(jaratszam);
    free(indulasiDatum);
    free(indulasiIdo);
    adminMenu();
}

void adminErkezesiIdo() {
    char *jaratszam = visszaJarat();
    adminMenubeLepes(jaratszam);

    printf("Erkezés dátuma [EEEE.HH.NN.]: ");
    char *erkezesiDatum = visszaDatum();
    adminMenubeLepes(erkezesiDatum);

    printf("Erkezés ideje [OO:PP]: ");
    char *erkezesiIdo = visszaIdo();
    adminMenubeLepes(erkezesiIdo);

    modositErkezesiIdo(jaratListaEleje, jaratszam, erkezesiDatum, erkezesiIdo);
    jaratFileUjrair(jaratListaEleje);
    free(jaratszam);
    free(erkezesiDatum);
    free(erkezesiIdo);
    adminMenu();
}

void adminMenubeLepes(char *s) {
    if (strlen(s) == 1 && s[0] == 'B') {
        adminMenu();
    }
}

void adatokLekerdezese() {
    char *bekerJarat = visszaJarat();
    adminMenubeLepes(bekerJarat);
    char txt[100];
    strcpy(txt, bekerJarat);
    free(bekerJarat);
    strcat(txt, ".txt");
    utasBeolvas(txt);

    printf("\nFoglaltsagi terkep");
    foglaltsagiTerkep();
    printf("\nMenu terkep");
    menuTerkep();

    printf("\nOsszes foglalas: %d\n", utasListaMeret(utasListaEleje));
    menukSzama(utasListaEleje);
    visszalep();
}

void visszalep() {
    printf("\nVissza lep? [Y][N]");
    char c[100];
    scanf("%s", c);
    fomenubeLepes(c);
    adminMenubeLepes(c);
    if (strlen(c) == 1 && c[0] == 'Y') adminMenu();
    else visszalep();
}