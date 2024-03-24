#include "UI.h"
#include "service.h"
#include "stdio.h"
#include "stdlib.h"



void add_oferta_UI(service * service1){
    char tip[30];
    char destinatie[30];
    char buffer;
    int an, luna, zi, pret;

    printf("Dati tipul ofertei(Mare/Munte/City Break): ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", tip);

    printf("Dati destinatia ofertei: ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", destinatie);

    printf("Dati anul datii de plecare a ofertei: ");
    scanf("%d", &an);

    printf("Dati luna datii de plecare a ofertei: ");
    scanf("%d", &luna);

    printf("Dati ziua datii de plecare a ofertei: ");
    scanf("%d", &zi);

    printf("Dati pretul ofertei: ");
    scanf("%d", &pret);

    int status = adaugare_oferta(service1,tip,destinatie,an,luna,zi,pret);

    if(status != 0){
        if(status == 1){
            printf("Exista deja aceasta oferta!\n");
        }
        else if(status == 2){
            printf("Date de intrare invalide!\n");
        }
    }
    else{
        printf("Adaugare reusita!\n");
    }

}

void del_oferta_UI(service * service1){

    int index;
    printf("Dati numarul ofertei pe care doriti sa o stergeti: ");
    scanf("%d", &index);

    int status = stergere_oferta(service1, index);

    if (status != 0){
        printf("Nu exista o oferta pe aceasta pozitie!\n");
    }
    else{
        printf("Stergere efectuata!\n");
    }

}

void modif_oferta_UI(service * service1){
    char tip[30];
    char destinatie[30];
    char buffer;
    int an, luna, zi, pret;
    int index;

    printf("Dati numarul ofertei pe care doriti sa o modificati: ");
    scanf("%d", &index);

    printf("Dati noul tip al ofertei(Mare/Munte/City Break): ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", tip);

    printf("Dati noua destinatie a ofertei: ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", destinatie);

    printf("Dati noul an al datii de plecare a ofertei: ");
    scanf("%d", &an);

    printf("Dati noua luna a datii de plecare a ofertei: ");
    scanf("%d", &luna);

    printf("Dati noua zi a datii de plecare a ofertei: ");
    scanf("%d", &zi);

    printf("Dati noul pret al ofertei: ");
    scanf("%d", &pret);

    int status = modificare_oferta(service1,index,tip,destinatie,an,luna,zi,pret);

    if(status != 0){
        if(status == 1){
            printf("Nu exista o oferta pe aceasta pozitie!\n");
        }
        else if(status == 2){
            printf("Date de intrare invalide!\n");
        }
    }
    else{
        printf("Modificare reusita!\n");
    }
}

void filtru_destinatie_UI(service * service1){
    oferta **oferte= malloc(service1->repository->numar_oferte_curente* sizeof(oferta*));
    for(int i = 0; i < service1->repository->numar_oferte_curente ; i++){
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        oferte[i] = malloc(sizeof(oferta));
        creare_oferta(oferte[i],"1","1",data1,1);
    }
    char buffer;
    char destinatie[30];

    printf("Dati destinatia dupa care doriti sa se filtreze ofertele: ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", destinatie);

    int numar_oferte_gasite = filtru_destinatie(service1, destinatie, oferte);

    if(numar_oferte_gasite != 0) {
        for (int i = 0; i < numar_oferte_gasite; i++) {
            printf("%d: %s %s %d.%d.%d %d lei\n", i, oferte[i]->tip, oferte[i]->destinatie, oferte[i]->data_plecare->zi,
                   oferte[i]->data_plecare->luna, oferte[i]->data_plecare->an, oferte[i]->pret);
        }
    }
    else{
        printf("Nu s-a gasit nicio oferta corespunzatoare!\n");
    }
    for(int i = 0; i < service1->repository->numar_oferte_curente ; i++){
        distrugere_oferta(oferte[i]);
    }
    free(oferte);
}


void filtru_pret_UI(service *service1){
    oferta **oferte= malloc(service1->repository->numar_oferte_curente* sizeof(oferta*));
    for(int i = 0; i < service1->repository->numar_oferte_curente ; i++){
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        oferte[i] = malloc(sizeof(oferta));
        creare_oferta(oferte[i],"1","1",data1,1);
    }
    int  pret;

    printf("Dati pretul maxim pe care il doriti de la oferte: ");
    scanf("%d", &pret);

    int numar_oferte_gasite = filtru_pret(service1, pret, oferte);

    if(numar_oferte_gasite != 0) {
        for (int i = 0; i < numar_oferte_gasite; i++) {
            printf("%d: %s %s %d.%d.%d %d lei\n", i, oferte[i]->tip, oferte[i]->destinatie, oferte[i]->data_plecare->zi,
                   oferte[i]->data_plecare->luna, oferte[i]->data_plecare->an, oferte[i]->pret);
        }
    }
    else{
        printf("Nu s-a gasit nicio oferta corespunzatoare!\n");
    }
    for(int i = 0; i < service1->repository->numar_oferte_curente ; i++){
        distrugere_oferta(oferte[i]);
    }
    free(oferte);
}

