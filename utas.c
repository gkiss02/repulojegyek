#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "jarat.h"
#include "utas.h"
#include "menu.h"
#include "segedFuggvenyek.h"
#include "debugmalloc.h"

void utasBeolvas(char *fileName) {
    if (utasListaEleje != NULL) utasFelszabadit(utasListaEleje);
    utasListaEleje = NULL;
    char sor[100], bekerUtasNeve[100], bekerUtlevelSzam[100], bekerSzulIdo[100], bekerJelszo[100], bekerMenu[100],
    bekerUles[100];

    FILE *fp;
    if ((fp = fopen(fileName, "r")) == NULL) {
        printf("Error! opening file");
    }

    while (fscanf(fp, "%s", sor) != EOF) {
        Utas utas;
        sscanf(sor, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]", bekerUtasNeve, bekerUtlevelSzam, bekerSzulIdo, bekerJelszo,
               bekerMenu, bekerUles);
        strcpy(utas.utasNeve, bekerUtasNeve);
        strcpy(utas.utlevelSzama, bekerUtlevelSzam);
        strcpy(utas.szuletesiIdeje, bekerSzulIdo);
        strcpy(utas.jelszava, bekerJelszo);
        strcpy(utas.menu, bekerMenu);
        strcpy(utas.ulesszam, bekerUles);
        utasListaEleje = utasHozzaad(utasListaEleje, utas);
    }
    fclose(fp);
}

UtasLista *utasHozzaad(UtasLista *eleje, Utas adat) {
    UtasLista *uj;
    uj = (UtasLista *) malloc(sizeof(UtasLista));
    uj->adat = adat;
    uj->kov = NULL;

    if (eleje == NULL) {
        eleje = uj;
    } else {
        UtasLista *mozgo = eleje;
        while (mozgo->kov != NULL)
            mozgo = mozgo->kov;
        mozgo->kov = uj;
        uj->kov = NULL;
    }
    return eleje;
}

void utasFelszabadit(UtasLista *eleje) {
    UtasLista *iter = eleje;
    while (iter != NULL) {
        UtasLista *kov = iter->kov;
        free(iter);
        iter = kov;
    }
}

int utasListaMeret(UtasLista *eleje) {
    int szamol = 0;
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        szamol++;
    }
    return szamol;
}

void menukSzama(UtasLista *eleje) {
    int n = 0, v = 0, l = 0;
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.menu, "N") == 0) n++;
        else if (strcmp(iter->adat.menu, "V") == 0) v++;
        else l++;
    }

    printf("Menuk szerint");
    printf("\n\tNormál: %d", n);
    printf("\n\tVega: %d", v);
    printf("\n\tLaktozmentes: %d", l);
}

void utasHozzafuz(char *fileName) {
    char *bekerUtasNeve, *bekerUtlevelSzam, *bekerSzulIdo, *bekerJelszo, *bekerMenu, *bekerUles;
    printf("Nev: ");
    bekerUtasNeve = hosszuSorVisszaad();
    if (strcmp(bekerUtasNeve, "B") == 0) menu();
    printf("Utlevélszam: ");
    bekerUtlevelSzam = visszaUtlevel();
    if (strcmp(bekerUtlevelSzam, "B") == 0) menu();
    printf("Szuletesi idő [EEEE.HH.NN.]: ");
    bekerSzulIdo = visszaDatum();
    if (strcmp(bekerSzulIdo, "B") == 0) menu();
    printf("Jelszo: ");
    bekerJelszo = visszaJelszo();
    if (strcmp(bekerJelszo, "B") == 0) menu();
    bekerMenu = visszaMenu();
    if (strcmp(bekerMenu, "B") == 0) menu();
    bekerUles =  visszaUles();
    if (strcmp(bekerUles, "B") == 0) menu();

    FILE *fp;
    fp = fopen(fileName, "a");
    fprintf(fp, "%s;%s;%s;%s;%s;%s\n", bekerUtasNeve, bekerUtlevelSzam, bekerSzulIdo, bekerJelszo, bekerMenu,
            bekerUles);

    free(bekerUtasNeve);
    free(bekerUtlevelSzam);
    free(bekerSzulIdo);
    free(bekerJelszo);
    free(bekerMenu);
    free(bekerUles);
    fclose(fp);
    utasBeolvas(fileName);
    menu();
}

UtasLista *utasTorlese(UtasLista *eleje, char *utas) {
    UtasLista *lemarado = NULL;
    UtasLista *mozgo = eleje;
    while (mozgo != NULL && strcmp(mozgo->adat.utasNeve, utas) != 0) {
        lemarado = mozgo;
        mozgo = mozgo->kov;
    }

    if (mozgo == NULL) {

    } else if (lemarado == NULL) {
        UtasLista *ujeleje = mozgo->kov;
        free(mozgo);
        eleje = ujeleje;
    } else {
        lemarado->kov = mozgo->kov;
        free(mozgo);
    }
    return eleje;
}

