#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure pour représenter un mouvement dans les Tours de Hanoï
struct Movement {
    int n; // Nombre de disques à déplacer
    char source, target, auxiliary; // Les trois tours impliquées dans le mouvement
};

// Fonction pour empiler un mouvement dans la pile
void push(struct Movement** stack, int* top, struct Movement movement) {
    (*top)++;
    *stack = realloc(*stack, (*top + 1) * sizeof(struct Movement));
    (*stack)[*top] = movement;
}

// Fonction pour dépiler un mouvement de la pile
struct Movement pop(struct Movement** stack, int* top) {
    struct Movement movement = (*stack)[*top];
    (*top)--;
    *stack = realloc(*stack, (*top + 1) * sizeof(struct Movement));
    return movement;
}

// Fonction pour résoudre les Tours de Hanoï de manière itérative
void iterativeHanoi(int n, char source, char target, char auxiliary) {
    // Initialiser une pile pour stocker les mouvements à effectuer
    struct Movement* stack = NULL;
    int top = -1;

    // Empiler le premier mouvement
    struct Movement initial = {n, source, target, auxiliary};
    push(&stack, &top, initial);

    while (top >= 0) {
        // Dépiler le mouvement en cours
        struct Movement current = pop(&stack, &top);

        if (current.n > 0) {
            // Empiler les mouvements nécessaires pour déplacer n-1 disques de la source à l'auxiliaire
            struct Movement move1 = {current.n - 1, current.source, current.auxiliary, current.target};
            push(&stack, &top, move1);

            // Déplacer le disque restant de la source à la cible
            printf("D%cplacer le disque %d de %c vers %c\n",130, current.n, current.source, current.target);

            // Empiler les mouvements nécessaires pour déplacer n-1 disques de l'auxiliaire à la cible
            struct Movement move2 = {current.n - 1, current.auxiliary, current.target, current.source};
            push(&stack, &top, move2);
        }
    }

    free(stack); // Libérer la mémoire de la pile
}

int main() {
    int n;
    printf("It%cratif // Entrez le nombre de disques : ",130);
    scanf("%d", &n);
    
    clock_t start_time = clock();
    
    // Appel de la fonction iterativeHanoi pour résoudre le problème
    iterativeHanoi(n, 'A', 'C', 'B');
    
    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("Temps d'ex%ccution : %f secondes\n",130, execution_time);
    
    return 0;
}
