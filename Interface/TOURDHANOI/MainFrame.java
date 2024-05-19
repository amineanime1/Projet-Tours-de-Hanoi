import java.util.LinkedList;
import javax.swing.JOptionPane;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.Timer;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;

public class MainFrame extends JFrame {
    // Constantes
    private static final int FRAME_WIDTH = 950; // Largeur de la fenêtre
    private static final int FRAME_HEIGHT = 500; // Hauteur de la fenêtre
    private static final int RODS_WIDTH = 600; // Largeur du composant principal
    private static final int RODS_HEIGHT = 400; // Hauteur du composant principal
    private static final int INITIAL_NUMBER_OF_DISKS = 4; // Nombre initial de disques
    private static final int INITIAL_ROD = 0; // Tige initiale
    private static final String TITLE = "Tour d'Hanoï"; // Titre de la fenêtre
    private static final String DISK_NUMBER_LABEL = "Nombre de disques :"; // Étiquette pour la sélection du nombre de
                                                                           // disques
    private static final int DELAY = 700; // Délai pour le timer en millisecondes
    private static int score = 0; // Score initial

    // Variables d'instance
    private JPanel panel; // Panneau principal
    private JButton nextButton; // Bouton pour l'action "Next"
    private JButton animateButton; // Bouton pour l'action "Animate"
    JLabel diskNumberLabel, scoreLabel; // Étiquettes pour afficher le nombre de disques et le score
    JComboBox<Integer> diskNumberSelection; // ComboBox pour sélectionner le nombre de disques
    JComponent mainComponent; // Composant principal pour dessiner les tiges et les disques
    Rods rods; // Objet représentant les tiges et les disques
    Timer timer; // Timer pour l'animation
    LinkedList<Integer> movesToSolve; // Liste des mouvements pour résoudre le puzzle

    Color couleur8 = new Color(0xC3D7DA); // Couleur de fond personnalisée

    public MainFrame() {
        // Initialisation des tiges avec le nombre initial de disques et la tige
        // initiale
        rods = new Rods(INITIAL_NUMBER_OF_DISKS, INITIAL_ROD);
        rods.solveTowersOfHanoi(INITIAL_NUMBER_OF_DISKS, INITIAL_ROD, 1, 2); // Résoudre le puzzle
        rods.initializeRods(INITIAL_NUMBER_OF_DISKS, INITIAL_ROD); // Réinitialiser les tiges

        createComponents(); // Création des composants de l'interface utilisateur

        setTitle(TITLE); // Définition du titre de la fenêtre
        setSize(FRAME_WIDTH, FRAME_HEIGHT); // Définition de la taille de la fenêtre
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Définition de l'action de fermeture
        setResizable(false); // Interdiction de redimensionner la fenêtre
        setVisible(true); // Rendre la fenêtre visible
        setBackground(couleur8); // Définition de la couleur de fond
    }

