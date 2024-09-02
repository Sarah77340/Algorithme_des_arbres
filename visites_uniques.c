#include <stdio.h>
#include <stdlib.h>
#include "ensemble.h"

long int encode_ip(char *ip) {
	unsigned char b1, b2, b3, b4;
    long int res;
	if (sscanf(ip, "%hhd.%hhd.%hhd.%hhd", &b1, &b2, &b3, &b4) == 4) {
        res = b1;
        res = 256*res + b2;
        res = 256*res + b3;
        res = 256*res + b4;
        return res;
    }
	return -1;
}

char* decode_ip(long int n) {
	if (n == -1)
		return "adresse ip incorrecte";
	unsigned char b1, b2, b3, b4;
	b4 = n % 256;
	n /= 256;
	b3 = n % 256;
	n /= 256;
	b2 = n % 256;
	b1 = n / 256;
	char *res = malloc(16 * sizeof(char));
	sprintf(res, "%d.%d.%d.%d", b1, b2, b3, b4);
	return res;
}

FILE *ouvre_fichier(const char *chemin) {
    FILE *df = fopen(chemin, "r");
    if (df == NULL) {
        fprintf(stderr, "impossible d'ouvrir %s", chemin);
        exit(1);
    }
    return df;
}

void verifie_appel(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage : %s <fichier à lire>", argv[0]);
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    verifie_appel(argc, argv);
    FILE *df = ouvre_fichier(argv[1]);

	Ensemble *a = cree_ensemble();
    char ip[16];
    while (fscanf(df, "%*d %s", ip) == 1) { /* on jette le timestamp avec %*d */
		long int n = encode_ip(ip);
		if (!appartient(a, n)) {
			ajoute(a, n);
		}
	}
    fclose(df);
    
	printf("trouvé %d ip différentes\n", taille(a));
    detruit_ensemble(a);

    return 0;
}