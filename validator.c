#include "validator.h"
#include "domain.h"
#include "string.h"
#include "assert.h"
#include "stdlib.h"


Validator validare_data(data data1){
    if(data1.zi <=0 || data1.zi > 31){
        return 1;
    }
    if(data1.luna <=0 || data1.luna > 12){
        return 1;
    }
    if(data1.an <=0){
        return 1;
    }


    return 0;
}

Validator validare_oferta(oferta oferta1){
    if(strcmp(oferta1.tip, "") == 0|| (strcmp(oferta1.tip, "Mare") != 0 && strcmp(oferta1.tip, "Munte") != 0
                                       && strcmp(oferta1.tip, "City Break") != 0)){
        return 2;
    }
    if(strcmp(oferta1.destinatie, "") == 0 ){
        return 2;
    }
    if(validare_data(*oferta1.data_plecare) == 1){
        return 2;
    }
    if(oferta1.pret <= 0){
        return 2;
    }
    return 0;
}



void test_validare_oferta(){
    data * data1 = malloc(sizeof (data));
    creare_data(data1, 12,3,2024);

    oferta * oferta1 = malloc(sizeof (oferta));
    creare_oferta(oferta1, "Munte", "Fagaras", data1, 500);

    data * data2 = malloc(sizeof (data));
    creare_data(data2, 12,3,2024);

    oferta * oferta2 = malloc(sizeof(oferta));
    creare_oferta(oferta2, "Mare", "", data2, 500);

    data * data3 = malloc(sizeof (data));
    creare_data(data3, 12,3,2024);

    oferta * oferta3 = malloc(sizeof(oferta));
    creare_oferta(oferta3, "", "Paris", data3, 500);

    data * data4 = malloc(sizeof (data));
    creare_data(data4, 12,3,2024);
    oferta * oferta4 = malloc(sizeof(oferta));
    creare_oferta(oferta4, "Test", "Paris", data4, 500);

    data * data5 = malloc(sizeof (data));
    creare_data(data5, 12,3,2024);
    oferta * oferta5 = malloc(sizeof(oferta));
    creare_oferta(oferta5, "Munte", "Fagaras", data5, -500);

    data * data6 = malloc(sizeof (data));
    creare_data(data6, 12,-3,2024);
    oferta * oferta6 = malloc(sizeof(oferta));
    creare_oferta(oferta6, "Munte", "Fagaras", data6, 500);

    assert(validare_oferta(*oferta1) == 0);
    assert(validare_oferta(*oferta2) == 2);
    assert(validare_oferta(*oferta3) == 2);
    assert(validare_oferta(*oferta4) == 2);
    assert(validare_oferta(*oferta5) == 2);
    assert(validare_oferta(*oferta6) == 2);

    distrugere_oferta(oferta1);
    distrugere_oferta(oferta2);
    distrugere_oferta(oferta3);
    distrugere_oferta(oferta4);
    distrugere_oferta(oferta5);
    distrugere_oferta(oferta6);
}

void test_validare_data(){
    data * data1 = malloc(sizeof(data));
    creare_data(data1, 12,3,2024);

    data *data2 = malloc(sizeof(data));
    creare_data(data2,-1,4,2024);

    data *data3 = malloc(sizeof(data));
    creare_data(data3,45, 4, 2024);

    data *data4 = malloc(sizeof(data));
    creare_data(data4,12, 7, -1);

    data *data5 = malloc(sizeof(data));
    creare_data(data5,3, -1, 2024);

    data *data6 = malloc(sizeof(data));
    creare_data(data6,3, 45, 2024);

    assert(validare_data(*data1) == 0);
    assert(validare_data(*data2) == 1);
    assert(validare_data(*data3) == 1);
    assert(validare_data(*data4) == 1);
    assert(validare_data(*data5) == 1);
    assert(validare_data(*data6) == 1);

    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
    free(data6);


}

void teste_validator(){
    test_validare_data();
    test_validare_oferta();
}
