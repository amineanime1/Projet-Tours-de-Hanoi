#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
// Fonction pour vérifier si la pile est vide
int isEmpty(Stack *stack) {
    // Vérifie si la pile est vide en vérifiant si le dessus de la pile est à -1
    return stack->top == -1; // Retourne 1 si la pile est vide, sinon 0
}

// Fonction pour vérifier si tous les disques sont dans la pile cible dans le bon ordre
int isComplete(Stack *target, int n) {
    // Vérifie si la taille de la pile cible correspond au nombre total de disques
    if (target->top != n - 1) { // Si la taille est différente, la pile n'est pas complète
        return 0; // Retourne 0 pour indiquer que la pile n'est pas complète
    }

    // Vérifie si les disques sont dans la pile cible dans le bon ordre
    for (int i = 0; i < n; i++) {
        if (target->array[i] != n - i) { // Si un disque est dans une position incorrecte
            return 0; // Retourne 0 pour indiquer que la pile n'est pas complète
        }
    }

    // Si toutes les vérifications sont réussies, retourne 1 pour indiquer que la pile est complète
    return 1;
}

// Déplacement d'un disque entre deux piles
void moveDisk(Stack *source, Stack *target) {
    int disk = pop(source); // Retire un disque de la pile source
    push(target, disk); // Ajoute le disque à la pile cible
    printf("D%cplacer disque %d de tour %c vers tour %c\n",130, disk, source->name, target->name); // Affiche le déplacement du disque
}

// Fonction récursive pour résoudre le jeu de Hanoï
void hanoi(int n, Stack *source, Stack *auxiliary, Stack *target) {
    if (n == 1) {
        moveDisk(source, target); // Déplace directement le disque de la source vers la cible
        return;
    }

    hanoi(n - 1, source, target, auxiliary); // Déplace n-1 disques de la source vers l'auxiliaire
    moveDisk(source, target); // Déplace le disque restant de la source vers la cible
    hanoi(n - 1, auxiliary, source, target); // Déplace les n-1 disques de l'auxiliaire vers la cible
}
// Fonction pour vérifier si le problème a été résolu correctement
bool verification(int n, Stack *source, Stack *auxiliary, Stack *target) {
    // Vérifie si toutes les piles sont vides sauf la pile cible, et si les disques sont dans le bon ordre dans la pile cible
    if (isEmpty(source) && isEmpty(auxiliary) && isComplete(target, n)) {
        // Affiche un message indiquant que les disques ont été déplacés avec succès vers la tour C
        printf("Les disques ont %ct%c d%cplac%cs avec succ%cs vers la tour C.\n",130,130,130,130,138);
        // Retourne vrai pour indiquer que la vérification est réussie
        return true;
    } else {
        // Affiche un message indiquant que les disques n'ont pas été déplacés avec succès
        printf("Les disques n'ont pas %ct%c d%cplac%cs avec succ%cs.\n",130,130,130,130,138);
        // Retourne faux pour indiquer que la vérification a échoué
        return false;
    }
}
 // La fonction principale
int main() {
    int n; // Nombre de disques
    printf("Algorithme de v%crification: \n(pour le bien du test nous avons choisi d'utiliser l'algorithme r%ccursif pour illustrer l'algorithme de v%crification)\n",130,130,130);
    printf("Entrez le nombre de disques: ");
    scanf("%d", &n); // Lit le nombre de disques depuis l'entrée utilisateur

    // Création des trois tours
    Stack *source = createStack(n, 'A'); // Crée la pile source avec la capacité n et le nom 'A'
    Stack *auxiliary = createStack(n, 'B'); // Crée la pile auxiliaire avec la capacité n et le nom 'B'
    Stack *target = createStack(n, 'C'); // Crée la pile cible avec la capacité n et le nom 'C'

    // Initialisation de la tour source avec les disques
    for (int i = n; i > 0; i--) {
        push(source, i); // Ajoute les disques à la pile source dans l'ordre décroissant
    }
    printf("Algorithme de v%crification: \n",130);

    // Affichage de l'état initial des tours
    printf("----------------------------------------------\n");
    printf("%ctat initial des tours :\n",130);
    printf("Tour A : ");
    for (int i = source->top; i >= 0; i--) {
        printf("%d ", source->array[i]); // Affiche les disques de la pile source
    }
    printf("\nTour B : ");
    for (int i = auxiliary->top; i >= 0; i--) {
        printf("%d ", auxiliary->array[i]); // Affiche les disques de la pile auxiliaire
    }
    printf("\nTour C : ");
    for (int i = target->top; i >= 0; i--) {
        printf("%d ", target->array[i]); // Affiche les disques de la pile cible
    }
    printf("\n");
    printf("----------------------------------------------\n");

    // Résolution du jeu de Hanoï
    hanoi(n, source, auxiliary, target);

    printf("----------------------------------------------\n");
    printf("%ctat final des tours :\n",130);
    printf("Tour A : ");
    for (int i = source->top; i >= 0; i--) {
        printf("%d ", source->array[i]); // Affiche les disques de la pile source
    }
    printf("\nTour B : ");
    for (int i = auxiliary->top; i >= 0; i--) {
        printf("%d ", auxiliary->array[i]); // Affiche les disques de la pile auxiliaire
    }
    printf("\nTour C : ");
    for (int i = target->top; i >= 0; i--) {
        printf("%d ", target->array[i]); // Affiche les disques de la pile cible
    }
    printf("\n");
    printf("----------------------------------------------\n");

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