void filtru_tip_UI(service * service1){
    oferta **oferte = malloc(service1->repository->numar_oferte_curente* sizeof(oferta*));
    for(int i = 0; i < service1->repository->numar_oferte_curente ; i++){
        data * data1 = malloc(sizeof(data));
        creare_data(data1,1,1,1);
        oferte[i] = malloc(sizeof(oferta));
        creare_oferta(oferte[i],"1","1",data1,1);
    }
    char buffer;
    char tip[30];

    printf("Dati tipul dupa care doriti sa se filtreze ofertele: ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", tip);

    int numar_oferte_gasite = filtru_tip(service1, tip, oferte);

    if(numar_oferte_gasite != 0) {
        for (int i = 0; i < numar_oferte_gasite; i++) {
            printf("%d: %s %s %d.%d.%d %d lei\n", i, oferte[i]->tip, oferte[i]->destinatie, oferte[i]->data_plecare->zi,
                   oferte[i]->data_plecare->luna, oferte[i]->data_plecare->an, oferte[i]->pret);
        }
    }
    else{
        printf("Nu s-a gasit nicio oferta corespunzatoare!\n");
    }
    for(int i = 0; i < service1->repository->numar_oferte_curente ; i++){
        distrugere_oferta(oferte[i]);
    }
    free(oferte);
}

void sortare_UI(service * service1){
    char directie[30];
    char buffer;
    printf("Doriti sortare crescatoare sau descrescatoare?: ");
    scanf("%c", &buffer);
    scanf("%[^\n]s", directie);
    int status = sortare(service1, directie,verificare_conditie_sortare_pret,verificare_conditie_sortare_destinatie);
    if(status == 0) {
        for (int i = 0; i < service1->repository->numar_oferte_curente; i++) {
            printf("%d: %s %s %d.%d.%d %d lei\n", i, service1->repository->oferte[i]->tip,
                   service1->repository->oferte[i]->destinatie, service1->repository->oferte[i]->data_plecare->zi,
                   service1->repository->oferte[i]->data_plecare->luna,
                   service1->repository->oferte[i]->data_plecare->an,
                   service1->repository->oferte[i]->pret);
        }
    }
    else{
        printf("Nu se poate efectua sortarea!\n");
    }

}

void toate_ofertele(service service1){
    if(service1.repository->numar_oferte_curente > 0) {
        for (int i = 0; i < service1.repository->numar_oferte_curente; i++) {
            printf("%d: %s %s %d.%d.%d %d lei\n", i, service1.repository->oferte[i]->tip,
                   service1.repository->oferte[i]->destinatie, service1.repository->oferte[i]->data_plecare->zi,
                   service1.repository->oferte[i]->data_plecare->luna,
                   service1.repository->oferte[i]->data_plecare->an,
                   service1.repository->oferte[i]->pret);
        }
    }
    else{
        printf("Nu exista oferte disponibile!\n");
    }


}


void run(){
    repo * repository = malloc(sizeof(repo));
    creare_repository(repository);
    service*  service1 = malloc(sizeof(service));
    creare_service(service1, repository);
    int still_running = 1;
    while (still_running){
        printf("1: Adaugare oferta\n2: Stergere oferta\n3: Modificare oferta\n");
        printf("4: Filtru dupa destinatie\n5: Filtru dupa pret\n6: Filtru dupa tip\n");
        printf("7: Sortare dupa pret si destinatie\n8: Afisare oferte disponibile\n0: Iesire\nOptiunea: ");
        int optiune = 0;
        scanf("%d", &optiune);
        switch (optiune) {
            case 1:
                add_oferta_UI(service1);
                break;
            case 2:
                del_oferta_UI(service1);
                break;
            case 3:
                modif_oferta_UI(service1);
                break;
            case 4:
                filtru_destinatie_UI(service1);
                break;
            case 5:
                filtru_pret_UI(service1);
                break;
            case 6:
                filtru_tip_UI(service1);
                break;
            case 7:
                sortare_UI(service1);
                break;
            case 8:
                toate_ofertele(*service1);
                break;
            case 0:
                still_running = 0;
                break;
            default:
                printf("Optiune Invalida!\n");

        }
    }
    distrugere_service(service1);
}
