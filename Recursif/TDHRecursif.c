#include <stdio.h>
#include <time.h> // Ajout de la bibliothèque pour la gestion du temps

// Fonction pour résoudre les Tours de Hanoï et calculer le nombre de déplacements
int hanoi(int n, char source, char target, char auxiliary) {
    if (n == 1) {
        printf("D%cplacer le disque 1 de %c vers %c\n", 130, source, target);
        return 1; // Un déplacement pour un disque
    } else {
        int moves = 0;
        // Déplacer n-1 disques de la source à l'auxiliaire en utilisant la tour cible comme tampon
        moves += hanoi(n-1, source, auxiliary, target);
        
        // Déplacer le disque le plus grand de la source à la cible
        printf("D%cplacer le disque %d de %c vers %c\n", 130,n, source, target);
        moves++; // Ajouter un déplacement
        
        // Déplacer n-1 disques de l'auxiliaire à la cible en utilisant la tour source comme tampon
        moves += hanoi(n-1, auxiliary, target, source);
        
        return moves;
    }
}

int main() {
    int n;
    printf("R%ccursif // Entrez le nombre de disques : ",130);
    scanf("%d", &n);
    
    clock_t start, end; // Déclaration de variables pour mesurer le temps
    double cpu_time_used; // Variable pour stocker le temps d'exécution
    
    start = clock(); // Début du comptage du temps
    
    // Appel de la fonction hanoi pour résoudre le problème et récupérer le nombre de déplacements
    int total_moves = hanoi(n, 'A', 'C', 'B');
    
    end = clock(); // Fin du comptage du temps
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcul du temps écoulé en secondes
    
    printf("Nombre total de d%cplacements : %d\n", 130,total_moves);
    printf("Temps d'ex%ccution : %f secondes\n", 130, cpu_time_used);
    
    return 0;
}
