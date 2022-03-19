#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "TLista.h"
#include "TStiva.h"
#include "TCoada.h"

#define MAX_LEN_STR 20
#define NR_CAT 4
#define MAX_LEN_STR_NAME 33
#define NR_MAX_TOP 10

typedef struct serial{
    int ID;
    char *nume;
    float rating;
    int nr_sez;
    int durata;
    int poz;//pozitia la carea a fost introdus in lista
    //Dupa actualizari ale listelor 1, 2, 3 poz nu se modifica
    void *sez;//coada de sezoane
} Serial;

typedef struct sezon{
    int nr_ep;
    int durata_sez;
    void *ep;//coada de episoade
} Sezon;

Sezon *Allocsez(int nr_ep);
void DistrugeSez(void *s);
Serial *Allocserial(char *nume, float rating, int nr_sez);
void DistrugeSerial(void *s);
void add(FILE *in, FILE *out, TLG *CAT);//functia care realizeaza
//adaugarea unui serial intr-o categorie
void add_sez(FILE *in, FILE *out, TLG *CAT, void *later, void *watching,
void *history);
//adauga un nou sezon unui serial
void add_top(FILE *in, FILE *out, TLG *TOP);//adaugare serial in top10
void watch_later(FILE *in, FILE *out, TLG *CAT, void *later); 
//adaugarea unui serial in coada later
void show(FILE *in, FILE *out, TLG *CAT,
 void *later, void *watching, void *history);;//functia care realizeaza
//afisarea serialelor dintr-o categorie
void watch(FILE *in, FILE *out, TLG *CAT, void *later, void *watching,
 void *history);
