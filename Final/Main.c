#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// Constants defining the maximum number of disks and logs
#define MAX_DISKS 100
#define MAX_LOGS 10 // Number of logs to keep

// Structure to hold log information
struct Log {
    char algo[20];         // Nom de l'algorithme
    int n;                 // Nombre de disques
    double execution_time; // Temps d'exécution
    int moves;             // Nombre total de déplacements
    bool verification_success; // Indicateur si la vérification a réussi
    int max_size; // Taille maximale observée
    double verification_time; // Temps passé sur la vérification
};

// Structure représentant une pile utilisée dans le problème des Tours de Hanoi
typedef struct Stack {
    int top; // Index de l'élément du dessus
    unsigned capacity; // Capacité de la pile
    int *array; // Tableau pour stocker les éléments de la pile
    char name; // Nom de la pile (A, B ou C)
    int current_size; // Taille actuelle de la pile
    int max_size; // Taille maximale observée
} Stack;

// Fonction pour créer une pile avec une capacité et un nom donnés
Stack *createStack(unsigned capacity, char name) {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int *)malloc(stack->capacity * sizeof(int));
    stack->name = name;
    stack->current_size = 0; // Initialiser la taille actuelle à 0
    stack->max_size = 0; // Initialiser la taille maximale à 0
    return stack;
}

// Fonction pour ajouter un élément à la pile
void push(Stack *stack, int item) {
    stack->array[++stack->top] = item;
    stack->current_size++; // Incrémenter la taille actuelle
    if (stack->current_size > stack->max_size) {
        stack->max_size = stack->current_size; // Mettre à jour la taille maximale si la taille actuelle est plus grande
    }
}

