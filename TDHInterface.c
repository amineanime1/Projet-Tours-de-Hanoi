#include <gtk/gtk.h>

// Déclarez vos algorithmes récursif et itératif ici

static void runRecursive(GtkWidget *widget, gpointer data) {
    // Appel de votre algorithme récursif
}

static void runIterative(GtkWidget *widget, gpointer data) {
    // Appel de votre algorithme itératif
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button_recursive;
    GtkWidget *button_iterative;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Tours de Hanoï");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    button_recursive = gtk_button_new_with_label("Exécuter récursif");
    g_signal_connect(button_recursive, "clicked", G_CALLBACK(runRecursive), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_recursive, 0, 0, 1, 1);

    button_iterative = gtk_button_new_with_label("Exécuter itératif");
    g_signal_connect(button_iterative, "clicked", G_CALLBACK(runIterative), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_iterative, 1, 0, 1, 1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
