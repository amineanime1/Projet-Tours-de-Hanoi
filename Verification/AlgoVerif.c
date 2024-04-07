#include <stdio.h>
#include <stdbool.h>

// Fonction pour vérifier si la solution des Tours de Hanoï est correcte
bool verifier_etat_final(int n, int tour_source[], int tour_target[], int tour_auxiliary[])
{
    // Vérifier si la tour source est vide
    for (int i = 1; i <= n; i++) {
        if (tour_source[i] != 0) {
            return false;
        }
    }

    // Vérifier si la tour auxiliaire est vide
    for (int i = 1; i <= n; i++) {
        if (tour_auxiliary[i] != 0) {
            return false;
        }
    }

    // Vérifier si la tour cible est ordonnée
    for (int i = 1; i <= n; i++) {
        if (tour_target[i] != i) {
            return false;
        }
    }

    return true; // La solution est correcte
}

int main()
{
    int n;
    printf("Entrez le nombre de disques : ");
    scanf("%d", &n);

    // Initialisation des tours
    int tour_source[n + 1], tour_target[n + 1], tour_auxiliary[n + 1];
    for (int i = 1; i <= n; i++) {
        tour_source[i] = i;
        tour_target[i] = 0;
        tour_auxiliary[i] = 0;
    }

    // Appel de la fonction de vérification
    bool solution_correcte = verifier_etat_final(n, tour_source, tour_target, tour_auxiliary);

    // Affichage du résultat de la vérification
    if (solution_correcte) {
        printf("La solution est correcte.\n");
    } else {
        printf("La solution est incorrecte.\n");
    }

    return 0;
}
