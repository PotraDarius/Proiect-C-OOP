#pragma once
#include "domain.h"

typedef struct {
    oferta * * oferte;
    int numar_oferte_curente;
    int capacitate;
}repo;

/* functie ce creeaza un repository
 *
 * output: repository1 - repository
 *
 */
void creare_repository(repo * repo1);

void distrugere_repository(repo * repo1);

void distrugere_lista_oferta(repo * repo1);

void copiere_date(oferta * oferta1, oferta * oferta2);


/* functie ce aloca un spatiu de memorie dublu listei de oferte dintr-un repository
 *
 * input: repo1 - repo
 *
 */
void redimensionare_in_sus(repo *  repo1);

/* functie ce elibereaza memoria listei de oferte dintr-un repository
 *
 * input: repo1 - repo
 *
 */
void redimensionare_in_jos(repo *  repo1);

/* functie ce adauga o oferta in lista de oferte
 * input: repo1 - repo
 *        oferta1 - oferta
 * output: 1 - exista deja aceasta oferta
 *         0 - adaugare reusita
 *
 */
int add_oferta(repo *  repo1, oferta * oferta1);


/* functie ce sterge o oferta din lista de oferte
 * input: repo1 - repo
 *        index - int
 * output: 1 - index este negativ sau index < numar de oferte curent ( nu exista o oferta pe aceasta pozitie)
 *         0 - stergere reusita
 *
 */
int delete_oferta(repo *  repo1, int index);

/* functie ce actualizeaza o oferta din lista de oferte
 * input: repo1 - repo
 *        index - int
 *        oferta1 - oferta
 * output: 1 - index este negativ sau index < numar de oferte curent ( nu exista o oferta pe aceasta pozitie)
 *         0 - modificare reusita
 */
int modify_oferta(repo * repo1, int index, oferta * oferta1);




void test_add_delete_oferta();
void test_delete_oferta();
void test_modify_oferta();
void teste_repository();