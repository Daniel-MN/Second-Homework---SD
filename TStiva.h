/* Musuroi Daniel-Nicusor - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include "TLista.h"

#ifndef STIVA
#define STIVA

typedef struct stiva{
    TLG Lista;
} Stiva;
 
void *InitS();    /* initializeaza stiva */
int Push(void *stiva, void *el);  /* pune element in varful stivei */
void *Pop(void *stiva, TElib fe);  /* extrage elementul din varful stivei la adresa el */
void *Top(void *stiva);  /* copiaza elementul din varful stivei la adresa el */
int VidaS(void *stiva); //verifica daca o stiva este vida sau nu
void DistrugeS(void *stiva, TElib fe); //distruge stiva
void *Rastoarna(void *stiva, TElib fe); //returneaza stiva rasturnata

#endif