    private void createComponents() {
        // Initialisation du timer avec un délai et un écouteur d'animation
        timer = new Timer(DELAY, new AnimationListener());

        // Création des boutons "Next" et "Animate"
        nextButton = new JButton("Next");
        animateButton = new JButton("Animate");

        // Ajout des écouteurs d'action aux boutons
        nextButton.addActionListener(new NextButtonListener());
        animateButton.addActionListener(new AnimateButtonListener());

        // Création du panneau principal avec BorderLayout
        panel = new JPanel(new BorderLayout());

        // Initialisation du composant principal pour dessiner les tiges et les disques
        mainComponent = new MainComponent(rods);
        mainComponent.setPreferredSize(new Dimension(RODS_WIDTH, RODS_HEIGHT));

        // Ajout du composant principal au centre du panneau principal
        panel.add(mainComponent, BorderLayout.CENTER);

        // Initialisation des étiquettes et du ComboBox
        diskNumberLabel = new JLabel(DISK_NUMBER_LABEL);
        scoreLabel = new JLabel(" Nombre de déplacements : " + score);
        panel.setBackground(couleur8); // Définition de la couleur de fond du panneau principal
        diskNumberSelection = new JComboBox<Integer>(new Integer[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
        diskNumberSelection.setSelectedItem(4); // Sélection initiale du ComboBox
        diskNumberSelection.addActionListener(new DiskNumberChoiceListener()); // Ajout de l'écouteur d'action au
                                                                               // ComboBox

        // Création d'un panneau pour l'étiquette du score
        JPanel scorePanel = new JPanel();
        scorePanel.add(scoreLabel);

        // Création des panneaux pour les boutons et le ComboBox
        JPanel animatePanel = new JPanel();
        animatePanel.add(animateButton);
        JPanel nextPanel = new JPanel();
        nextPanel.add(nextButton);
        JPanel selectionPanel = new JPanel();
        selectionPanel.add(diskNumberLabel);
        selectionPanel.add(diskNumberSelection);

        // Ajout des panneaux au panneau de boutons avec BorderLayout
        JPanel buttonsPanel = new JPanel(new BorderLayout());
        animatePanel.setBackground(couleur8);
        nextPanel.setBackground(couleur8);
        scorePanel.setBackground(couleur8);
        selectionPanel.setBackground(couleur8);
        buttonsPanel.add(animatePanel, BorderLayout.WEST); // Ajout du panneau "Animate" à gauche
        buttonsPanel.add(nextPanel, BorderLayout.EAST); // Ajout du panneau "Next" à droite
        buttonsPanel.add(scorePanel, BorderLayout.SOUTH); // Ajout du panneau du score en bas
        buttonsPanel.add(selectionPanel, BorderLayout.CENTER); // Ajout du panneau de sélection au centre

        // Ajout du panneau de boutons au nord du panneau principal
        panel.add(buttonsPanel, BorderLayout.NORTH);
        buttonsPanel.setBackground(couleur8); // Définition de la couleur de fond du panneau de boutons
        add(panel); // Ajout du panneau principal au frame
    }

    // Listener pour le bouton "Next"
    private class NextButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            timer.stop(); // Arrêter le timer
            movesToSolve = rods.getMovesToSolve(); // Obtenir les mouvements pour résoudre le puzzle
            if (!movesToSolve.isEmpty()) {
                // Effectuer le mouvement suivant
                rods.moveDisk(movesToSolve.removeFirst(), movesToSolve.removeFirst());
                ((MainComponent) mainComponent).update(); // Mettre à jour le composant principal
                score++; // Incrémenter le score
                updateScoreLabel(); // Mettre à jour l'étiquette du score
            }
            // Vérifier si tous les disques sont sur la troisième tige
            if (rods.getRodArray()[2].size() == (int) diskNumberSelection.getSelectedItem()) {
                JOptionPane.showMessageDialog(mainComponent, "Félicitations ! Vous avez terminé le jeu !", "Victoire",
                        JOptionPane.PLAIN_MESSAGE);
            }
        }
    }

    // Listener pour le bouton "Animate"
    private class AnimateButtonListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            timer.start(); // Démarrer le timer
            updateScoreLabel(); // Mettre à jour l'étiquette du score
        }
    }

    // Listener pour le timer
    private class AnimationListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            movesToSolve = rods.getMovesToSolve(); // Obtenir les mouvements pour résoudre le puzzle
            if (!movesToSolve.isEmpty()) {
                // Effectuer le mouvement suivant
                rods.moveDisk(movesToSolve.removeFirst(), movesToSolve.removeFirst());
                ((MainComponent) mainComponent).update(); // Mettre à jour le composant principal
                score++; // Incrémenter le score
                updateScoreLabel(); // Mettre à jour l'étiquette du score
            } else {
                timer.stop(); // Arrêter le timer
                JOptionPane.showMessageDialog(mainComponent, "Félicitations ! Vous avez terminé le jeu !",
                        "felicitation", JOptionPane.OK_CANCEL_OPTION);
            }
        }
    }

    // Listener pour la sélection du nombre de disques
    private class DiskNumberChoiceListener implements ActionListener {
        public void actionPerformed(ActionEvent event) {
            timer.stop(); // Arrêter le timer
            timer = new Timer(DELAY, new AnimationListener()); // Réinitialiser le timer
            rods = new Rods((int) diskNumberSelection.getSelectedItem(), INITIAL_ROD); // Réinitialiser les tiges
            ((MainComponent) mainComponent).updateRods(rods); // Mettre à jour les tiges dans le composant principal
            rods.solveTowersOfHanoi(rods.getRodArray()[INITIAL_ROD].getDisksOnTop().size(), INITIAL_ROD, 1, 2); // Résoudre
                                                                                                                // le
                                                                                                                // puzzle
            rods.initializeRods((int) diskNumberSelection.getSelectedItem(), INITIAL_ROD); // Réinitialiser les tiges

            score = 0; // Réinitialiser le score
            updateScoreLabel(); // Mettre à jour l'étiquette du score
        }
    }

    // Méthode pour mettre à jour l'étiquette du score
    private void updateScoreLabel() {
        scoreLabel.setText(" Nombre de déplacements : " + score);
    }
}
