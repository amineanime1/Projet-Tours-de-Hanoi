#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure de la pile
typedef struct Stack {
    int top;
    unsigned capacity;
    int *array;
    char name;
} Stack;

// Création d'une pile
Stack *createStack(unsigned capacity, char name) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    stack->name = name;
    return stack;
}

// Ajout d'un élément dans la pile
void push(Stack *stack, int item) {
    stack->array[++stack->top] = item;
}

// Retrait d'un élément de la pile
int pop(Stack *stack) {
    if (stack->top == -1)
        return -1;
    return stack->array[stack->top--];
}

// Récupération du sommet de la pile sans le retirer
int top(Stack* stack) {
    if (stack->top == -1)
        return -1;
    return stack->array[stack->top];
}

// Vérification si la pile est vide
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Vérification si tous les disques sont dans la pile cible
int isComplete(Stack *target, int n) {
    if (target->top != n - 1) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        if (target->array[i] != n - i) {
            return 0;
        }
    }

    return 1;
}

// Déplacement d'un disque entre deux piles
void moveDisk(Stack *source, Stack *target) {
    int disk = pop(source);
    push(target, disk);
    printf("Déplacer disque %d de tour %c à tour %c\n", disk, source->name, target->name);
}

// Fonction récursive pour résoudre le jeu de Hanoï
void hanoi(int n, Stack *source, Stack *auxiliary, Stack *target) {
    if (n == 1) {
        moveDisk(source, target);
        return;
    }

    hanoi(n - 1, source, target, auxiliary);
    moveDisk(source, target);
    hanoi(n - 1, auxiliary, source, target);
}

// Vérification de la solution
bool verification(int n, Stack *source, Stack *auxiliary, Stack *target) {
    if (isEmpty(source) && isEmpty(auxiliary) && isComplete(target, n)) {
        printf("Les disques ont été déplacés avec succès vers la tour C.\n");
        return true;
    } else {
        printf("Les disques n'ont pas été déplacés avec succès.\n");
        return false;
    }
}

int main() {
    int n = 3; // Nombre de disques

    // Création des trois tours
    Stack *source = createStack(n, 'A');
    Stack *auxiliary = createStack(n, 'B');
    Stack *target = createStack(n, 'C');

    // Initialisation de la tour source avec les disques
    for (int i = n; i > 0; i--) {
        push(source, i);
    }

    // Affichage de l'état initial des tours
    printf("État initial des tours :\n");
    printf("Tour A : ");
    for (int i = source->top; i >= 0; i--) {
        printf("%d ", source->array[i]);
    }
    printf("\nTour B : ");
    for (int i = auxiliary->top; i >= 0; i--) {
        printf("%d ", auxiliary->array[i]);
    }
    printf("\nTour C : ");
    for (int i = target->top; i >= 0; i--) {
        printf("%d ", target->array[i]);
    }
    printf("\n\n");

    // Résolution du jeu de Hanoï
    hanoi(n, source, auxiliary, target);

    // Vérification de la solution
    verification(n, source, auxiliary, target);

    // Libération de la mémoire allouée
    free(source->array);
    free(auxiliary->array);
    free(target->array);
    free(source);
    free(auxiliary);
    free(target);

    return 0;
}
