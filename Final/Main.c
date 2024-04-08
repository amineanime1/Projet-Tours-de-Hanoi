#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAX_DISKS 100
#define MAX_LOGS 10 // Nombre maximal de logs à conserver

struct Log
{
    char algo[20];         // Nom de l'algorithme
    int n;                 // Nombre de disques
    double execution_time; // Temps d'exécution
    int moves;             // Nombre total de déplacements
    bool verification_success; // Flag to indicate if the verification was successful
};
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

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

// Function to check if all disks are in the target stack
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

bool verification (int n, Stack *source, Stack *auxiliary, Stack *target) {
        if (isEmpty(source) && isEmpty(auxiliary) && isComplete(target, n)) {
            printf("Les disques ont %ct%c d%cplac%cs avec succ%cs vers la tour C.\n",130,130,130,130,138);
    return true;
} else {
    printf("Les disques n'ont pas %ct%c d%cplac%cs avec succ%cs.\n",130,130,130,130,138);
   return false;
}
}
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
// Fonction pour enregistrer un log
void add_log(struct Log logs[], char algo[], int n, double execution_time, int moves, int *log_count, bool verification_success)
{
    if (*log_count < MAX_LOGS)
    {
        struct Log new_log = {0};
        sprintf(new_log.algo, "%s", algo);
        new_log.n = n;
        new_log.execution_time = execution_time;
        new_log.moves = moves; // Mettre à jour le nombre total de déplacements
        new_log.verification_success = verification_success; // Add verification success flag
        logs[*log_count] = new_log;
        (*log_count)++;
    }
    else
    {
        // Si le nombre maximal de logs est atteint, supprimer le premier et décaler les autres
        for (int i = 0; i < MAX_LOGS - 1; i++)
        {
            logs[i] = logs[i + 1];
        }
        // Ajouter le nouveau log à la fin
        struct Log new_log = {0};
        sprintf(new_log.algo, "%s", algo);
        new_log.n = n;
        new_log.execution_time = execution_time;
        new_log.moves = moves; // Mettre à jour le nombre total de déplacements
        new_log.verification_success = verification_success; // Add verification success flag
        logs[MAX_LOGS - 1] = new_log;
    }
}

// Fonction pour afficher les logs
void display_logs(struct Log logs[], int log_count)
{
    printf("Logs des derni%cres utilisations :\n", 138);
    for (int i = 0; i < log_count; i++)
    {
        printf("%d - %s | %d disques | Temps d'ex%ccution : %f secondes | Nombre total de d%cplacements : %d | ",
               i + 1, logs[i].algo, logs[i].n, 130, logs[i].execution_time, 130, logs[i].moves);

        // Check if verification was successful and print accordingly
        if (logs[i].verification_success) {
            printf("Correct solution\n");
        } else {
            printf("Incorrect solution\n");
        }
    }
}

int main()
{
    int choix_algo;
     struct Log logs[MAX_LOGS] = {0};
    int log_count = 0;

    do
    {
        printf("\nChoisissez l'algorithme pour r%csoudre les Tours d'Hano%c :\n",130,139);
        printf("1. R%ccursif\n",130);
        printf("2. It%cratif\n",130);
        printf("3. Logs des derni%cres utilisations\n",138);
        printf("4. Quitter\n");
        scanf("%d", &choix_algo);

        if (choix_algo == 1 || choix_algo == 2)
        {
            int n;
            printf("Entrez le nombre de disques : ");
            scanf("%d", &n);

            clock_t start_time, end_time;
            double execution_time;
            int moves = 0;
            start_time = clock();

if (choix_algo == 1)
{
    printf("Algorithme r%ccursif :\n",130);
    Stack *source = createStack(n, 'A');
    Stack *auxiliary = createStack(n, 'B');
    Stack *target = createStack(n, 'C');

    for (int i = n; i > 0; i--)
    {
        push(source, i);
    }
    moves = tohRecursif(n, source, auxiliary, target); 
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
  printf("Nombre de d%cplacements : %d coups\n",130, moves);
    printf("Temps d'ex%ccution : %f secondes\n", 130,execution_time);
 bool verificationResult = verification(n, source, auxiliary, target);
    add_log(logs, "R\x82" "cursif", n, execution_time, moves, &log_count, verificationResult); // Add the verification result to the logs
}
if (choix_algo == 2)
{
    printf("Algorithme it%cratif :\n",130);
    Stack *source = createStack(n, 'A');
    Stack *auxiliary = createStack(n, 'B');
    Stack *target = createStack(n, 'C');

    for (int i = n; i > 0; i--)
    {
        push(source, i);
    }
    moves = tohIteratif(n, source, target, auxiliary); // Passer l'adresse de la variable moves
    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Nombre de d%cplacements : %d coups\n",130, moves);
    printf("Temps d'ex%ccution : %f secondes\n", 130,execution_time);
 bool verificationResult = verification(n, source, auxiliary, target);
    add_log(logs, "It\x82ratif", n, execution_time, moves, &log_count, verificationResult); // Add the verification result to the logs
}
        }
         else if (choix_algo == 3)
        {
            display_logs(logs, log_count);
        }

    } while (choix_algo != 4);

    printf("Fin du programme.\n");
    return 0;
}