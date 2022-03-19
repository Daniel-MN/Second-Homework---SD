/* Musuroi Daniel-Nicusor - 313CB */
#include "TStiva.h"

void *InitS(){
    void *stiva = calloc(1, sizeof(Stiva));
    return stiva;
}

//inserare la inceputul listei:
int Push(void *stiva, void *el){
    return InsLG(&((Stiva *)stiva)->Lista, el);
}

void *Pop(void *stiva, TElib fe){
    if (stiva == NULL || ((Stiva *)stiva)->Lista == NULL){
		return NULL;
	}

    void *info = ((Stiva *)stiva)->Lista->info;
    Elimina(&((Stiva *)stiva)->Lista, fe);
    return info;
}

void *Top(void *stiva){
    if (stiva == NULL || ((Stiva *)stiva)->Lista == NULL){
		return NULL;
	}

    return ((Stiva *)stiva)->Lista->info;
}

int VidaS(void *stiva){
    if (stiva == NULL || ((Stiva *)stiva)->Lista == NULL){
		return 1;	
    }
    
    return 0;
}

void DistrugeS(void *stiva, TElib fe){
    Distruge(&((Stiva *)stiva)->Lista, fe);
    free(stiva);
}

void *Rastoarna(void *stiva, TElib fe){
    void *res = InitS();
    if (!res){
        printf("Alocare nereusita\n");
        return NULL;
    }

    void *a = Pop(stiva, fe);
    while (a){
        if (!Push(res, a)){
            printf("Rasturnare nereusita\n");
            return NULL;
        }
        a = Pop(stiva, fe);
    }

    return res;
}
