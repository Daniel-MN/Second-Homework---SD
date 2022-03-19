/* Musuroi Daniel-Nicusor - 313CB */
#include "Tema2.h"

#ifndef TEMA2
#define TEMA2

Sezon *Allocsez(int nr_ep){
    Sezon *s = (Sezon *)calloc(1, sizeof(Sezon));
    if (!s)
        return NULL;

    s->nr_ep = nr_ep;
    s->ep = InitQ(sizeof(int));
    if (!s->ep)
        return NULL;

    return s;
}

Serial *Allocserial(char *nume, float rating, int nr_sez){
    Serial *s = (Serial *)calloc(1, sizeof(Serial));
    if (!s)
        return NULL;
    
    s->nume = (char *)malloc((strlen(nume) + 1) * sizeof(char));
    if (!s->nume){
        free(s);
        return NULL;
    }
    strcpy(s->nume, nume);
    s->rating = rating;
    s->nr_sez = nr_sez;
    s->poz = 0;
    s->sez = InitQ(sizeof(Sezon));
    if (!s->sez)
        return NULL;

    return s;
}

Sezon *ReadSezon(FILE *in){
    int nr_ep, j;
    int *durata_ep;
    Sezon *aux;
    fscanf(in, "%d", &nr_ep);
    aux = Allocsez(nr_ep);
    if (!aux){
        printf("Alocare nereusita\n");
        return NULL;
    }
    aux->durata_sez = 0;

    for (j = 0; j < nr_ep; j++){
        durata_ep = (int *)malloc(sizeof(int));
        if (!durata_ep){
            printf("Alocare nereusita\n");
            return NULL;
        }
        fscanf(in, "%d", durata_ep);
        aux->durata_sez += *durata_ep;

        if (!IntrQ(aux->ep, (void *)durata_ep)){
            return NULL;
        }
    }

    return aux;
}

void DistrugeSez(void *s){
    Sezon *sez = (Sezon *)s;
    DistrugeQ(sez->ep, free);
    free(sez);
}

Serial *ReadSerial(FILE *in){
    int nr_sez, i;
    char nume[MAX_LEN_STR_NAME];
    float rating;
    Sezon *aux;
    fscanf(in, "%s %f %d", nume, &rating, &nr_sez);
    Serial *s = Allocserial(nume, rating, nr_sez);
    if (!s){
        printf("Alocarea nu a reusit\n");
        return NULL;
    }
    s->durata = 0;

    for (i = 0; i < nr_sez; i++){
        aux = ReadSezon(in);
        if (!aux){
            printf("Citire nereusita\n");
            return NULL;
        }
        s->durata += aux->durata_sez;

        if (!IntrQ(s->sez, (void *)aux))
            return NULL;
    }

    return s;
}

void DistrugeSerial(void *s){
    Serial *serial = (Serial *)s;
    DistrugeQ(serial->sez, DistrugeSez);
    free(serial->nume);
    free(serial);
}

void add_serial(Serial *s, TLG *Lista){
    //lista vida:
    if (*Lista == NULL){
        if (InsLG(Lista, (void *)s)){
            s->poz = 1;
            return;
        } else {
            printf("Nu s-a reusit inserarea\n");
            return;
        }
    }

    //Daca trebuie sa introdus serialul la inceputul listei:
    if (((Serial *)(*Lista)->info)->rating < s->rating){
        if (InsLG(Lista, (void *)s)){
            s->poz = 1;
            return;
        } else {
            printf("Nu s-a reusit inserarea\n");
            return;
        }
    }

    if (((Serial *)(*Lista)->info)->rating == s->rating && 
    strcmp(s->nume, ((Serial *)(*Lista)->info)->nume) < 0){
        if (InsLG(Lista, (void *)s)){
            s->poz = 1;
            return;
        } else {
            printf("Nu s-a reusit inserarea\n");
            return;
        }
    }

    s->poz = 1;
    TLG p, ant;
    //parcurgere:
    for (ant = *Lista, p = (*Lista)->urm; p != NULL; ant = p, p = p->urm){
        s->poz++;
        if (((Serial *)p->info)->rating < s->rating){
            if (InsDupa(ant, (void *)s)){
                return;
            } else {
                printf("Nu s-a reusit inserarea\n");
                return;
            }
        }

        if (((Serial *)p->info)->rating == s->rating && 
        strcmp(s->nume, ((Serial *)p->info)->nume) < 0){
            if (InsDupa(ant, (void *)s)){
                return;
            } else {
                printf("Nu s-a reusit inserarea\n");
                return;
            }
        }
    }

    //Daca se parcurge toata lista, inseamna ca serialul trebuie
    //introdus la finalul listei:
    if (InsDupa(ant, (void *)s)){
        s->poz++;
        return;
    } else {
        printf("Nu s-a reusit inserarea\n");
        return;
    }
}

