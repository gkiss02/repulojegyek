#ifndef REPULOJEGYEK_UTAS_H
#define REPULOJEGYEK_UTAS_H

typedef struct Utas {
    char utasNeve[100], utlevelSzama[100], szuletesiIdeje[100], jelszava[100], menu[100], ulesszam[100];
} Utas;

typedef struct UtasLista {
    Utas adat;
    struct UtasLista *kov;
} UtasLista;

UtasLista *utasListaEleje;

void utasBeolvas(char *jarat);
UtasLista *utasHozzaad(UtasLista *eleje, Utas adat);
void utasFelszabadit(UtasLista *eleje);
int utasListaMeret(UtasLista *eleje);
void menukSzama(UtasLista *eleje);
void utasHozzafuz(char *jarat);
UtasLista *utasTorlese(UtasLista *eleje, char *utas);
void utasFileUjrair(UtasLista *eleje, char *fileName);
void keresJaratSz();
void keresIndErk();
bool foglaltE(UtasLista *eleje, char *ules);
char milyenMenu(UtasLista *eleje, char *ules);
void modositNev(UtasLista *eleje, char *nev, char *uj);
void modositUtlevel(UtasLista *eleje, char *nev, char *uj);
void modositSzul(UtasLista *eleje, char *nev, char *uj);
void modositJelszo(UtasLista *eleje, char *nev, char *uj);
void modositMenu(UtasLista *eleje, char *nev, char *uj);
void modositUles(UtasLista *eleje, char *nev, char *uj);
bool vanEIlyenUtas(UtasLista *eleje, char *nev, char *jelszo);
void utasModosit(char *nev, char *fileName);
bool vanEIlyenUles(char *s);
char *visszaUtlevel();
char *visszaJelszo();
char *visszaMenu();
char *visszaUles();

#endif //REPULOJEGYEK_UTAS_H
