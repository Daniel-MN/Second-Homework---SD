/* Musuroi Daniel-Nicusor - 313CB */
#include "TCoada.h"
#include "Tema2.h"

void *InitQ(int dim){
    Coada *coada = calloc(1, sizeof(Coada));
    coada->dim = dim;
    coada->inc = NULL;
    coada->sf = NULL;

    return (void *)coada;
}

int VidaQ(void *coada){
    Coada *c = (Coada *)coada;
    if (c == NULL || (c->inc == NULL && c->sf == NULL)){
        return 1;
    }

    return 0;
}

void *ExtrQ(void *coada, TElib fe){
    if (VidaQ(coada)){
        return NULL;
    }

    Coada *c = (Coada *)coada;
    //coada nevida:
    void *info = c->inc->info;

    if (c->inc == c->sf){//coada are un singur element
        c->inc->info = NULL;
        Distruge(&(c->inc), fe);
        c->inc = NULL;
        c->sf = NULL;
    } else {//coada contine mai multe elemente
        Elimina(&(c->inc), fe);
    }

    return info;
}

int IntrQ(void *coada, void *el){
    Coada *c = (Coada *)coada;
    TLG aux = malloc(sizeof(TCelulaG));
    if(!aux)
        return 0;

    aux->info = el;
    aux->urm = NULL;

    if (VidaQ(coada)){

        c->inc = aux;
        c->sf = aux;
        return 1;
    } else {

        c->sf->urm = aux;
        c->sf = aux;
        return 1;
    }
}

int LungimeCoada(void *coada){
    Coada *c = (Coada *)coada;
    int nr = 0;
    TLG p;
    for (p = c->inc; p != NULL; p = p->urm){
        nr++;
    }
    return nr;
}

void *copie_coada(void *coada){
    Coada *c = (Coada *)coada;
    void *copie = InitQ(c->dim);
    if (!copie){
        printf("Alocare nereusita\n");
        return NULL;
    }

    ((Coada *)copie)->inc = copie_lista(c->inc);
    TLG p;
    for (p = ((Coada *)copie)->inc; p->urm != NULL; p = p->urm);
    ((Coada *)copie)->sf = p;
    return copie;
}

void DistrugeQ(void *coada, TElib fe){
    Coada *c = (Coada *)coada;
    while (c->inc != NULL){
        TLG aux = c->inc;
        c->inc = c->inc->urm;

        fe(aux->info);
        free(aux);
    }
    free(coada);
}