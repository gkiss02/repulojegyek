#ifndef REPULOJEGYEK_SEGEDFUGGVENYEK_H
#define REPULOJEGYEK_SEGEDFUGGVENYEK_H

char *hosszuSortOlvas();
char *szokozEltavolit(char *s);
bool datumEllenoriz(char *s);
bool idoEllenoriz(char *s);
bool napHelyes (char *d);
int szamma(char c1, char c2);
bool jelszoEllenoriz(char *s);
void fomenubeLepes(char *s);
bool menuEllenoriz(char *s);
char *dinFoglal(char *s);
char *hosszuSorVisszaad();
char *visszaDatum();
char *visszaIdo();
char *visszaJarat();
void fomenuBack(char *s);

#endif //REPULOJEGYEK_SEGEDFUGGVENYEK_H
