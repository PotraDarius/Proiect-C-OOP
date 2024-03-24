#pragma once
#include "domain.h"

typedef int Validator;


/* functie ce valideaza o oferta data
 * input: oferta1 - oferta
 * output: 2 - tipul este nul, destinatie este nula, data plecarii nu este valida, pretul este negativ sau nul
 *         0 - oferta este valida
 *
 */
Validator validare_oferta(oferta oferta1);


/* functie ce valideaza o data
 * input: data1 - data
 *
 * output: 1 - ziua este negativa sau nula sau mai mare decat 31, luna este negativa sau nula sau mai mare decat 12,
 *             anul este negativ sau nul
 *
 *         0 - altfel
 *
 */
Validator validare_data(data data1);

void test_validare_oferta();

void test_validare_data();

void teste_validator();