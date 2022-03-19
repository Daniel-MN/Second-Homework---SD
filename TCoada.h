/* Musuroi Daniel-Nicusor - 313CB */
#include "TLista.h"

#ifndef COADA
#define COADA

typedef struct coada{
    TLG inc;
    TLG sf;
    int dim;
} Coada;

void *InitQ(int dim); //initializeaza coada cu elemente de dimensiunea dim
int VidaQ(void *coada); //verifica daca o coada este vida sau nu
void *ExtrQ(void *coada, TElib fe); //extrage primul element din coada
int IntrQ(void *coada, void *el); //introduce un element in coada
int LungimeCoada(void *coada);//calculeaza lungimea cozii
void *copie_coada(void *coada);//returneaza o copie a cozii
void DistrugeQ(void *coada, TElib fe); //distruge coada

#endif