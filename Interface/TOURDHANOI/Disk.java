
public class Disk {

    protected static final int THICKNESS = 18;// l'épaisseur d'un disque
    private int size;// Variable d'instance représentant la taille du disque

    // Constructeur de la classe Disk qui initialise la taille du disque
    public Disk(int size) {
        this.size = size;
    }

    // obtenir la taille du disque
    public int getSize() {
        return size;
    }
}
