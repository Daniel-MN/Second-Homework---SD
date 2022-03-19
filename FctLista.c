/* Musuroi Daniel-Nicusor - 313CB */
#include "TLista.h"

int InsLG(TLG *L, void* el){

	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = el;
	aux->urm = *L;
	*L = aux;

	return 1;
}

//Numarul de elemente dintr-o lista:
size_t LungimeLG(TLG *L){
	size_t lg = 0;
	TLG p;
	for (p = *L; p != NULL; p = p->urm)
        lg++;

	return lg;
}

void Distruge(TLG *L, TElib free_elem) /* distruge lista */
{
	while(*L != NULL)
    {
        TLG aux = *L;     /* adresa celulei eliminate */
        if (!aux)
            return;

        free_elem(aux->info);  /* elib.spatiul ocupat de element*/
        *L = aux->urm;    /* deconecteaza celula din lista */
        free(aux);   /* elibereaza spatiul ocupat de celula */
    }
}

void Elimina(TLG *L, TElib fe){
	if (*L == NULL){
		return;
	}

	TLG aux = (*L);
	*L = (*L)->urm;
	aux->urm = NULL;
	Distruge(&aux, fe);
}

int InsDupa(TLG a, void *el){
	TLG aux = malloc(sizeof(TCelulaG));
	if(!aux)
	    return 0;

	aux->info = el;
	aux->urm = a->urm;
	a->urm = aux;

	return 1;
}

void Inserarecelula(TLG *a, TLG b){
	if (*a == NULL){
		*a = b;
		(*a)->urm = NULL;
	}
	(*a)->urm = b;
}

TLG copie_lista(TLG a){
	TLG c = NULL;
	TLG p_c, p_a;
	InsLG(&c, a->info);
	p_c = c;
	for (p_a = a->urm; p_a != NULL; p_a = p_a->urm){
		InsDupa(p_c, p_a->info);
		p_c = p_c->urm;
	}

	return c;
}