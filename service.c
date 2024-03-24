#include "service.h"
#include "assert.h"
#include "string.h"
#include "stdlib.h"


void  creare_service(service * service1, repo * repository){
    service1->repository =  repository;
}

void distrugere_service(service * service1){
    distrugere_repository(service1->repository);
    free(service1);
}


int adaugare_oferta(service * service1, char * tip, char * destinatie, int an, int luna, int zi, int pret){
    data * data_plecare = malloc(sizeof(data));
    creare_data(data_plecare, zi, luna, an);
    oferta * oferta1 = malloc(sizeof (oferta));
    creare_oferta(oferta1, tip, destinatie, data_plecare, pret);
    int status_validare = validare_oferta(*oferta1);
    if(status_validare == 0){
        int status = add_oferta(service1->repository, oferta1);
        return status;
    }
    else{
        distrugere_oferta(oferta1);
        return status_validare;
    }
}


int stergere_oferta(service * service1, int index){
    int status = delete_oferta( service1->repository, index);
    return status;
}

int modificare_oferta(service * service1, int index, char * tip, char * destinatie, int an, int luna, int zi, int pret){
    data * data_plecare = malloc(sizeof(data));
    creare_data(data_plecare, zi, luna, an);

    oferta * oferta1 = malloc(sizeof (oferta));
    creare_oferta(oferta1, tip, destinatie, data_plecare, pret);

    int status_validare = validare_oferta(*oferta1);
    if(status_validare == 0){
        int status = modify_oferta(service1->repository,index ,oferta1);
        distrugere_oferta(oferta1);
        return status;
    }
    else{
        distrugere_oferta(oferta1);
        return status_validare;
    }
}





int  filtru_destinatie(service * service1, char * destinatie, oferta ** filtru){
    int numar_oferte_gasite = 0;
    for(int i = 0; i < service1->repository->numar_oferte_curente; i++){
        if(strcmp(service1->repository->oferte[i]->destinatie, destinatie) == 0){
            copiere_date(filtru[numar_oferte_gasite] , service1->repository->oferte[i]);
            numar_oferte_gasite ++;
        }
    }
    return numar_oferte_gasite;
}

int  filtru_pret(service * service1, int pret, oferta ** filtru){
    int numar_oferte_gasite = 0;
    for(int i = 0; i < service1->repository->numar_oferte_curente; i++){
        if(service1->repository->oferte[i]->pret <= pret){
            copiere_date(filtru[numar_oferte_gasite] , service1->repository->oferte[i]);
            numar_oferte_gasite ++;
        }
    }
    return numar_oferte_gasite;
}



int  filtru_tip(service * service1, char * tip, oferta ** filtru){


    int numar_oferte_gasite = 0;
    for(int i = 0; i < service1->repository->numar_oferte_curente; i++){
        if(strcmp(service1->repository->oferte[i]->tip, tip) == 0){
            copiere_date(filtru[numar_oferte_gasite] , service1->repository->oferte[i]);
            numar_oferte_gasite ++;
        }
    }
    return numar_oferte_gasite;
}

int verificare_conditie_sortare_pret(oferta oferta1, oferta oferta2, char * directie){
    if(strcmp(directie,"crescator") == 0){
        if (oferta1.pret > oferta2.pret){
            return 1;
        }
        return 0;
    }
    else if(strcmp(directie, "descrescator") == 0){
        if (oferta1.pret < oferta2.pret){
            return 1;
        }
        return 0;
    }
    return 0;
}

int verificare_conditie_sortare_destinatie(oferta oferta1, oferta oferta2, char * directie){
    if(strcmp(directie,"crescator") == 0){
        if (strcmp(oferta1.destinatie, oferta2.destinatie) > 0){
            return 1;
        }
        return 0;
    }
    else if(strcmp(directie, "descrescator") == 0){
        if (strcmp(oferta1.destinatie, oferta2.destinatie) < 0){
            return 1;
        }
        return 0;
    }
    return 0;
}

