import java.util.Stack;

public class Rod {

    private static final int DISK_CAPACITY = 10; // Capacité maximale des disques, utilisée pour déterminer la taille
                                                 // des disques

    private Stack<Disk> disksOnTop; // Pile pour stocker les disques sur la tige

    // Constructeur par défaut pour créer une tige vide
    public Rod() {
        disksOnTop = new Stack<Disk>(); // Initialisation de la pile de disques
    }

    // Constructeur pour créer une tige avec un nombre spécifié de disques
    public Rod(int numberOfDisks) {
        disksOnTop = new Stack<Disk>(); // Initialisation de la pile de disques
        for (int i = 0; i < numberOfDisks; i++) {
            // Création des disques avec des tailles décroissantes et les ajouter à la pile
            disksOnTop.push(new Disk(DISK_CAPACITY - i));
        }
    }

    // Méthode pour obtenir la pile de disques sur la tige
    public Stack<Disk> getDisksOnTop() {
        return disksOnTop;
    }

    // Méthode pour obtenir le nombre total de disques sur la tige
    public int getTotalDisks() {
        return disksOnTop.size();
    }

    // Méthode pour obtenir la taille de la pile de disques
    public int size() {
        return disksOnTop.size();
    }
}
