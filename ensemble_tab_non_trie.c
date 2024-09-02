//
// Created by Antoine Meyer on 18/01/2022.
//

//  ./visites_uniques_tab_non_trie visites_court.log
//  ./visites_uniques_tab_non_trie visites_long.log

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ensemble.h"

#define TAILLE_INIT 10
#define COEF_TAILLE 2
#define SEUIL_REMPLISSAGE 4

struct Ensemble {
    long int *elems;
    int taille;
    int taille_max;
};

Ensemble* cree_ensemble() {
    Ensemble *res = malloc(sizeof(Ensemble));
    if (res == NULL)
        return NULL;
    res->elems = malloc(TAILLE_INIT * sizeof(long int));
    res->taille_max = TAILLE_INIT;
    res->taille = 0;
    return res;
}

void detruit_ensemble(Ensemble *ensemble) {
    free(ensemble->elems);
    free(ensemble);
}

int taille(const Ensemble *ensemble) {
    // complexité: O(1)
    return ensemble->taille;
}

int localise(const Ensemble *ensemble, long int element) {
    int i;
    for (i = 0; i < ensemble->taille; i++)
        if (ensemble->elems[i] == element)
            return i;
    return -1;
}

bool appartient(const Ensemble *ensemble, long int element) {
    // complexité: O(n)
    return localise(ensemble, element) >= 0;
}

bool redimensionne(Ensemble *ensemble, int taille) {
    long int *tmp = realloc(ensemble->elems,taille*sizeof(long int));
    if (tmp == NULL)
        return false;
    ensemble->elems = tmp;
    ensemble->taille_max = taille;
    return true;
}

int ajoute(Ensemble *ensemble, long int element) {
    // complexité: O(n)
    int i;
    if (appartient(ensemble, element))
        return 1;  /* élément déjà présent, pas d'ajout */
    if (ensemble->taille == ensemble->taille_max)
        if (!redimensionne(ensemble, ensemble->taille * COEF_TAILLE))
            return 2;  /* erreur d'allocation */
    ensemble->elems[ensemble->taille] = element;
    ensemble->taille++;
    return 0;
}

int supprime(Ensemble *ensemble, long int element) {
    int i = localise(ensemble, element);
    if (i < 0)
        return 1;  /* élément non présent, pas de suppression */
    if (ensemble->taille <= ensemble->taille_max / SEUIL_REMPLISSAGE)
        if (!redimensionne(ensemble, ensemble->taille_max / COEF_TAILLE))
            return 2;  /* erreur d'allocation */
    for (; i < ensemble->taille - 1; i++)
        ensemble->elems[i] = ensemble->elems[i + 1];
    ensemble->taille--;
    return 0;
}