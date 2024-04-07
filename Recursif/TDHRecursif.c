#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Définition de la structure de la pile
typedef struct {
    char *array; // Tableau pour stocker les disques
    int capacity; // Capacité maximale de la pile
    int top; // Indice du sommet de la pile
} Stack;

// Fonction pour initialiser une pile avec une capacité donnée
Stack *createStack(int capacity) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char *)malloc(stack->capacity * sizeof(char));
    return stack;
}

// Fonction pour vérifier si la pile est pleine
int isFull(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

// Fonction pour vérifier si la pile est vide
int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Fonction pour empiler un élément sur la pile
void push(Stack *stack, char item) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

// Fonction pour dépiler un élément de la pile
char pop(Stack *stack) {
    if (isEmpty(stack))
        return '\0';
    return stack->array[stack->top--];
}

// Fonction pour résoudre les Tours de Hanoï et calculer le nombre de déplacements
int hanoi(Stack *source, Stack *target, Stack *auxiliary, int n) {
    if (n == 1) {
        char disk = pop(source);
        push(target, disk);
        printf("Déplacer le disque %d vers la tour %c\n", disk - '0', target == source ? 'A' : (target == auxiliary ? 'B' : 'C'));
        return 1; // Un déplacement pour un disque
    } else {
        int moves = 0;
        // Déplacer n-1 disques de la source à l'auxiliaire en utilisant la tour cible comme tampon
        moves += hanoi(source, auxiliary, target, n - 1);
        
        // Déplacer le disque le plus grand de la source à la cible
        moves += hanoi(source, target, auxiliary, 1);
        
        // Déplacer n-1 disques de l'auxiliaire à la cible en utilisant la tour source comme tampon
        moves += hanoi(auxiliary, target, source, n - 1);
        
        return moves;
    }
}

int main() {
    int n;
    printf("Entrez le nombre de disques : ");
    scanf("%d", &n);
    
    Stack *source = createStack(n);
    Stack *auxiliary = createStack(n);
    Stack *target = createStack(n);

    // Initialiser la tour source avec les disques
    for (int i = n; i >= 1; i--) {
        push(source, i + '0');
    }
    
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    
    int total_moves = hanoi(source, target, auxiliary, n);
    
    end = clock();
    
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Nombre total de déplacements : %d\n", total_moves);
    printf("Temps d'exécution : %f secondes\n", cpu_time_used);

    free(source->array);
    free(source);
    free(auxiliary->array);
    free(auxiliary);
    free(target->array);
    free(target);
    
    return 0;
}