void utasFileUjrair(UtasLista *eleje, char *fileName) {
    UtasLista *iter;
    FILE *fp;
    fp = fopen(fileName, "w");
    for (iter = eleje; iter != NULL; iter = iter->kov) {
        Utas u = iter->adat;
        fprintf(fp, "%s;%s;%s;%s;%s;%s\n", u.utasNeve, u.utlevelSzama, u.szuletesiIdeje, u.jelszava, u.menu, u
        .ulesszam);
    }
    fclose(fp);
}

void keresJaratSz() {
    char *bekerJarat = visszaJarat();
    fomenuBack(bekerJarat);

    printf("Van ilyen jarat\n");

    printf("Szeretne foglalni? [Y][N]");
    char c[100];
    scanf("%s", c);
    fomenubeLepes(c);
    getchar();

    if (strlen(c) == 1 && c[0] == 'Y') {
        char fileName[100];
        strcpy(fileName, bekerJarat);
        free(bekerJarat);
        strcat(fileName, ".txt");
        utasBeolvas(fileName);
        if (utasListaMeret(utasListaEleje) == 150) {
            printf("Nincs szabadhely");
            return;
        }
        utasHozzafuz(fileName);
    } else {
        free(bekerJarat);
        menu();
    }
}

void keresIndErk () {
    char *bekerInd, *bekerErk, ind[100], erk[100];
    printf("Honnan: ");
    bekerInd = hosszuSorVisszaad();
    printf("Hova: ");
    bekerErk = hosszuSorVisszaad();
    strcpy(ind, bekerInd);
    strcpy(erk, bekerErk);
    free(bekerInd);
    free(bekerErk);
    keresIndErkPoint(jaratListaEleje, ind, erk);
}

bool foglaltE(UtasLista *eleje, char *ules) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.ulesszam, ules) == 0) return true;
    }
    return false;
}

char milyenMenu(UtasLista *eleje, char *ules) {
    UtasLista *iter;
    char c = 'S';
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.ulesszam, ules) == 0) {
            c = iter->adat.menu[0];
            break;
        }
    }
    return c;
}

void modositNev(UtasLista *eleje, char *nev, char *uj) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0) {
            strcpy(iter->adat.utasNeve, uj);
            break;
        }
    }
}

void modositUtlevel(UtasLista *eleje, char *nev, char *uj) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0) {
            strcpy(iter->adat.utlevelSzama, uj);
            break;
        }
    }
}

void modositSzul(UtasLista *eleje, char *nev, char *uj) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0) {
            strcpy(iter->adat.szuletesiIdeje, uj);
            break;
        }
    }
}

void modositJelszo(UtasLista *eleje, char *nev, char *uj) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0) {
            strcpy(iter->adat.jelszava, uj);
            break;
        }
    }
}

void modositMenu(UtasLista *eleje, char *nev, char *uj) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0) {
            strcpy(iter->adat.menu, uj);
            break;
        }
    }
}

void modositUles(UtasLista *eleje, char *nev, char *uj) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0) {
            strcpy(iter->adat.ulesszam, uj);
            break;
        }
    }
}

bool vanEIlyenUtas(UtasLista *eleje, char *nev, char *jelszo) {
    UtasLista *iter;
    for (iter = eleje; iter != NULL; iter = (UtasLista *) iter->kov) {
        if (strcmp(iter->adat.utasNeve, nev) == 0 && strcmp(iter->adat.jelszava, jelszo) == 0) return true;
    }
    return false;
}

