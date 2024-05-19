#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure représentant une pile utilisée dans le problème des Tours de Hanoi
typedef struct Stack {
    int top; // Index de l'élément du dessus
    unsigned capacity; // Capacité de la pile
    int *array; // Tableau pour stocker les éléments de la pile
    char name; // Nom de la pile (A, B ou C)
} Stack;

// Fonction pour créer une pile avec une capacité et un nom donnés
Stack *createStack(unsigned capacity, char name) {
    Stack *stack = (Stack *)malloc(sizeof(Stack)); // Alloue de la mémoire pour la structure Stack
    stack->capacity = capacity; // Initialise la capacité de la pile
    stack->top = -1; // Initialise l'index de l'élément du dessus à -1 (pile vide)
    stack->array = (int *)malloc(stack->capacity * sizeof(int)); // Alloue de la mémoire pour le tableau d'éléments de la pile
    stack->name = name; // Initialise le nom de la pile
    return stack; // Retourne la pile créée
}

// Fonction pour ajouter un élément à la pile
void push(Stack *stack, int item) {
    stack->array[++stack->top] = item; // Ajoute l'élément au sommet de la pile et met à jour l'index du sommet
}

// Fonction pour retirer un élément de la pile
int pop(Stack *stack) {
    if (stack->top == -1)
        return -1; // Si la pile est vide, retourne -1
    return stack->array[stack->top--]; // Retourne l'élément du sommet de la pile et met à jour l'index du sommet
}

// Fonction pour obtenir l'élément du dessus de la pile sans le retirer
int top(Stack* stack) {
    // Vérifie si la pile est vide
    if (stack->top == -1) return -1; // Si la pile est vide, retourne -1
    // Sinon, retourne l'élément du dessus de la pile
    return stack->array[stack->top];
}

// Fonction récursive pour déplacer un disque de la source vers la cible
void moveDiskRecursif(Stack *source, Stack *target) {
    int disk = pop(source); // Retire le disque du sommet de la source
    push(target, disk); // Ajoute le disque au sommet de la cible
    printf("D%cplacement du disque %d de %c vers %c\n",130, disk, source->name, target->name); // Affiche le déplacement
}

// Fonction récursive pour résoudre le problème des Tours de Hanoi
int tohRecursif(int n, Stack *source, Stack *auxiliary, Stack *target) {
    int moveCount = 0; // Compteur de mouvements

    if (n > 0) {
        moveCount += tohRecursif(n - 1, source, target, auxiliary); // Déplace les n-1 disques du source vers l'auxiliaire
        moveDiskRecursif(source, target); // Déplace le disque restant de source vers cible
        moveCount++; // Incrémente le compteur de mouvements
        moveCount += tohRecursif(n - 1, auxiliary, source, target); // Déplace les n-1 disques de l'auxiliaire vers la cible
    }

    return moveCount; // Retourne le nombre total de mouvements effectués
}
 // La fonction principale
int main (){

    int n ;
    printf("Entrez le nombre de disques: ");
    scanf("%d", &n); // Demande à l'utilisateur d'entrer le nombre de disques
    Stack *source = createStack(n, 'A'); // Crée une pile source avec le nombre de disques et le nom 'A'
    Stack *auxiliary = createStack(n, 'B'); // Crée une pile auxiliaire avec le nombre de disques et le nom 'B'
    Stack *target = createStack(n, 'C'); // Crée une pile cible avec le nombre de disques et le nom 'C'

    clock_t start_time, end_time;
    start_time = clock(); // Enregistre le temps de début de l'algorithme

    for (int i = n; i > 0; i--) {
        push(source, i); // Ajoute les disques à la pile source en ordre décroissant
    }

    printf("Solution R%ccursive: \n",130);
    // Appel de la fonction tohRecursif pour résoudre le problème
    int moveCount = tohRecursif(n, source, auxiliary, target);

    end_time = clock(); // Enregistre le temps de fin de l'algorithme
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcule le temps d'exécution en secondes

    printf("Temps d'ex%ccution : %f secondes\n",130, execution_time); // Affiche le temps d'exécution
    printf("Nombre de d%cplacements: %d\n",130, moveCount); // Affiche le nombre de déplacements effectués

    return 0;
}