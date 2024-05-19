import java.util.Stack;
import java.util.LinkedList;

public class Rods {
    // Constantes
    static final int NUMBER_OF_RODS = 3; // Nombre de tiges dans le jeu
    static final int RODS_WIDTH = 600; // Largeur des tiges

    Rod[] rodArray; // Tableau des tiges
    LinkedList<Integer> movesToSolve; // Liste des mouvements nécessaires pour résoudre le puzzle
    int nombrededisque; // Nombre de disques

    // Constructeur pour initialiser les tiges et les disques
    public Rods(int numberOfDisks, int initialRod) {
        nombrededisque = numberOfDisks; // Initialiser le nombre de disques
        Rod initial = new Rod(numberOfDisks); // Créer la tige initiale avec les disques
        rodArray = new Rod[NUMBER_OF_RODS]; // Initialiser le tableau des tiges
        for (int i = 0; i < NUMBER_OF_RODS; i++) {
            if (i == initialRod) {
                rodArray[i] = initial; // Placer les disques sur la tige initiale
            } else {
                rodArray[i] = new Rod(); // Créer des tiges vides
            }
        }
        movesToSolve = new LinkedList<Integer>(); // Initialiser la liste des mouvements
    }

    // Méthode pour réinitialiser les tiges avec un nouveau nombre de disques
    public void initializeRods(int numberOfDisks, int initialRod) {
        Rod initial = new Rod(numberOfDisks); // Créer la tige initiale avec les nouveaux disques
        rodArray = new Rod[NUMBER_OF_RODS]; // Réinitialiser le tableau des tiges
        for (int i = 0; i < NUMBER_OF_RODS; i++) {
            if (i == initialRod) {
                rodArray[i] = initial; // Placer les disques sur la tige initiale
            } else {
                rodArray[i] = new Rod(); // Créer des tiges vides
            }
        }
    }

    // Méthode pour obtenir le tableau des tiges
    public Rod[] getRodArray() {
        return rodArray;
    }

    // Méthode pour déplacer un disque d'une tige à une autre
    public void moveDisk(int from, int destination) {
        Stack<Disk> fromStack = rodArray[from].getDisksOnTop(); // Obtenir les disques de la tige source
        if (!fromStack.isEmpty()) {
            rodArray[destination].getDisksOnTop().push(fromStack.pop()); // Déplacer le disque vers la tige destination
        } else {
            System.out.println("Rod is empty, no disks to move..."); // Message si la tige source est vide
        }
    }

    // Méthode récursive pour résoudre le puzzle des Tours de Hanoï
    public void solveTowersOfHanoi(int disksOnTop, int from, int spare, int destination) {
        if (disksOnTop >= 1) {
            solveTowersOfHanoi(disksOnTop - 1, from, destination, spare); // Déplacer les disques au-dessus vers la tige
                                                                          // intermédiaire
            moveDisk(from, destination); // Déplacer le disque du bas vers la tige destination
            movesToSolve.addLast(from); // Enregistrer le mouvement
            movesToSolve.addLast(destination); // Enregistrer le mouvement
            solveTowersOfHanoi(disksOnTop - 1, spare, from, destination); // Déplacer les disques de la tige
                                                                          // intermédiaire vers la tige destination
        }
    }

    // Méthode pour obtenir la liste des mouvements nécessaires pour résoudre le
    // puzzle
    public LinkedList<Integer> getMovesToSolve() {
        return movesToSolve;
    }

    // Méthode pour obtenir la taille totale des disques sur toutes les tiges
    public int size() {
        int size = 0;
        for (Rod rod : rodArray) {
            size += rod.size(); // Ajouter la taille de chaque tige
        }
        return size;
    }
}
