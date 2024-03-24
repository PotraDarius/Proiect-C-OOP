#include "domain.h"
#include "repository.h"
#include "assert.h"
#include "stdlib.h"
#include "string.h"


void creare_repository(repo * repo1){
    repo1->numar_oferte_curente = 0;
    repo1->capacitate = 2;
    repo1->oferte = malloc(repo1->capacitate * sizeof(oferta *));
}

void distrugere_repository(repo * repo1){
    distrugere_lista_oferta(repo1);
    free(repo1);
}

void redimensionare_in_sus(repo *  repo1){
    oferta * *  aux = malloc(2* repo1->capacitate * sizeof (oferta*));
    for(int i = 0; i < repo1->capacitate; i++)
        aux[i] = repo1->oferte[i];
    repo1->capacitate *= 2;
    free(repo1->oferte);
    repo1->oferte = aux;
}

void redimensionare_in_jos(repo * repo1){
    oferta * * aux = malloc(repo1->capacitate/2 * sizeof(oferta*) );
    for(int i = 0; i < repo1->numar_oferte_curente; i++)
        aux[i] = repo1->oferte[i];
    repo1->capacitate /= 2;
    free(repo1->oferte);
    repo1->oferte = aux;
}

int add_oferta(repo* repo1, oferta * oferta1){
    for(int i = 0; i < repo1->numar_oferte_curente; i++){
        if(verificare_egalitate(*oferta1, *repo1->oferte[i]) == 1){
            return 1;
        }
    }
    if (repo1->numar_oferte_curente == repo1->capacitate){
        redimensionare_in_sus(repo1);
    }
    repo1->oferte[repo1->numar_oferte_curente++] = oferta1;
    return 0;

}

void copiere_date(oferta * oferta1, oferta * oferta2){
    strcpy(oferta1->tip, oferta2->tip);
    strcpy(oferta1->destinatie, oferta2->destinatie);
    *oferta1->data_plecare = *oferta2->data_plecare;
    oferta1->pret = oferta2->pret;
}

int delete_oferta(repo * repo1, int index){
    if(index >= 0 && index < repo1->numar_oferte_curente){

        for(int i = index; i < repo1->numar_oferte_curente-1; i++){
            copiere_date(repo1->oferte[i], repo1->oferte[i+1]);
        }
        distrugere_oferta(repo1->oferte[--repo1->numar_oferte_curente]);
        if(repo1->numar_oferte_curente < repo1->capacitate/2){
            redimensionare_in_jos(repo1);
        }
        return 0;
    }
    else{
        return 1;
    }
}

void distrugere_lista_oferta(repo * repo1){
    for(int i = 0; i <= repo1->numar_oferte_curente-1; i++){
        distrugere_oferta(repo1->oferte[i]);
    }
    repo1->numar_oferte_curente = 0;
    free(repo1->oferte);
}

int modify_oferta(repo * repo1, int index, oferta * oferta1){
    if(index >= 0 && index < repo1->numar_oferte_curente){
        copiere_date(repo1->oferte[index] , oferta1);
        return 0;
    }
    else{
        return 1;
    }
}

void test_add_delete_oferta(){
    repo * repo1 = malloc(1*sizeof (repo));
    creare_repository(repo1);
    assert(repo1->numar_oferte_curente == 0);

    data * data1 = malloc(sizeof (data));
    creare_data(data1, 12,3,2024);

    oferta * oferta1 = malloc(1*sizeof (oferta)) ;
    creare_oferta(oferta1, "Munte", "Fagaras", data1, 500);

    data * data2 = malloc(sizeof (data));
    creare_data(data2, 12,3,2024);

    oferta * oferta2 = malloc(1*sizeof (oferta));
    creare_oferta(oferta2,"Munte", "Fagaras", data2, 500);

    data * data3 = malloc(sizeof (data));
    creare_data(data3, 12,3,2024);

    oferta * oferta3 = malloc(1*sizeof (oferta));
    creare_oferta(oferta3,"City Break", "Paris", data3, 500);

    data * data4 = malloc(sizeof (data));
    creare_data(data4, 12,3,2024);

    oferta * oferta4 = malloc(1*sizeof (oferta));
    creare_oferta(oferta4,"Mare", "Costinesti", data4, 500);

    int status = add_oferta(repo1, oferta1);
    int status1 = add_oferta(repo1, oferta2);
    distrugere_oferta(oferta2);
    assert(status == 0);
    assert(status1 == 1);
    assert(repo1->numar_oferte_curente == 1);
    assert(verificare_egalitate(*repo1->oferte[0], *oferta1) == 1);

    add_oferta(repo1, oferta3);
    add_oferta(repo1, oferta4);

    assert(repo1->numar_oferte_curente == 3);
    assert(repo1->capacitate == 4);


    int status2 = delete_oferta(repo1, 4);
    assert(status2 == 1);

    status = delete_oferta(repo1, 0);
    delete_oferta(repo1,0);

    assert(status == 0);
    assert(repo1->numar_oferte_curente == 1);
    assert(repo1->capacitate == 2);



    distrugere_repository(repo1);
}



void test_modify_oferta(){
    repo * repo1 = malloc(sizeof (repo));
    creare_repository(repo1);
    assert(repo1->numar_oferte_curente == 0);
    data * data1 = malloc(sizeof(data));
    creare_data(data1, 12,3,2024);
    oferta * oferta1 = malloc(1*sizeof (oferta));
    creare_oferta(oferta1,"munte", "Fagaras", data1, 500);
    add_oferta(repo1, oferta1);


    data * data2 = malloc(sizeof(data));
    creare_data(data2, 20,5,2024);
    oferta * oferta2 = malloc(1*sizeof (oferta));
    creare_oferta(oferta2,"mare", "Costinesti", data2, 300);

    modify_oferta(repo1, 0, oferta2);
    assert(verificare_egalitate(*repo1->oferte[0], *oferta2) == 1);

    int status = modify_oferta(repo1, 1, oferta2);
    assert(status == 1);
    distrugere_repository(repo1);
    distrugere_oferta(oferta2);
}

void teste_repository(){
   test_add_delete_oferta();
   test_modify_oferta();
}
