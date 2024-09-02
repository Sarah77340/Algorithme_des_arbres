#include <stdbool.h>

typedef struct Ensemble Ensemble;

Ensemble* cree_ensemble();
void detruit_ensemble(Ensemble *ensemble);
int taille(const Ensemble *ensemble);
bool appartient(const Ensemble *ensemble, long int element);
int ajoute(Ensemble *ensemble, long int element);
int supprime(Ensemble *ensemble, long int element);
