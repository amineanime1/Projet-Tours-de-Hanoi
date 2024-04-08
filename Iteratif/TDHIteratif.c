#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Stack
{
    int top;
    unsigned capacity;
    int *array;
    char name;
} Stack;

Stack *createStack(unsigned capacity, char name)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    stack->name = name;
    return stack;
}

void push(Stack *stack, int item)
{
    stack->array[++stack->top] = item;
}

int pop(Stack *stack)
{
    if (stack->top == -1)
        return -1;
    return stack->array[stack->top--];
}
int top(Stack* stack) {
    if (stack->top == -1) return -1;
    return stack->array[stack->top];
}
// Structure pour représenter un mouvement dans les Tours de Hanoï
void moveDiskIteratif(Stack *source, Stack *target) {
    int diskFromSource = top(source);
    int diskFromTarget = top(target);

    if (diskFromSource != -1 && (diskFromTarget == -1 || diskFromSource < diskFromTarget)) {
        diskFromSource = pop(source);
        push(target, diskFromSource);
        printf("D%cplacement du disque %d de %c vers %c\n",130, diskFromSource, source->name, target->name);
    } else if (diskFromTarget != -1 && (diskFromSource == -1 || diskFromTarget < diskFromSource)) {
        diskFromTarget = pop(target);
        push(source, diskFromTarget);
        printf("D%cplacement du disque %d de %c vers %c\n",130, diskFromTarget, target->name, source->name);
    }
}
int tohIteratif(int n, Stack *source, Stack *target, Stack *auxiliary)
{
    int total_moves = (1 << n) - 1; 
    int moveCount = 0;

    if (n % 2 == 0) {
        Stack *temp = target;
        target = auxiliary;
        auxiliary = temp;
    }

    while (moveCount < total_moves) {
        if (moveCount % 3 == 0) {
            moveDiskIteratif(source, target);
        } else if (moveCount % 3 == 1) {
            moveDiskIteratif(source, auxiliary);
        } else {
            moveDiskIteratif(auxiliary, target);
        }
        moveCount++;
    }

    return moveCount;
}
int main (){


    int n ;
    printf("Entrez le nombre de disques: ");
    scanf("%d", &n);
    Stack *source = createStack(n, 'A');
    Stack *auxiliary = createStack(n, 'B');
    Stack *target = createStack(n, 'C');

     clock_t start_time, end_time;
            start_time = clock();
    for (int i = n; i > 0; i--) {
        push(source, i);
    }
 
    printf("Solution It%crative: \n",130);
    // Appel de la fonction tohIteratif pour résoudre le problème
 int moveCount = tohIteratif(n, source, target, auxiliary);
    
        end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("Temps d'ex%ccution : %f secondes\n",130, execution_time);
   
    printf("Nombre de d%ccalages: %d\n",130, moveCount);

    return 0;
}