void add(FILE *in, FILE *out, TLG *CAT){
    int ID;
    fscanf(in, "%d", &ID);
    Serial *s = ReadSerial(in);
    s->ID = ID;
    add_serial(s, &CAT[s->ID - 1]);
    fprintf(out, "Serialul %s a fost adaugat la pozitia %d.\n", s->nume, s->poz);
}

//gaseste un serial dupa nume in cele 4 categorii:
void *find_CAT(TLG *CAT, char *nume){
    int i;
    for (i = 0; i < NR_CAT; i++){
        TLG p;
        for (p = CAT[i]; p != NULL; p = p->urm){
            if (strcmp(((Serial *)p->info)->nume, nume) == 0)
                return p->info;
        }
    }

    return NULL;
}

void *find_later(void *later, char *nume){
    TLG L = ((Coada *)later)->inc;
    TLG p;
    for (p = L; p != NULL; p = p->urm){
        if (strcmp(((Serial *)p->info)->nume, nume) == 0)
            return p->info;
    }
    return NULL;
}

void *find_stiva(void *watching, char *nume){
    TLG L = ((Stiva *)watching)->Lista;
    TLG p;
    for (p = L; p != NULL; p = p->urm){
        if (strcmp(((Serial *)p->info)->nume, nume) == 0)
            return p->info;
    }
    return NULL;
}

void add_sez(FILE *in, FILE *out, TLG *CAT, void *later, void *watching,
void *history){
    char nume[MAX_LEN_STR_NAME];
    fscanf(in, "%s", nume);

    Serial *s = find_CAT(CAT, nume);
    if (!s){
        s = find_later(later, nume);
        if (!s){
            s = find_stiva(watching, nume);
            if (!s){
                s = find_stiva(history, nume);
                if (!s){
                    printf("add_sez Nu s-a gasit serialul %s\n", nume);
                }
            }
        }
    }

    Sezon *sez_nou = ReadSezon(in);
    if (!sez_nou){
        printf("Citire sezon nereusita\n");
        return;
    }
    if (!IntrQ(s->sez, (void *)sez_nou)){
        printf("Introducere sezon nereusita\n");
        return;
    }
    s->nr_sez++;
    s->durata += sez_nou->durata_sez;
    fprintf(out, "Serialul %s are un sezon nou.\n", nume);
}

void reducere_top(TLG *TOP){
    TLG p;
    int i;
    for (p = *TOP, i = 0; p != NULL && i < NR_MAX_TOP - 1; p = p->urm, i++);
    if (p == NULL){
        return;
    }
    
    Distruge(&p->urm, DistrugeSerial);
    p->urm = NULL;
}

void show_CAT123TOP10(FILE *out, TLG L){
    //lista vida:
    if (L == NULL)
        return;
    for (; L->urm != NULL; L = L->urm){
        fprintf(out, "(%s, %.1f), ", ((Serial *)L->info)->nume,
        ((Serial *)L->info)->rating);
    }

    fprintf(out, "(%s, %.1f)", ((Serial *)L->info)->nume,
    ((Serial *)L->info)->rating);
}

void show_coada(FILE *out, void *coada){
    if (VidaQ(coada)){
		return;
	}

    TLG L = ((Coada *)coada)->inc;
    TLG p;
    Serial *s = (Serial *)L->info;
    fprintf(out, "(%s, %.1f)", s->nume, s->rating);

    for (p = L->urm; p != NULL; p = p->urm){
        s = (Serial *)p->info;
        fprintf(out, ", (%s, %.1f)", s->nume, s->rating);
    }
}

void show_stiva(FILE *out, void *stiva){
    if (VidaS(stiva)){
        return;
    }

    TLG L = ((Stiva *)stiva)->Lista;
    TLG p;
    Serial *s = (Serial *)L->info;
    fprintf(out, "(%s, %.1f)", s->nume, s->rating);
    for (p = L->urm; p != NULL; p = p->urm){
        s = (Serial *)p->info;
        fprintf(out, ", (%s, %.1f)", s->nume, s->rating);
    }
}