// Fonction pour retirer un élément de la pile
int pop(Stack *stack) {
    if (stack->top == -1)
        return -1;
    stack->current_size--; // Décrémenter la taille actuelle
    return stack->array[stack->top--];
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

// Fonction pour vérifier si le problème a été résolu correctement
bool verification(int n, Stack *source, Stack *auxiliary, Stack *target) {
    // Vérifie si toutes les piles sont vides sauf la pile cible, et si les disques sont dans le bon ordre dans la pile cible
    if (isEmpty(source) && isEmpty(auxiliary) && isComplete(target, n)) {
        // Affiche un message indiquant que les disques ont été déplacés avec succès vers la tour C
        printf("Les disques ont été déplacés avec succès vers la tour C.\n");
        // Retourne vrai pour indiquer que la vérification est réussie
        return true;
    } else {
        // Affiche un message indiquant que les disques n'ont pas été déplacés avec succès
        printf("Les disques n'ont pas été déplacés avec succès.\n");
        // Retourne faux pour indiquer que la vérification a échoué
        return false;
    }
}

// Fonction récursive pour déplacer un disque de la source vers la cible
void moveDiskRecursif(Stack *source, Stack *target) {
    int disk = pop(source); // Retire le disque du sommet de la source
    push(target, disk); // Ajoute le disque au sommet de la cible
    printf("Déplacement du disque %d de %c vers %c\n", disk, source->name, target->name); // Affiche le déplacement
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

// Fonction itérative pour déplacer un disque entre deux piles
void moveDiskIteratif(Stack *source, Stack *target) {
    int diskFromSource = top(source); // Obtient le disque au sommet de la source
    int diskFromTarget = top(target); // Obtient le disque au sommet de la cible

    // Déplace le disque si la source n'est pas vide et la cible est vide ou si la source est plus petite que la cible
    if (diskFromSource != -1 && (diskFromTarget == -1 || diskFromSource < diskFromTarget)) {
        diskFromSource = pop(source); // Retire le disque de la source
        push(target, diskFromSource); // Ajoute le disque à la cible
        printf("Déplacement du disque %d de %c vers %c\n", diskFromSource, source->name, target->name); // Affiche le déplacement
    } 
    // Déplace le disque si la cible n'est pas vide et la source est vide ou si la cible est plus petite que la source
    else if (diskFromTarget != -1 && (diskFromSource == -1 || diskFromTarget < diskFromSource)) {
        diskFromTarget = pop(target); // Retire le disque de la cible
        push(source, diskFromTarget); // Ajoute le disque à la source
        printf("Déplacement du disque %d de %c vers %c\n", diskFromTarget, target->name, source->name); // Affiche le déplacement
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

// Fonction pour ajouter une entrée de journal
void add_log(struct Log logs[], char algo[], int n, double execution_time, int moves, int *log_count, bool verification_success, int max_size, double verification_time) {
    if (*log_count < MAX_LOGS) {
        struct Log new_log = {0}; // Crée une nouvelle entrée de journal
        sprintf(new_log.algo, "%s", algo); // Copie l'algorithme dans la nouvelle entrée
        new_log.n = n; // Affecte le nombre de disques
        new_log.execution_time = execution_time; // Affecte le temps d'exécution
        new_log.moves = moves; // Affecte le nombre de mouvements
        new_log.verification_success = verification_success; // Affecte le succès de la vérification
        new_log.max_size = max_size; // Affecte la taille maximale
        new_log.verification_time = verification_time; // Affecte le temps de vérification
        logs[*log_count] = new_log; // Ajoute la nouvelle entrée au journal
        (*log_count)++; // Incrémente le compteur de journal
    } else {
        // Si le nombre maximum de journaux est atteint, supprimer le premier et décaler les autres
        for (int i = 0; i < MAX_LOGS - 1; i++) {
            logs[i] = logs[i + 1];
        }
        struct Log new_log = {0}; // Crée une nouvelle entrée de journal
        sprintf(new_log.algo, "%s", algo); // Copie l'algorithme dans la nouvelle entrée
        new_log.n = n; // Affecte le nombre de disques
        new_log.execution_time = execution_time; // Affecte le temps d'exécution
        new_log.moves = moves; // Affecte le nombre de mouvements
        new_log.verification_success = verification_success; // Affecte le succès de la vérification
        logs[MAX_LOGS - 1] = new_log; // Ajoute la nouvelle entrée au journal
    }
}

// Fonction pour afficher les journaux
void display_logs(struct Log logs[], int log_count) {
    printf("Logs des dernières utilisations :\n"); // Affiche l'en-tête des logs
    for (int i = 0; i < log_count; i++) {

        // Affiche les détails de chaque entrée de journal
        printf("%d - %s | %d disques | Temps d'exécution : %f secondes | Nombre total de déplacements : %d | Espace mémoire occupé : %d bytes | Temps de vérification : %lf | ",
               i + 1, logs[i].algo, logs[i].n, logs[i].execution_time, logs[i].moves, logs[i].max_size, logs[i].verification_time);

        // Affiche si la vérification a réussi ou échoué
        if (logs[i].verification_success) {
            printf("Solution correcte\n"); // Affiche un message indiquant que la solution est correcte
        } else {
            printf("Solution incorrecte\n"); // Retourne faux pour indiquer que la solution est fausse
        }
    }
}

// Fonction pour afficher l'état des piles
void afficherEtatDesTours(Stack *source, Stack *auxiliary, Stack *target) {
    printf("----------------------------------------------\n"); // Affiche une ligne de séparation
    printf("Tour A : ");
    for (int i = source->top; i >= 0; i--) { // Parcourt la pile source de haut en bas
        printf("%d ", source->array[i]); // Affiche le contenu de chaque élément de la pile source
    }
    printf("\nTour B : ");
    for (int i = auxiliary->top; i >= 0; i--) { // Parcourt la pile auxiliaire de haut en bas
        printf("%d ", auxiliary->array[i]); // Affiche le contenu de chaque élément de la pile auxiliaire
    }
    printf("\nTour C : ");
    for (int i = target->top; i >= 0; i--) { // Parcourt la pile cible de haut en bas
        printf("%d ", target->array[i]); // Affiche le contenu de chaque élément de la pile cible
    }
    printf("\n----------------------------------------------\n"); // Affiche une ligne de séparation
}

int main() {
    int choix_algo; // Variable pour stocker le choix de l'algorithme
    struct Log logs[MAX_LOGS] = {0}; // Tableau pour stocker les logs des exécutions
    int log_count = 0; // Variable pour suivre le nombre de logs enregistrés

    do {
        printf("\nChoisissez l'algorithme pour résoudre les Tours de Hanoï :\n");
        printf("1. Récursif\n");
        printf("2. Itératif\n");
        printf("3. Logs des dernières utilisations\n");
        printf("4. Quitter\n");
        scanf("%d", &choix_algo); // Demande à l'utilisateur de saisir son choix

        // Traitement des choix de l'utilisateur
        if (choix_algo == 1 || choix_algo == 2) { // Si l'utilisateur a choisi l'algorithme récursif ou itératif
            int n; // Variable pour stocker le nombre de disques
            printf("Entrez le nombre de disques : ");
            scanf("%d", &n); // Demande à l'utilisateur de saisir le nombre de disques

            clock_t start_time, end_time; // Variables pour mesurer le temps d'exécution
            double execution_time; // Variable pour stocker le temps d'exécution
            int moves = 0; // Variable pour stocker le nombre de déplacements

            start_time = clock(); // Démarre le chronomètre pour mesurer le temps d'exécution

            // Exécution de l'algorithme choisi (récursif ou itératif)
            if (choix_algo == 1) { // Si l'utilisateur a choisi l'algorithme récursif
                printf("Algorithme récursif :\n");
                Stack *source = createStack(n, 'A'); // Crée une pile pour la tour A
                Stack *auxiliary = createStack(n, 'B'); // Crée une pile pour la tour B
                Stack *target = createStack(n, 'C'); // Crée une pile pour la tour C

                // Initialise la tour A avec les disques
                for (int i = n; i > 0; i--) {
                    push(source, i);
                }

                printf("État initial des tours :\n");
                afficherEtatDesTours(source, auxiliary, target); // Affiche l'état initial des tours
                moves = tohRecursif(n, source, auxiliary, target); // Exécute l'algorithme récursif
                end_time = clock(); // Arrête le chronomètre après l'exécution de l'algorithme
                execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcule le temps d'exécution
                printf("État final des tours :\n");
                afficherEtatDesTours(source, auxiliary, target); // Affiche l'état final des tours
                printf("Nombre de déplacements : %d coups\n", moves); // Affiche le nombre de déplacements
                printf("Temps d'exécution : %f secondes\n", execution_time); // Affiche le temps d'exécution
                int total_elements = source->max_size + auxiliary->max_size + target->max_size;
                int total_bytes = total_elements * sizeof(int);
                printf("Espace mémoire occupé : %d bytes\n", total_bytes); // Affiche l'espace mémoire occupé

                // Vérification de la solution
                clock_t start_verification, end_verification; // Variables pour mesurer le temps de vérification
                double verification_time; // Variable pour stock
                start_verification = clock(); // Démarre le chronomètre avant la vérification
                bool verificationResult = verification(n, source, auxiliary, target); // Vérifie la solution
                end_verification = clock(); // Arrête le chronomètre après la vérification
                verification_time = (double)(end_verification - start_verification) / CLOCKS_PER_SEC; // Calcule le temps de vérification
                printf("Temps de vérification : %f secondes\n", verification_time); // Affiche le temps de vérification

                // Ajoute les informations de l'exécution aux logs
                add_log(logs, "Récursif", n, execution_time, moves, &log_count, verificationResult, total_bytes, verification_time);
            }

            if (choix_algo == 2) { // Si l'utilisateur a choisi l'algorithme itératif
                printf("Algorithme itératif :\n");
                Stack *source = createStack(n, 'A'); // Crée une pile pour la tour A
                Stack *auxiliary = createStack(n, 'B'); // Crée une pile pour la tour B
                Stack *target = createStack(n, 'C'); // Crée une pile pour la tour C

                // Initialise la tour A avec les disques
                for (int i = n; i > 0; i--) {
                    push(source, i);
                }

                printf("État initial des tours :\n");
                afficherEtatDesTours(source, auxiliary, target); // Affiche l'état initial des tours
                moves = tohIteratif(n, source, target, auxiliary); // Exécute l'algorithme itératif
                end_time = clock(); // Arrête le chronomètre après l'exécution de l'algorithme
                execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; // Calcule le temps d'exécution
                printf("État final des tours :\n");
                afficherEtatDesTours(source, auxiliary, target); // Affiche l'état final des tours
                printf("Nombre de déplacements : %d coups\n", moves); // Affiche le nombre de déplacements
                printf("Temps d'exécution : %f secondes\n", execution_time); // Affiche le temps d'exécution
                int total_elements = source->max_size + auxiliary->max_size + target->max_size;
                int total_bytes = total_elements * sizeof(int);
                printf("Espace mémoire occupé : %d bytes\n", total_bytes); // Affiche l'espace mémoire occupé

                // Vérification de la solution
                clock_t start_verification, end_verification; // Variables pour mesurer le temps de vérification
                double verification_time; // Variable pour stocker le temps de vérification
                start_verification = clock(); // Démarre le chronomètre avant la vérification
                bool verificationResult = verification(n, source, auxiliary, target); // Vérifie la solution
                end_verification = clock(); // Arrête le chronomètre après la vérification
                verification_time = (double)(end_verification - start_verification) / CLOCKS_PER_SEC; // Calcule le temps de vérification
                printf("Temps de vérification : %f secondes\n", verification_time); // Affiche le temps de vérification

                // Ajoute les informations de l'exécution aux logs
                add_log(logs, "Itératif", n, execution_time, moves, &log_count, verificationResult, total_bytes, verification_time);
            }
        } else if (choix_algo == 3) { // Si l'utilisateur a choisi d'afficher les logs
            display_logs(logs, log_count); // Affiche les logs des exécutions précédentes
        }
    } while (choix_algo != 4); // Continue tant que l'utilisateur n'a pas choisi de quitter

    printf("Fin du programme.\n"); // Affiche un message de fin de programme
    return 0; // Termine le programme
}