int sortare_dupa_destinatie(oferta * * oferte,int inceput, int lungime, char * directie,
                            int (*cmp2)(oferta oferta1, oferta oferta2, char * destinatie)){
    oferta * aux = malloc(sizeof (oferta));
    data * data1 = malloc(sizeof(data));
    creare_data(data1,1,1,1);
    creare_oferta(aux,"1","1",data1,1);
    for (int i = inceput; i < lungime - 1; i++) {
        for (int j = i + 1; j < lungime; j++) {
            if (cmp2(*oferte[i], *oferte[j],directie) == 1) {
                copiere_date(aux , oferte[i]);
                copiere_date(oferte[i] , oferte[j]);
                copiere_date(oferte[j] , aux);
            }
        }
    }
    distrugere_oferta(aux);
    return 0;
}

int sortare(service * service1, char * directie, int(*cmp1)(oferta oferta1, oferta oferta2, char * destinatie),
            int (*cmp2)(oferta oferta1, oferta oferta2, char * destinatie)){
    if(service1->repository->numar_oferte_curente > 0) {
        oferta * aux_var = malloc(sizeof (oferta));
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        creare_oferta(aux_var,"1","1",data1,1);
        for (int i = 0; i < service1->repository->numar_oferte_curente - 1; i++) {
            for (int j = i + 1; j < service1->repository->numar_oferte_curente; j++) {
                if (cmp1(*service1->repository->oferte[i], *service1->repository->oferte[j],
                                                     directie) == 1) {

                    copiere_date(aux_var, service1->repository->oferte[i]);
                    copiere_date(service1->repository->oferte[i], service1->repository->oferte[j]);
                    copiere_date(service1->repository->oferte[j], aux_var);
                }
            }
        }
        distrugere_oferta(aux_var);
        oferta **aux= malloc(service1->repository->numar_oferte_curente * sizeof(oferta*));
        for(int i = 0; i < service1->repository->numar_oferte_curente; i++){
            data * data2 = malloc(sizeof(data));
            creare_data(data2,1,1,1);
            aux[i] = malloc(sizeof(oferta));
            creare_oferta(aux[i],"1ftgshfhg","1sfghdsdfh",data2,1);
        }
        int index_sfarsit_aux = 0;
        int index_inceput_aux = 0;
        int pret_initial = service1->repository->oferte[0]->pret;
        for (int i = 0; i < service1->repository->numar_oferte_curente; i++) {
                if(service1->repository->oferte[i]->pret == pret_initial){
                    copiere_date(aux[index_sfarsit_aux++] , service1->repository->oferte[i]);
                }
                else{
                    sortare_dupa_destinatie(aux,index_inceput_aux, index_sfarsit_aux,directie,cmp2);
                    for(int j = index_inceput_aux; j < index_sfarsit_aux; j++){
                        copiere_date(service1->repository->oferte[j] , aux[j]);
                    }
                    index_inceput_aux = index_sfarsit_aux;
                    pret_initial = service1->repository->oferte[i]->pret;
                    copiere_date(aux[index_sfarsit_aux++] , service1->repository->oferte[i]);
                }
        }
        sortare_dupa_destinatie(aux, index_inceput_aux,index_sfarsit_aux,directie,cmp2);
        for(int j = index_inceput_aux; j < index_sfarsit_aux; j++){
            copiere_date(service1->repository->oferte[j] , aux[j]);
        }
        for(int i = 0; i < service1->repository->numar_oferte_curente; i++){
            distrugere_oferta(aux[i]);
        }
        free(aux);
        return 0;
    }
    else{
        return 1;
    }
}