void utasModosit(char *nev, char *fileName) {
    char beker[100];
    int bekerInt = 0;
    printf("Utas adatok modositasa");
    printf("\n(1) Nev modositasa");
    printf("\n(2) Utlevelszam modositasa");
    printf("\n(3) Szuletesi datum modositasa");
    printf("\n(4) Jelszo modositasa");
    printf("\n(5) Menu modositasa");
    printf("\n(6) Ules modositasa");
    printf("\n(7) Foglalas torlése");
    printf("\nVálasz: ");
    scanf("%s", beker);
    getchar();

    if (strlen(beker) == 1 && isdigit(beker[0]) != 0) {
        bekerInt = atoi(&beker[0]);
    } else menu();

    switch (bekerInt) {
        case 1:
            printf("Modositott nev: ");
            char *ujNev;
            ujNev = hosszuSorVisszaad();
            if (strcmp(ujNev, "B") == 0) utasModosit(nev,fileName);
            fomenubeLepes(ujNev);
            modositNev(utasListaEleje, nev, ujNev);
            utasFileUjrair(utasListaEleje, fileName);
            strcpy(nev, ujNev);
            free(ujNev);
            utasModosit(nev,fileName);
            break;

        case 2:
            printf("Uj utlevelszam: ");
            char *ujUt;
            ujUt = visszaUtlevel();
            if (strcmp(ujUt, "B") == 0) utasModosit(nev,fileName);
            fomenubeLepes(ujUt);
            modositUtlevel(utasListaEleje, nev, ujUt);
            utasFileUjrair(utasListaEleje, fileName);
            free(ujUt);
            utasModosit(nev,fileName);
            break;

        case 3:
            printf("Modositott szuletesi datum: ");
            char *ujSzul;
            ujSzul = visszaDatum();
            if (strcmp(ujSzul, "B") == 0) utasModosit(nev,fileName);
            modositSzul(utasListaEleje, nev, ujSzul);
            utasFileUjrair(utasListaEleje, fileName);
            free(ujSzul);
            utasModosit(nev,fileName);
            break;

        case 4:
            printf("Új jelszot: ");
            char *ujJelszo;
            ujJelszo = visszaJelszo();
            if (strcmp(ujJelszo, "B") == 0) utasModosit(nev,fileName);
            modositJelszo(utasListaEleje, nev, ujJelszo);
            utasFileUjrair(utasListaEleje, fileName);
            free(ujJelszo);
            utasModosit(nev,fileName);
            break;

        case 5:
            printf("");
            char *ujMenu;
            ujMenu = visszaMenu();
            if (strcmp(ujMenu, "B") == 0) utasModosit(nev,fileName);
            modositMenu(utasListaEleje, nev, ujMenu);
            utasFileUjrair(utasListaEleje, fileName);
            free(ujMenu);
            utasModosit(nev,fileName);
            break;

        case 6:
            printf("");
            char *ujUles;
            ujUles = visszaUles();
            if (strcmp(ujUles, "B") == 0) utasModosit(nev,fileName);
            modositUles(utasListaEleje, nev, ujUles);
            utasFileUjrair(utasListaEleje, fileName);
            free(ujUles);
            utasModosit(nev,fileName);
            break;

        case 7:
            printf("Biztosan torolni szeretne foglalasat? ");
            char c[100];
            scanf("%s", c);
            fomenubeLepes(c);
            if (strlen(c) == 1 && c[0] == 'Y') {
                utasListaEleje = utasTorlese(utasListaEleje, nev);
                utasFileUjrair(utasListaEleje, fileName);
                menu();
            } else {
                utasModosit(nev,fileName);
            }
            break;

        default:
            utasModosit(nev,fileName);
            break;
    }
}

bool vanEIlyenUles(char *s) {
    char c[4];
    for (int i = 1; i <= 25; ++i) {
        for (char j = 'A'; j <= 'F'; ++j) {
            sprintf(c, "%d%c", i,j);
            if (strcmp(s, c) == 0) return true;
        }
    }
    return false;
}

char *visszaUtlevel() {
    char beker[100];
    scanf("%s", beker);
    char *vissza = dinFoglal(beker);
    fomenubeLepes(beker);
    return vissza;
}

char *visszaJelszo() {
    char beker[100];
    bool b;
    do {
        scanf("%s", beker);
        if (strcmp(beker, "B") == 0) return "B";
        fomenubeLepes(beker);
        b = jelszoEllenoriz(beker);
        if (!b) printf("A jelszo nem megfelelo. A jelszonak minimum 8 karakterbol kell allni, tartalmaznia"
                                  " kell egy nagy betut, illetve szamot\n");
    } while (!b);
    char *vissza = dinFoglal(beker);
    return vissza;
}

char *visszaMenu() {
    char beker[100];
    bool b;
    do {
        printf("Kerjuk valasszon menuink kozul");
        printf("\n\tN-Normal");
        printf("\n\tV-Vegetárianus");
        printf("\n\tL-Laktozmentes");
        printf("\nMenu: ");
        scanf("%s", beker);
        if (strcmp(beker, "B") == 0) return "B";
        fomenubeLepes(beker);
        b = menuEllenoriz(beker);
        if (!b) printf("Kerjuk az N/V/L karaktereket hasznalja csak!\n");
    } while (!b);
    char *vissza = dinFoglal(beker);
    return vissza;
}

char *visszaUles() {
    char beker[100];
    bool foglalt, van;
    do {
        foglaltsagiTerkep();
        printf("Valasszon egy helyet, (S jelzi a szabad helyeket): ");
        scanf("%s", beker);
        if (strcmp(beker, "B") == 0) return "B";
        fomenubeLepes(beker);
        if (beker[0] == '0') {
            beker[0] = beker[1];
            beker[1] = beker[2];
            beker[2] = '\0';
        }
        foglalt = foglaltE(utasListaEleje, beker);
        van = vanEIlyenUles(beker);
        if (foglalt) printf("Az ules mar foglalt!");
        if (!van) printf("Nincs ilyen ules!\n");
    } while (foglalt || !van);
    char *vissza = dinFoglal(beker);
    return vissza;
}
