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
// Définition de la structure de la pile
void moveDiskRecursif(Stack *source, Stack *target)
{
    int disk = pop(source);
    push(target, disk);
    printf("D%cplacement du disque %d de %c vers %c\n",130, disk, source->name,target->name);
}

int tohRecursif(int n, Stack *source, Stack *auxiliary, Stack *target) {
    int moveCount = 0;

    if (n > 0) {
        moveCount += tohRecursif(n - 1, source, target, auxiliary);
        moveDiskRecursif(source, target);
        moveCount++;
        moveCount += tohRecursif(n - 1, auxiliary, source, target);
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
 
     printf("Solution R%ccursive: \n",130);
    // Appel de la fonction tohRecursif pour résoudre le problème
 int moveCount = tohRecursif(n, source, auxiliary, target);
    
        end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    
    printf("Temps d'ex%ccution : %f secondes\n",130, execution_time);
   
    printf("Nombre de d%ccalages: %d\n",130, moveCount);

    return 0;
}