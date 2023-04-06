#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "segedFuggvenyek.h"
#include "menu.h"
#include "debugmalloc.h"

char *hosszuSortOlvas() {
    int db = 0;
    char *sor = (char*) malloc(sizeof(char) * 1);
    sor[0] = '\0';
    char ujkar;
    while (scanf("%c", &ujkar) == 1 && ujkar != '\n') {
        char *ujtomb = (char*) malloc(sizeof(char) * (db+1+1));
        for (int i = 0; i < db; ++i)
            ujtomb[i] = sor[i];
        free(sor);
        sor = ujtomb;
        ujtomb[db] = ujkar;
        ujtomb[db+1] = '\0';
        ++db;
    }
    return sor;
}

char *szokozEltavolit(char *s) {
    int szamol = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] != ' ') szamol++;
    }

    char *uj = (char *) malloc((szamol + 1) * sizeof (char ));
    if (uj == NULL) return NULL;

    int idx = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] != ' ') {
            uj[idx++] = s[i];
        }
    }
    uj[idx] = '\0';
    return uj;
}

bool datumEllenoriz(char *s) {
    if (strlen(s) != 11) return false;

    for (int i = 0; i < 3; ++i) {
        if (isdigit(s[i]) == 0) return false;
    }

    if (s[4] != '.') return false;

    if (isdigit(s[5]) == 0 || isdigit(s[6]) == 0) {
        return false;
    } else {
        int szam = szamma(s[5], s[6]);
        if (szam > 12 || szam < 1) return false;
    }

    if (s[7] != '.') return false;

    if (isdigit(s[8]) == 0 || isdigit(s[9]) == 0) {
        return false;
    } else {
        char datum[12];
        strcpy(datum,s);
        char *d = strtok(datum, " ");
        if (!napHelyes(d)) return false;
    }

    if (s[10] != '.') return false;
    return true;
}

bool idoEllenoriz(char *s) {
    if (strlen(s) != 5) return false;

    if (isdigit(s[0]) == 0 || isdigit(s[1]) == 0) {
        return false;
    } else {
        int szam = szamma(s[0], s[1]);
        if (szam > 23) return false;
    }

    if (s[2] != ':') return false;

    if (isdigit(s[3]) == 0 || isdigit(s[4]) == 0) {
        return false;
    } else {
        int szam = szamma(s[3], s[4]);
        if (szam >= 60) return false;
    }
    return true;
}

bool napHelyes(char *d) {
    char datum[12], sep[2] = ".";
    int honapok[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    strcpy(datum,d);
    int ev, honap, nap;
    ev = atoi(strtok(datum, sep));
    honap = atoi(strtok(NULL, sep));
    nap = atoi(strtok(NULL, sep));

    if (ev % 4 == 0) honapok[1] = 29;

    if (honapok[honap - 1] < nap) return false;
    return true;
}

int szamma(char c1, char c2) {
    char szam[3];
    szam[0] = c1;
    szam[1] = c2;
    szam[2] = '\0';
    return atoi(szam);
}

bool jelszoEllenoriz (char *s) {
    bool nagyBetu = false, szam = false;

    if (strlen(s) < 8) return false;

    for (int i = 0; s[i] != '\0' ; ++i) {
        if (s[i] == toupper(s[i]) && isdigit(s[i]) == 0) {
            nagyBetu = true;
            break;
        }
    }
    if (!nagyBetu) return false;

    for (int i = 0; s[i] != '\0' ; ++i) {
        if (isdigit(s[i]) != 0) {
            szam = true;
            break;
        }
    }
    if (!szam) return false;

    return true;
}

void fomenubeLepes(char *s) {
    if (strlen(s) == 1 && s[0] == 'M') {
        menu();
    }
}

bool menuEllenoriz(char *s) {
    if (strlen(s) != 1) return false;
    char c = s[0];
    if (c != 'N' && c != 'L' && c != 'V') return false;
    return true;
}

char *dinFoglal(char *s) {
    unsigned long meret = strlen(s) + 1;
    char *uj = (char *) malloc(meret * sizeof (char ));
    strcpy(uj, s);
    uj[meret - 1] = '\0';
    return uj;
}

char *hosszuSorVisszaad() {
    char *beker, str[100], str2[100];
    beker = hosszuSortOlvas();
    strcpy(str, beker);
    free(beker);
    beker = szokozEltavolit(str);
    strcpy(str2, beker);
    free(beker);
    fomenubeLepes(str2);
    char *vissza = dinFoglal(str2);
    return vissza;
}

char *visszaDatum() {
    char beker[100];
    bool b;
    do {
        scanf("%s", beker);
        if (strcmp(beker, "B") == 0) return "B";
        fomenubeLepes(beker);
        b = datumEllenoriz(beker);
        if (!b) printf("Hibas formatum! Kérjük EEEE.HH.NN. formaban irja be\n");
    } while (!b);
    char *vissza = dinFoglal(beker);
    return vissza;
}

char *visszaIdo() {
    char beker[100];
    bool b;
    do {
        scanf("%s", beker);
        if (strcmp(beker, "B") == 0) return "B";
        fomenubeLepes(beker);
        b = idoEllenoriz(beker);
        if (!b) printf("Hibas formatum! Kérjük [OO:PP] formaban írja be\n");
    } while (!b);
    char *vissza = dinFoglal(beker);
    return vissza;
}

char *visszaJarat() {
    char beker[100];
    bool c;
    do {
        printf("Jaratszam: ");
        scanf("%s", beker);
        getchar();
        fomenubeLepes(beker);
        c = vanEJarat(jaratListaEleje, beker);
        if (!c) printf("Nincs ilyen jarat!\n");
    } while(!c);
    char *uj = dinFoglal(beker);
    return uj;
}

void fomenuBack(char *s) {
    if (strlen(s) == 1 && s[0] == 'B') menu();
}