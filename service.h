#pragma once
#include "repository.h"
#include "validator.h"

typedef struct {
    repo * repository;
}service;



/* functie ce initializeaza o variabila de tipul service
 * input: repository - repo *
 *
 * output: service - service
 *
 */
void creare_service(service * service1, repo * repository);

/* functie ce creeaza, valideaza si adauga o oferta in lista de oferte
 * input : service1 - service *
 *         tip - char *
 *         destinatie - char *
 *         an - int
 *         luna - int
 *         zi - int
 *         pret - int
 * output: nenul - nu s-a putut efectua adaugarea
 *         nul - operatie efectuata cu succes
 *
 */
int adaugare_oferta(service * service1, char * tip, char * destinatie, int an, int luna, int zi, int pret);

/* functie ce sterge o oferta de pe o pozitie data sin lista de oferte
 * input : service1 - service *
 *         index - int
 * output: nenul - nu s-a putut efectua stergerea
 *         nul - operatie efectuata cu succes
 *
 */
int stergere_oferta(service * service1, int index);


/* functie ce modifica o oferta de pe o pozitie data din lista de oferte
 * input : service1 - service *
 *         tip - char *
 *         destinatie - char *
 *         an - int
 *         luna - int
 *         zi - int
 *         pret - int
 * output: nenul - nu s-a putut efectua modificarea
 *         nul - operatie efectuata cu succes
 *
 */
int modificare_oferta(service * service1, int index, char * tip, char * destinatie, int an, int luna, int zi, int pret);


/* functie ce filtreaza lista de oferte dupa o anumita destinatie
 * input: service1 - service *
 *        destinatie - char *
 *        filtru - oferta *
 * output: nenul - functia nu a gasit nicio oferta corespunzatoare
 *         nul - toate ofertele gasite vor fi in lista filtru
 *
 */
int  filtru_destinatie(service * service1, char * destinatie,oferta ** filtru);

/* functie ce filtreaza lista de oferte dupa o anumit pret maxim
 * input: service1 - service *
 *        pret - int
 *        filtru - oferta *
 * output: nenul - functia nu a gasit nicio oferta corespunzatoare
 *         nul - toate ofertele gasite vor fi in lista filtru
 *
 */
int  filtru_pret(service * service1, int pret,oferta ** filtru);

/* functie ce filtreaza lista de oferte dupa un anumit tip
 * input: service1 - service *
 *        tip - char *
 *        filtru - oferta *
 * output: nenul - functia nu a gasit nicio oferta corespunzatoare
 *         nul - toate ofertele gasite vor fi in lista filtru
 *
 */
int  filtru_tip(service * service1, char * tip,oferta ** filtru);


/* functie ce sorteaza crescator sau descrescator dupa pret si destinatie lista de oferte
 * input : service1 - service *
 *         directie - char *
 * output: nenul - nu s-a putut efectua sortarea
 *         nul - lista a fost sortata cu succes
 *
 */
int sortare(service * service1, char * directie,int(*cmp1)(), int (*cmp2)());

/* functie ce verifica legatura dintre doua oferte dupa destinatie
 * input: oferta1 - oferta
 *        oferta2 - oferta
 *        directie - char *
 *  output : 1 - conditie satisfacuta
 *           0 - altfel
 *
 */
int verificare_conditie_sortare_destinatie(oferta  oferta1, oferta oferta2, char * directie);

/* functie ce sorteaza o lista de oferta crescator sau descrescator dupa destinatie
 * input: oferte - oferta *
 *        inceput - int
 *        lungime - int
 *        directie - char *
 *
 * output: 0 - sortare finalizata
 *
 */
int sortare_dupa_destinatie(oferta ** oferte,int inceput, int lungime,  char * directie,int (*cmp2)(oferta oferta1, oferta oferta2, char * destinatie));

/* functie ce verifica legatura dintre doua oferte dupa pret
 * input: oferta1 - oferta
 *        oferta2 - oferta
 *        directie - char *
 *  output : 1 - conditie satisfacuta
 *           0 - altfel
 *
 */
int verificare_conditie_sortare_pret(oferta oferta1, oferta oferta2, char * directie);


void distrugere_service(service * service1);

void test_adaugare_oferta();
void test_stergere_oferta();
void test_modificare_oferta();
void test_filtru_destinatie();
void test_filtru_pret();
void test_filtru_tip();
void test_sortare_dupa_pret_si_destinatie();

void teste_service();