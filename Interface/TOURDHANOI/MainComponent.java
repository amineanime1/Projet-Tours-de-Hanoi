import javax.swing.JComponent;
import java.util.Stack;
import java.awt.Graphics;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.BasicStroke;

public class MainComponent extends JComponent {
    // Constants
    static Color couleur1 = new Color(0xFF8A00);
    static Color couleur2 = new Color(0xFF5C00);
    static Color couleur3 = new Color(0xFF0000);
    static Color couleur4 = new Color(0xA50077);
    static Color couleur5 = new Color(0x61004D);
    static Color couleur6 = new Color(0x250033);
    static Color couleur7 = new Color(0x09006B);
    static Color couleur8 = new Color(0xC3D7DA);
    static final Color[] COLOR_ARRAY = { couleur1, couleur2, couleur3, couleur4, couleur5, couleur6, couleur7, couleur1, couleur2, couleur3 };
    static final int X_START = 50;
    static final int X_END = 500;
    static final int Y_END = 300;
    static final int ROD_LENGTH = 200;
    static final int ROD_GAP = 150;
    static final int SIDE_GAP = 75;
    static final int THICKNESS = 3;
    static final int STRING_ADJUST = 30;

   
    private Rods rods; // L'objet Rods représentant l'état des tiges et des disques

    public MainComponent(Rods rods) {
        this.rods = rods; // Initialisation de la variable rods
    }

    // Méthode pour mettre à jour la vue
    public void update() {
        removeAll(); // Supprime tous les composants enfants
        revalidate(); // Revalide le conteneur
        repaint(); // Redessine le composant
    }

    // Méthode pour mettre à jour l'objet rods et redessiner
    public void updateRods(Rods newRods) {
        rods = newRods; // Met à jour la variable rods
        removeAll(); // Supprime tous les composants enfants
        revalidate(); // Revalide le conteneur
        repaint(); // Redessine le composant
    }

    // Méthode pour dessiner le composant
    public void paintComponent(Graphics g) {
        paintRods(g); // Dessine les tiges

        Rod[] rodArray = rods.getRodArray(); // Obtient le tableau des tiges
        for (int i = 0; i < rodArray.length; i++) {
            Stack<Disk> disksOnTop = rodArray[i].getDisksOnTop(); // Obtient la pile de disques sur la tige
            for (int j = 0; j < disksOnTop.size(); j++) {
                paintDisk(disksOnTop.get(j), i, 1 + j, g); // Dessine chaque disque
            }
        }

        g.setColor(Color.WHITE); // Définit la couleur de dessin à blanc
        Font font = new Font("Arial", Font.PLAIN, 12); // Définit la police à Arial, taille 12
        g.setFont(font);// Définit la police dans Graphics

        // Ajustement des coordonnées x pour centrer les textes au-dessus des tiges
        int startX = X_START + SIDE_GAP - g.getFontMetrics().stringWidth("Début") / 2;
        int spareX = X_START + SIDE_GAP + ROD_GAP - g.getFontMetrics().stringWidth("Supplémentaire") / 2;
        int destinationX = X_END - SIDE_GAP - g.getFontMetrics().stringWidth("Destination ");

        // Dessine les textes
        g.drawString("Début", startX + 115, Y_END + STRING_ADJUST);
        g.drawString("Supplémentaire", spareX + 170, Y_END + STRING_ADJUST);
        g.drawString("Destination ", destinationX + 270, Y_END + STRING_ADJUST);
    }

    // Méthode pour dessiner les tiges
    private void paintRods(Graphics g) {
        Graphics2D g2D = (Graphics2D) g;
        Color customColor = new Color(70, 0, 0); // Couleur personnalisée pour les tiges
        g.setColor(customColor);
        g2D.setStroke(new BasicStroke(10)); // Définit l'épaisseur des lignes

        // Dessine la plateforme
        int platformX = 130; // Position X de la plateforme
        int platformWidth = 650; // Largeur de la plateforme
        int platformY = 300; // Position Y de la plateforme
        int platformHeight = 100; // Hauteur de la plateforme
        int arcWidth = 40; // Largeur de l'arc pour les coins arrondis
        int arcHeight = 20; // Hauteur de l'arc pour les coins arrondis

        g2D.setColor(Color.BLACK);
        g2D.drawRoundRect(platformX, platformY, platformWidth, platformHeight, arcWidth, arcHeight); // Dessine le contour de la plateforme
        g2D.setColor(customColor);
        g2D.fillRoundRect(platformX, platformY, platformWidth, platformHeight, arcWidth, arcHeight); // Remplit la plateforme

        // Dessine les tiges
        int rodX1 = platformX + platformWidth / 6; // Position de la première tige
        int rodX2 = platformX + 2 * platformWidth / 6 + 100; // Position de la deuxième tige
        int rodX3 = platformX + 4 * platformWidth / 6 + 100; // Position de la troisième tige
        int rodLength = 200; // Longueur des tiges
        int rodY = platformY - rodLength; // Position Y des tiges

        g.setColor(Color.BLACK);
        g.drawLine(rodX1, rodY, rodX1, platformY); // Dessine la première tige
        g.drawLine(rodX2, rodY, rodX2, platformY); // Dessine la deuxième tige
        g.drawLine(rodX3, rodY, rodX3, platformY); // Dessine la troisième tige
    }

         // Méthode pour dessiner un disque
    private void paintDisk(Disk toDraw, int rodNumber, int order, Graphics g) {
        int diskSize = toDraw.getSize(); // Taille du disque
        int separation = 2; // Séparation entre les disques
        Graphics2D g2D = (Graphics2D) g;
        g2D.setStroke(new BasicStroke(THICKNESS - 1));
        g.setColor(Color.BLACK);
        int diskWidth = diskSize * Disk.THICKNESS; // Largeur du disque

        // Positions des tiges
        int platformX = 130; // Position X de la plateforme
        int platformWidth = 650; // Largeur de la plateforme
        int rodX1 = platformX + platformWidth / 6;
        int rodX2 = platformX + 2 * platformWidth / 6 + 100;
        int rodX3 = platformX + 4 * platformWidth / 6 + 100;

        // Position X du milieu de la tige spécifiée par rodNumber
        int middleRodX = 0;
        switch (rodNumber) {
            case 0:
                middleRodX = rodX1;
                break;
            case 1:
                middleRodX = rodX2;
                break;
            case 2:
                middleRodX = rodX3;
                break;
        }

        // Calcul de la position X du disque centré sur la tige
        int diskX = middleRodX - (diskWidth / 2);

        // Ajustement de la position Y en fonction de l'ordre et de la séparation
        int diskY = Y_END - Disk.THICKNESS * order - (separation * order) - 4;

        // Dessiner le disque avec des coins arrondis
        int cornerRadius = 5; // Rayon des coins arrondis
        g.drawRoundRect(diskX, diskY, diskWidth, Disk.THICKNESS, cornerRadius, cornerRadius); // Dessine le contour du disque
        g.setColor(COLOR_ARRAY[COLOR_ARRAY.length - diskSize]); // Définit la couleur du disque
        g.fillRoundRect(diskX, diskY, diskWidth, Disk.THICKNESS, cornerRadius, cornerRadius); // Remplit le disque
    }
}
