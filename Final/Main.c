#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h> // Pour utiliser le type bool en C

#define MAX_LOGS 10 // Nombre maximal de logs à conserver

// Structure pour représenter un mouvement dans les Tours de Hanoï
struct Movement
{
    int n;                          // Nombre de disques à déplacer
    char source, target, auxiliary; // Les trois tours impliquées dans le mouvement
};

// Structure pour représenter un log
struct Log
{
    char algo[20];         // Nom de l'algorithme
    int n;                 // Nombre de disques
    double execution_time; // Temps d'exécution
    int moves;             // Nombre total de déplacements
};

// Fonction pour empiler un mouvement dans la pile
void push(struct Movement **stack, int *top, struct Movement movement)
{
    (*top)++;
    *stack = realloc(*stack, (*top + 1) * sizeof(struct Movement));
    (*stack)[*top] = movement;
}

// Fonction pour dépiler un mouvement de la pile
struct Movement pop(struct Movement **stack, int *top)
{
    struct Movement movement = (*stack)[*top];
    (*top)--;
    *stack = realloc(*stack, (*top + 1) * sizeof(struct Movement));
    return movement;
}

// Fonction pour vérifier si l'état final est correct
bool check_final_state(struct Movement *stack, int top) {
    if (top == -1) {
        return true;
    }

    int prev_disk = stack[top].n;
    for (int i = top - 1; i >= 0; i--) {
        if (stack[i].n >= prev_disk) {
            return false;
        }
        prev_disk = stack[i].n;
    }

    return true;
}
// Fonction pour résoudre les Tours de Hanoï de manière récursive et enregistrer les logs
int hanoi_recursif(int n, char source, char target, char auxiliary, struct Log logs[], int *log_count)
{
    // Initialiser une pile pour stocker les mouvements à effectuer
    struct Movement *stack = NULL;
    int top = -1;

    // Empiler le premier mouvement
    struct Movement initial = {n, source, target, auxiliary};
    push(&stack, &top, initial);

    int moves = 0;

    while (top >= 0)
    {
        // Dépiler le mouvement en cours
        struct Movement current = pop(&stack, &top);

        if (current.n == 1)
        {
            // Si le nombre de disques est 1, effectuer le déplacement directement
            printf("D%cplacer le disque 1 de %c vers %c\n", 130,current.source, current.target);
            moves++; // Ajouter un déplacement
        }
        else
        {
            // Empiler les mouvements nécessaires pour déplacer n-1 disques de la source à l'auxiliaire
            struct Movement move1 = {current.n - 1, current.source, current.auxiliary, current.target};
            push(&stack, &top, move1);

            // Déplacer le disque restant de la source à la cible
            printf("D%cplacer le disque %d de %c vers %c\n",130, current.n, current.source, current.target);
            moves++; // Ajouter un déplacement

            // Empiler les mouvements nécessaires pour déplacer n-1 disques de l'auxiliaire à la cible
            struct Movement move2 = {current.n - 1, current.auxiliary, current.target, current.source};
            push(&stack, &top, move2);
        }
    }

    free(stack); // Libérer la mémoire de la pile

    // Enregistrer le log
    if (*log_count < MAX_LOGS)
    {
        struct Log new_log = {0};
        sprintf(new_log.algo, "R%ccursif", 130);
        new_log.n = n;
        new_log.moves = moves;
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
        sprintf(new_log.algo, "R%ccursif", 130);
        new_log.n = n;
        new_log.moves = moves;
        logs[MAX_LOGS - 1] = new_log;
    }

    return moves;
}

// Fonction pour résoudre les Tours de Hanoï de manière itérative et enregistrer les logs
int hanoi_iteratif(int n, char source, char target, char auxiliary)
{
    // Initialize a counter for moves
    int moves = 0;

    // Initialiser une pile pour stocker les mouvements à effectuer
    struct Movement *stack = NULL;
    int top = -1;

    // Empiler le premier mouvement
    struct Movement initial = {n, source, target, auxiliary};
    push(&stack, &top, initial);

    while (top >= 0)
    {
        // Dépiler le mouvement en cours
        struct Movement current = pop(&stack, &top);

        if (current.n > 0)
        {
            // Empiler les mouvements nécessaires pour déplacer n-1 disques de la source à l'auxiliaire
            struct Movement move1 = {current.n - 1, current.source, current.auxiliary, current.target};
            push(&stack, &top, move1);

            // Déplacer le disque restant de la source à la cible
            printf("D%cplacer le disque %d de %c vers %c\n", 130, current.n, current.source, current.target);

            // Empiler les mouvements nécessaires pour déplacer n-1 disques de l'auxiliaire à la cible
            struct Movement move2 = {current.n - 1, current.auxiliary, current.target, current.source};
            push(&stack, &top, move2);

            moves++; // Ajouter un déplacement
        }
    }

    free(stack); // Libérer la mémoire de la pile

    // Return the number of moves
    return moves;
}

// Fonction pour enregistrer un log
void add_log(struct Log logs[], char algo[], int n, double execution_time, int moves, int *log_count)
{
    if (*log_count < MAX_LOGS)
    {
        struct Log new_log = {0};
        sprintf(new_log.algo, "%s", algo);
        new_log.n = n;
        new_log.execution_time = execution_time;
        new_log.moves = moves; // Mettre à jour le nombre total de déplacements
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
        logs[MAX_LOGS - 1] = new_log;
    }
}

// Fonction pour afficher les logs
void display_logs(struct Log logs[], int log_count)
{
    printf("Logs des derni%cres utilisations :\n", 138);
    for (int i = 0; i < log_count; i++)
    {
        printf("%d - %s | %d disques | Temps d'ex%ccution : %f secondes | Nombre total de d%cplacements : %d\n",
               i + 1, logs[i].algo, logs[i].n,130, logs[i].execution_time,130, logs[i].moves);
    }
}

int main()
{
    int choix_algo;
    struct Log logs[MAX_LOGS] = {0};
    int log_count = 0;

struct Movement *final_state_stack = NULL;
    int final_state_top = -1;

    do
    {
        printf("\nChoisissez l'algorithme pour r%csoudre les Tours de Hano%c :\n",130,139);
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

            start_time = clock();

            int moves; // Définir moves ici
            if (choix_algo == 1)
            {
                printf("Algorithme r%ccursif :\n",130);
                int moves = hanoi_recursif(n, 'A', 'C', 'B', logs, &log_count);
                printf("Nombre total de d%cplacements : %d\n",130, moves);
                end_time = clock();
                execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                add_log(logs, "R\x82" "cursif", n, execution_time, moves, &log_count);
            }
            else if (choix_algo == 2)
            {
                printf("Algorithme it%cratif :\n",130);
                int moves = hanoi_iteratif(n, 'A', 'C', 'B');
                printf("Nombre total de d%cplacements : %d\n", 130,moves);
                end_time = clock();
                execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                add_log(logs, "It\x82" "ratif", n, execution_time, moves, &log_count);
            }
            printf("Temps d'ex%ccution : %f secondes\n", 130,execution_time);

            // Vérification de l'état final
                printf("V%crification de l'%ctat final :\n",130,130);
            bool final_state_correct = check_final_state(final_state_stack, final_state_top);
            if (final_state_correct) {
                printf("L'%ctat final est correct.\n",130);
            } else {
                printf("L'%ctat final est incorrect.\n",130);
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