void test_filtru_destinatie(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));

    creare_service(service1, repo1);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);
    adaugare_oferta(service1,"Munte", "Himalaya", 2024, 5,17, 700);
    oferta * * filtru = malloc(service1->repository->capacitate * sizeof(oferta*));

    for(int i = 0; i < service1->repository->capacitate ; i++){
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        filtru[i] = malloc(sizeof(oferta));
        creare_oferta(filtru[i],"","",data1,1);
    }

    int numar_oferte_filtru = filtru_destinatie(service1, "Fagaras", filtru);

    data *data1 = malloc(sizeof(data));
    creare_data(data1,12,4,2024);

    oferta  *oferta1 = malloc(sizeof(oferta));
    creare_oferta(oferta1, "Munte", "Fagaras", data1, 500);

    assert(numar_oferte_filtru == 1);
    assert(verificare_egalitate(*filtru[0], *oferta1) == 1);

    for(int i = 0; i < service1->repository->capacitate ; i++){
        distrugere_oferta(filtru[i]);
    }
    free(filtru);

    distrugere_oferta(oferta1);
    distrugere_service(service1);


}

void test_filtru_pret(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));

    creare_service(service1, repo1);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);
    adaugare_oferta(service1,"Munte", "Himalaya", 2024, 5,17, 700);
    oferta * * filtru = malloc(service1->repository->capacitate * sizeof(oferta*));

    for(int i = 0; i < service1->repository->capacitate ; i++){
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        filtru[i] = malloc(sizeof(oferta));
        creare_oferta(filtru[i],"","",data1,1);
    }


    int numar_oferte_filtru = filtru_pret(service1, 600, filtru);


    data * data1 = malloc(sizeof(data));
    creare_data(data1,12,4,2024);
    oferta *oferta1 = malloc(sizeof(oferta));
    creare_oferta(oferta1,"Munte", "Fagaras", data1, 500);
    assert(numar_oferte_filtru == 1);
    assert(verificare_egalitate(*filtru[0], *oferta1) == 1);

    for(int i = 0; i < service1->repository->capacitate ; i++){
        distrugere_oferta(filtru[i]);
    }
    free(filtru);

    distrugere_oferta(oferta1);
    distrugere_service(service1);

}

void test_filtru_tip(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));

    creare_service(service1, repo1);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);
    adaugare_oferta(service1,"Mare", "Costinesti", 2024, 5,17, 700);

    oferta * * filtru = malloc(service1->repository->capacitate * sizeof(oferta*));

    for(int i = 0; i < service1->repository->capacitate ; i++){
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        filtru[i] = malloc(sizeof(oferta));
        creare_oferta(filtru[i],"1","1",data1,1);
    }
    int numar_oferte_filtru = filtru_tip(service1, "Mare", filtru);


    data * data1 = malloc(sizeof(data));
    creare_data(data1, 17,5,2024);
    oferta *oferta1 = malloc(sizeof(oferta));
    creare_oferta(oferta1,"Mare", "Costinesti", data1, 700);

    assert(numar_oferte_filtru == 1);
    assert(verificare_egalitate(*filtru[0], *oferta1) == 1);

    for(int i = 0; i < service1->repository->capacitate ; i++){
        distrugere_oferta(filtru[i]);
    }
    free(filtru);

    distrugere_oferta(oferta1);
    distrugere_service(service1);
}


