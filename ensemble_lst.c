//
// Created by Antoine Meyer on 18/01/2022.
//

//  ./visites_uniques_lst visites_court.log
//  ./visites_uniques_lst visites_long.log

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ensemble.h"

typedef struct cellule {
    long int valeur;
    struct cellule *suivant;
} Cellule;

struct Ensemble {
    Cellule *premier;
    int taille;
};

Cellule* cree_cellule(long int elem) {
    Cellule *res = malloc(sizeof(Cellule));
    res->valeur = elem;
    res->suivant = NULL;
    return res;
}

void detruit_cellule(Cellule *cellule) {
    free(cellule);
}

Ensemble* cree_ensemble() {
    // complexité: 0(1)
    Ensemble *tmp = malloc(sizeof(struct Ensemble));
    tmp->premier = NULL;
    tmp->taille = 0;
    return tmp;
}

void detruit_ensemble(Ensemble *ens) {
    Cellule *courant, *suivant;
    courant = ens->premier;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    free(ens);
}

Cellule* trouve_cellule(Cellule *cellule, long int elem) {
    if (!cellule)
        return NULL;
    if (cellule->valeur == elem)
        return cellule;
    else
        return trouve_cellule(cellule->suivant, elem);
}

bool appartient(const Ensemble *ens, long int elem) {
    // complexité: O(n)
    Cellule* resultat = trouve_cellule(ens->premier, elem);
    if (resultat == NULL)
        return false;
    else
        return true;
}

int ajoute(Ensemble *ens, long int elem) {
    // complexité O(n)
    if (appartient(ens, elem) == true) //element deja dans ens
        return 1;
    Cellule* tmp = cree_cellule(elem);
    tmp->suivant = ens->premier;
    ens->premier = tmp;
    ens->taille += 1;
    return 0;
}

int taille(const Ensemble *ens) {
    // complexité O(1)
    return ens->taille;
}