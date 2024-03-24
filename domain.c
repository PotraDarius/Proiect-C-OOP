#include "domain.h"
#include "string.h"
#include "assert.h"
#include "stdlib.h"

void creare_oferta( oferta * oferta1, char * tip, char * destinatie, data * data_plecare, int pret){
    oferta1->tip = malloc((strlen(tip)+1) * sizeof (char * ));
    strcpy(oferta1->tip, tip);

    oferta1->destinatie = malloc((strlen(destinatie)+1) * sizeof (char *));
    strcpy(oferta1->destinatie, destinatie);
    oferta1->pret = pret;


    oferta1->data_plecare = data_plecare;

}

void creare_data(data * data1, int zi, int luna, int an){
    data1->zi = zi;
    data1->luna = luna;
    data1->an = an;
}




int verificare_egalitate_data(data data1, data data2){
    if(data1.an == data2.an && data1.luna == data2.luna && data1.zi == data2.zi){
        return 1;
    }
    return 0;
}

int verificare_egalitate(oferta oferta1, oferta oferta2){
    if(strcmp(oferta1.tip, oferta2.tip) == 0){
        if(strcmp(oferta1.destinatie, oferta2.destinatie) == 0){
            if(verificare_egalitate_data(*oferta1.data_plecare, *oferta2.data_plecare) == 1){
                if(oferta1.pret == oferta2.pret){
                    return 1;
                }
            }
        }
    }
    return 0;
}

void distrugere_oferta(oferta * oferta1){
    free(oferta1->tip);
    free(oferta1->destinatie);
    free(oferta1->data_plecare);
    free(oferta1);
}

void test_creare_si_distrugere(){
    oferta * oferta1 = malloc(1*sizeof (oferta));

    data *data1 = malloc(sizeof(data));
    creare_data(data1, 12,3,2024);

    creare_oferta(oferta1, "munte", "Fagaras", data1, 500);
    assert(oferta1->pret == 500);
    assert(strcmp(oferta1->tip, "munte") == 0);
    assert(strcmp(oferta1->destinatie, "Fagaras") == 0);
    assert(verificare_egalitate_data(*oferta1->data_plecare, *data1) == 1);

    distrugere_oferta(oferta1);
}

void test_verificare_egalitate_oferta(){
    data *data1 = malloc(sizeof(data));
    creare_data(data1, 12,3,2024);
    oferta * oferta1 ;
    oferta1 = malloc(sizeof (oferta));
    creare_oferta(oferta1, "munte", "Fagaras", data1, 500);

    oferta * oferta2;
    data *data2 = malloc(sizeof(data));
    creare_data(data2, 12,3,2024);
    oferta2 = malloc(sizeof (oferta));
    creare_oferta(oferta2, "munte", "Fagaras", data2, 500);

    assert(verificare_egalitate(*oferta1, *oferta2) == 1);

    distrugere_oferta(oferta1);
    distrugere_oferta(oferta2);
}


void test_verificare_egalitate_data(){
    data *data1 = malloc(sizeof (data));
    creare_data(data1, 4,5,2024);
    data *data2 = malloc(sizeof (data));
    creare_data(data2, 4,6,2024);
    data *data3 = malloc(sizeof(data));
    creare_data(data3, 4,5,2024);

    assert(verificare_egalitate_data(*data1, *data2) == 0);
    assert(verificare_egalitate_data(*data1, *data3) == 1);
    free(data1);
    free(data2);
    free(data3);
}

void teste_domain(){
    test_creare_si_distrugere();
    test_verificare_egalitate_data();
    test_verificare_egalitate_oferta();
}