void test_sortare_dupa_pret_si_destinatie(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));

    creare_service(service1, repo1);

    repo * repo2 = malloc(sizeof(repo));
    creare_repository(repo2);

    service * service2 = malloc(sizeof(service));

    creare_service(service2, repo2);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);
    adaugare_oferta(service1, "Munte", "Arabia Saudita", 2024, 4,12, 500);
    adaugare_oferta(service1, "Munte", "Costinesti", 2024, 4,12, 700);
    adaugare_oferta(service1, "Munte", "Dolomiti", 2024, 4,12, 500);
    adaugare_oferta(service1, "Munte", "Cluj", 2024, 4,12, 600);
    sortare(service1,"crescator",verificare_conditie_sortare_pret, verificare_conditie_sortare_destinatie);
    assert(strcmp(service1->repository->oferte[0]->destinatie,"Arabia Saudita") == 0);
    assert(strcmp(service1->repository->oferte[1]->destinatie,"Dolomiti") == 0);
    assert(strcmp(service1->repository->oferte[2]->destinatie,"Fagaras") == 0);
    assert(strcmp(service1->repository->oferte[3]->destinatie,"Cluj") == 0);
    assert(strcmp(service1->repository->oferte[4]->destinatie,"Costinesti") == 0);

    sortare(service1, "descrescator", verificare_conditie_sortare_pret, verificare_conditie_sortare_destinatie);
    assert(strcmp(service1->repository->oferte[0]->destinatie,"Costinesti") == 0);
    assert(strcmp(service1->repository->oferte[1]->destinatie,"Cluj") == 0);
    assert(strcmp(service1->repository->oferte[2]->destinatie,"Fagaras") == 0);
    assert(strcmp(service1->repository->oferte[3]->destinatie,"Dolomiti") == 0);
    assert(strcmp(service1->repository->oferte[4]->destinatie,"Arabia Saudita") == 0);

    int status1 = sortare(service2, "crescator",verificare_conditie_sortare_pret,verificare_conditie_sortare_destinatie);
    assert(status1 == 1);


    data *data1 = malloc(sizeof(data));
    creare_data(data1,12,12,2024);

    oferta *oferta1 = malloc(sizeof(oferta));
    creare_oferta(oferta1,"Munte", "Fagaras", data1, 500);

    data *data2 = malloc(sizeof(data));
    creare_data(data2,12,12,2024);

    oferta *oferta2 = malloc(sizeof(oferta));
    creare_oferta(oferta2, "Mare", "Costinesti", data2, 700);

    int status = verificare_conditie_sortare_destinatie(*oferta1,*oferta2, "");
    assert(status == 0);

    status = verificare_conditie_sortare_pret(*oferta1,*oferta2, "");
    assert(status == 0);

    distrugere_oferta(oferta1);
    distrugere_oferta(oferta2);

    distrugere_service(service1);
    distrugere_service(service2);
}

void test_adaugare_oferta(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));

    creare_service(service1, repo1);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);

    data  * data1 = malloc(sizeof(data));
    creare_data(data1, 12,4,2024);

    oferta * oferta1 = malloc(sizeof(oferta));
    creare_oferta(oferta1, "Munte", "Fagaras", data1, 500);

    assert(service1->repository->numar_oferte_curente == 1);
    assert(verificare_egalitate(*service1->repository->oferte[0], *oferta1) == 1);

    int status = adaugare_oferta(service1, "munte", "Fagaras", 2024,4,12,500);
    assert(status == 2);
    distrugere_oferta(oferta1);
    distrugere_service(service1);
}



void test_stergere_oferta(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));
    creare_service(service1,repo1);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);
    assert(service1->repository->numar_oferte_curente == 1);

    stergere_oferta(service1, 0);
    assert(service1->repository->numar_oferte_curente == 0);

    distrugere_service(service1);

}

void test_modificare_oferta(){
    repo * repo1 = malloc(sizeof(repo));
    creare_repository(repo1);

    service * service1 = malloc(sizeof(service));
    creare_service(service1,repo1);

    adaugare_oferta(service1, "Munte", "Fagaras", 2024, 4,12, 500);

    data *data1 = malloc(sizeof(data));
    creare_data(data1, 7,4,2023);

    oferta * oferta1 = malloc(sizeof(oferta));
    creare_oferta(oferta1, "Mare", "Costinesti", data1, 400);

    modificare_oferta(service1,0, "Mare", "Costinesti", 2023,4,7,400);
    assert(verificare_egalitate(*service1->repository->oferte[0], *oferta1) == 1);

    int status = modificare_oferta(service1, 0, "munte", "Fagaras", 2024, 4, 12, 500);
    assert(status == 2);

    distrugere_oferta(oferta1);
    distrugere_service(service1);
}

void teste_service(){
    test_adaugare_oferta();
    test_stergere_oferta();
    test_modificare_oferta();
    test_filtru_destinatie();
    test_filtru_pret();
    test_filtru_tip();
    test_sortare_dupa_pret_si_destinatie();
}