void add_top(FILE *in, FILE *out, TLG *TOP){
    int poz;
    fscanf(in, "%d", &poz);
    Serial *s = ReadSerial(in);
    s->poz = poz;
    s->ID = 4;
    if (s->poz == 1){
        if (!InsLG(TOP, (void *)s)){
            printf("Adaugare serial nereusita\n");
            return;
        } else {
            reducere_top(TOP);
            fprintf(out, "Categoria top10: [");
            show_CAT123TOP10(out, *TOP);
            fprintf(out, "].\n");
            return;
        }
    }

    int i;
    TLG p;
    for (p = *TOP, i = 1; p->urm != NULL && i < poz - 1; p = p->urm, i++);
    if (!InsDupa(p, (void *)s)){
        printf("Adaugare serial nereusita\n");
        return;
    } 

    reducere_top(TOP);

    fprintf(out, "Categoria top10: [");
    show_CAT123TOP10(out, *TOP);
    fprintf(out, "].\n");
}

Serial *Extrage(TLG *L, char *nume){
    TLG p, ant;
    void *info;
    for (ant  = NULL, p = *L; p != NULL; ant = p, p = p->urm){
        if (strcmp(((Serial *)(p->info))->nume, nume) == 0){
            if (ant == NULL){
                *L = (*L)->urm;
            } else {
                ant->urm = p->urm;
            }
            info = p->info;
            p->info = NULL;
            p->urm = NULL;
            free(p);
            
            return info;
        }
    }

    return NULL;
}

//extragereaa serialului cu numele dat din una dintre cele 4 categorii:
Serial *Extrage_serial(TLG *CAT, char *nume){
    int i = 0;
    Serial *s;
    for (i = 0; i < NR_CAT; i++){
        s = (Serial *)Extrage(&CAT[i], nume);
        if (s)
            return s;
    }
    return NULL;
}

Serial *Extrage_serial_coada(void *coada, char *nume){
    Coada *c = (Coada *)coada;
    if (c == NULL){
        return NULL;
    }
    Serial *info = Extrage(&(c->inc), nume);
    if (c->inc == NULL){
        c->sf = NULL;
    }
    return info;
}

Serial *Extrage_serial_stiva(void *watching, char *nume){
    Stiva *s = (Stiva *)watching;
    if (s == NULL){
        return NULL;
    }
    return Extrage(&(s->Lista), nume);
}

void watch_later(FILE *in, FILE *out, TLG *CAT, void *later){
    char nume[MAX_LEN_STR_NAME];
    fscanf(in, "%s", nume);


    //extragerea serialului cu numele dat din una dintre cele 4 categorii:
    Serial *s = Extrage_serial(CAT, nume);
    if (!s){
        printf("Serialul nu exista\n");
        return;
    }

    if(!IntrQ(later, (void *)s)){
        printf("Introducere in later esuata\n");
        return;
    }

    fprintf(out, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n",
    nume, LungimeCoada(later));
}

void show(FILE *in, FILE *out, TLG *CAT,
 void *later, void *watching, void *history){

    char *categorie = (char *)malloc(MAX_LEN_STR * sizeof(char));
    if (!categorie){
        printf("Alocarea operation nu a reusit!\n");
        return;
    }
    fscanf(in, "%s", categorie);

    fprintf(out, "Categoria %s: [", categorie);
    if (strcmp(categorie, "1") == 0){
        show_CAT123TOP10(out, CAT[0]);
    }
    if (strcmp(categorie, "2") == 0){
        show_CAT123TOP10(out, CAT[1]);
    }
    if (strcmp(categorie, "3") == 0){
        show_CAT123TOP10(out, CAT[2]);
    }
    if (strcmp(categorie, "top10") == 0){
        show_CAT123TOP10(out, CAT[3]);
    }
    if (strcmp(categorie, "later") == 0){
        show_coada(out, later);
    }
    if (strcmp(categorie, "watching") == 0){
        show_stiva(out, watching);
    }
    if (strcmp(categorie, "history") == 0){
        show_stiva(out, history);
    }
    fprintf(out, "].\n");

    free(categorie);
}


void watch(FILE *in, FILE *out, TLG *CAT, void *later, void *watching,
void *history){
    char nume[MAX_LEN_STR_NAME];
    fscanf(in, "%s", nume);

    int durata;
    fscanf(in, "%d", &durata);
    
    Serial *s = Extrage_serial(CAT, nume);
    if (!s){//trebuie sa caut in watching, later
        s = Extrage_serial_coada(later, nume);
        if (!s){
            s = Extrage_serial_stiva(watching, nume);
            if (!s){
                printf("Watch Nu s-a gasit serialul %s\n", nume);
                return;
            }
        }
    }

    s->durata = s->durata - durata;
    if (s->durata > 0){
        Push(watching, (void *)s);
    } else {
        Push(history, (void *)s);
        fprintf(out, "Serialul %s a fost vizionat integral.\n", nume);
    }
}

#endif