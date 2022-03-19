/* Musuroi Daniel-Nicusor - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef Lista_generica
#define Lista_generica

typedef struct celulag
{
  void *info;
  struct celulag *urm;
} TCelulaG, *TLG;

typedef void (*TElib)(void *); //functie de eliberare element
typedef void *(*TCopie)(void *); //fcuntie de copiere a unui element
typedef void (*TShow)(FILE *, void *); //afisare element

/* functii lista generica */
int InsLG(TLG *L, void*);  /*- inserare la inceput reusita sau nu (1/0) -*/
void Distruge(TLG *L, TElib fe); /* distruge lista */
size_t LungimeLG(TLG *L);   /* numarul de elemente din lista */
void Elimina(TLG *L, TElib fe); //elimina primul element din lista
int InsDupa(TLG a, void *el); //insereaza elementul el dupa celula a
void Inserarecelula(TLG *a, TLG b); //inserare celula b la sfarsitul listei a
TLG copie_lista(TLG a); //copiaza o lista

#endif
