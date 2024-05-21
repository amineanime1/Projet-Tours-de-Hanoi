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
// Fonction itérative pour déplacer un disque entre deux piles
void moveDiskIteratif(Stack *source, Stack *target) {
    int diskFromSource = top(source); // Obtient le disque au sommet de la source
    int diskFromTarget = top(target); // Obtient le disque au sommet de la cible

    // Déplace le disque si la source n'est pas vide et la cible est vide ou si la source est plus petite que la cible
    if (diskFromSource != -1 && (diskFromTarget == -1 || diskFromSource < diskFromTarget)) {
        diskFromSource = pop(source); // Retire le disque de la source
        push(target, diskFromSource); // Ajoute le disque à la cible
        printf("D%cplacement du disque %d de %c vers %c\n",130, diskFromSource, source->name, target->name); // Affiche le déplacement
    } 
    // Déplace le disque si la cible n'est pas vide et la source est vide ou si la cible est plus petite que la source
    else if (diskFromTarget != -1 && (diskFromSource == -1 || diskFromTarget < diskFromSource)) {
        diskFromTarget = pop(target); // Retire le disque de la cible
        push(source, diskFromTarget); // Ajoute le disque à la source
        printf("D%cplacement du disque %d de %c vers %c\n",130, diskFromTarget, target->name, source->name); // Affiche le déplacement
    }
}
// Fonction itérative pour résoudre le problème des Tours de Hanoi
int tohIteratif(int n, Stack *source, Stack *target, Stack *auxiliary) {
    int total_moves = (1 << n) - 1; // Calcule le nombre total de mouvements
    int moveCount = 0; // Compteur de mouvements

    // Échanger la cible et l'auxiliaire si le nombre de disques est pair
    if (n % 2 == 0) {
        Stack *temp = target;
        target = auxiliary;
        auxiliary = temp;
    }

    // Effectue les mouvements jusqu'à ce que le nombre total de mouvements soit atteint
    while (moveCount < total_moves) {
        // Déplace les disques selon la règle des 3 mouvements
        if (moveCount % 3 == 0) {
            moveDiskIteratif(source, target); // Déplace un disque de source vers cible
        } else if (moveCount % 3 == 1) {
            moveDiskIteratif(source, auxiliary); // Déplace un disque de source vers auxiliaire
        } else {
            moveDiskIteratif(auxiliary, target); // Déplace un disque de auxiliaire vers cible
        }
        moveCount++; // Incrémente le compteur de mouvements
    }

    return moveCount; // Retourne le nombre total de mouvements effectués
}
 // La fonction principale
int main (){
    int n ;
    printf("Entrez le nombre de disques: ");
    scanf("%d", &n);
    Stack *source = createStack(n, 'A'); // Crée une pile source avec le nombre de disques donné et le nom 'A'
    Stack *auxiliary = createStack(n, 'B'); // Crée une pile auxiliaire avec le nombre de disques donné et le nom 'B'
    Stack *target = createStack(n, 'C'); // Crée une pile cible avec le nombre de disques donné et le nom 'C'

    clock_t start_time, end_time;
    start_time = clock(); // Enregistre le temps de début de l'exécution

    for (int i = n; i > 0; i--) {
        push(source, i); // Ajoute les disques à la pile source en ordre décroissant
    }

    printf("Solution It%crative: \n",130);
    // Appel de la fonction tohIteratif pour résoudre le problème
    int moveCount = tohIteratif(n, source, target, auxiliary); // Résout le problème des Tours de Hanoi de manière itérative

    end_time = clock(); // Enregistre le temps de fin de l'exécution
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcule le temps d'exécution en secondes

    printf("Temps d'ex%ccution : %f secondes\n",130, execution_time); // Affiche le temps d'exécution
    printf("Nombre de d%cplacements: %d\n", 130,moveCount); // Affiche le nombre total de déplacements effectués

    return 0;
}
