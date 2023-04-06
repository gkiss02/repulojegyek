#ifndef REPULOJEGYEK_JARAT_H
#define REPULOJEGYEK_JARAT_H

typedef struct Jarat{
    char jaratSzam[100], indulasiHely[100], erkezesiHely[100], indulasiDatum[100], indulasiIdo[100],
    erkezesiDatum[100], erkezesiIdo[100];
} Jarat;

typedef struct  JaratLista{
    Jarat adat;
    struct JaratLista *kov;
} JaratLista;

JaratLista *jaratListaEleje;

void jaratBeolvas();
JaratLista *jaratHozzaad(JaratLista *eleje, Jarat adat);
JaratLista *jaratTorlese(JaratLista *eleje, char *jarat);
void modositJaratszam(JaratLista *eleje, char *ujJaratszam, char *regiJaratszam);
void modositIndulasihely(JaratLista *eleje, char *jaratSzam, char *ujHely);
void modositErkezesihely(JaratLista *eleje, char *jaratSzam, char *ujHely);
void modositIndulasiIdo(JaratLista *eleje, char *jaratSzam, char *ujDatum, char *ujIdo);
void modositErkezesiIdo(JaratLista *eleje, char *jaratSzam, char *ujDatum, char *ujIdo);
void jaratFileUjrair(JaratLista *eleje);
void jaratFelszabadit(JaratLista *eleje);
void keresIndErkPoint(JaratLista *eleje, char *indulasi, char *erkezesi);
void foglaltsagiTerkep();
void menuTerkep();
bool vanEJarat(JaratLista *eleje, char *jarat);

#endif //REPULOJEGYEK_JARAT_H
