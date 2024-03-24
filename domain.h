#pragma once

typedef struct{
    int  zi;
    int luna;
    int an;
}data;

typedef struct{
    char * tip;
    char * destinatie;
    data * data_plecare;
    int  pret;
}oferta;



/* functie ce creeaza o oferta
 * input: tip - char * nevid
 *        destinatie - char * nevid
 *        data_plecare - char * nevid
 *        pret - int pozitiv nenu;
 * output: oferta - de tip oferta
 * */
void  creare_oferta(oferta * oferta1, char * tip, char * destinatie, data * data_plecare, int pret);



/* functie ce creeaza o data
 * input : zi - int
 *         luna - int
 *         an - int
 * output : data - data
 *
 */
void creare_data(data* data1, int zi, int luna, int an);




/* functie ce verifica daca doua date sunt egale
 *
 * input: data1 - data
 *         data2 - data
 *
 * output: 1 - data1 == data2
 *         0 - altfel
 */
int verificare_egalitate_data(data data1, data data2);


/* functie ce verifica egalitatea dintre doua oferte
 * input: oferta1 - oferta
 *        oferta2 - oferta
 * output: 1 - oferta1 == oferta2
 *         0 - altfel
 *
 */
int verificare_egalitate(oferta oferta1, oferta oferta2);


/*
 * functie ce "distruge" o oferta, fiecare atribut al ofertei devenin neutilizabil
 * input: oferta1 - oferta
 */
void distrugere_oferta(oferta * oferta1);


void test_creare_si_distrugere();
void test_verificare_egalitate_data();
void test_verificare_egalitate_oferta();
void teste_domain();

