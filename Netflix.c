/* Musuroi Daniel-Nicusor - 313CB */
#include "Tema2.h"

void tema2(FILE *in, FILE *out){
    TLG *CAT;//vector ce contine cele patru categorii
    CAT = (TLG *)calloc(NR_CAT, sizeof(TLG));
    if (!CAT){
        printf("Alocare nereusita!\n");
        return; 
    }
    void *later = InitQ(sizeof(Serial));
    if (!later){
        printf("Alocare nereusita!\n");
        return;
    }
    void *watching = InitS();
    if (!watching){
        printf("Alocare nereusita!\n");
        return;
    }
    void *history = InitS();
    if (!history){
        printf("Alocare nereusita!\n");
        return;
    }
    char *operation = (char *)malloc(MAX_LEN_STR * sizeof(char));
    if (!operation){
        printf("Alocarea operation nu a reusit!\n");
        return;
    }

    //citesc fiecare operatia din fisierul de intrare
    //pana la intalnirea sfarsitului de fisier:
    while (fscanf(in, "%s", operation) != EOF){

        if (strcmp(operation, "add") == 0){
            add(in, out, CAT);
        }

        if (strcmp(operation, "add_top") == 0){
            add_top(in, out, &CAT[3]);
        }

        if (strcmp(operation, "later") == 0){
            watch_later(in, out, CAT, later);
        }

        if (strcmp(operation, "add_sez") == 0){
            add_sez(in, out, CAT, later, watching, history);
        }

        if (strcmp(operation, "watch") == 0){
            watch(in, out, CAT, later, watching, history);
        }

        if (strcmp(operation, "show") == 0){
            show(in, out, CAT, later, watching, history);
        }

    }

    free(operation);
    int i;
    for (i = 0; i < NR_CAT; i++)
        Distruge(&CAT[i], DistrugeSerial);
    free(CAT);
    DistrugeQ(later, DistrugeSerial);
    DistrugeS(watching, DistrugeSerial);
    DistrugeS(history, DistrugeSerial);
}

int main(int argc, char *argv[]){
    if (argc != 3)
    {
        printf("Mod de rulare al temei incorect!\n");
        return 1;
    }

    FILE *in = fopen(argv[1], "rt");
    if (in == NULL)
    {
        return 2;
    }

    FILE *out = fopen(argv[2], "wt");
    if (out == NULL)
    {
        return 2;
    }

    // functia care rezolva tema:
    tema2(in, out);

    fclose(in);
    fclose(out);

    return 0;
}