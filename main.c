#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Dilemme du prisonnier");
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pHBox;
    GtkWidget *pMenuBar;
    GtkWidget *pMenu;
    GtkWidget *pMenuItem;
    GtkWidget *pButton[1];


    gtk_init(&argc, &argv);

    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);



/* ------------------------------------------------Boutons Collaboration et Trahison----------------------------------------------------- */


    /* Création de la GtkBox verticale */
    pVBox = gtk_vbox_new(TRUE, 0);
    /* Ajout de la GtkVBox dans la fenêtre */
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);


    /* Creation des boutons */
    pButton[0] = gtk_button_new_with_label("Collaboration");
    pButton[1] = gtk_button_new_with_label("trahison");

    /* Ajout des boutons 2 et 3 dans la GtkHBox */
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[0], TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pHBox), pButton[1], TRUE, FALSE, 0);


/* ---------------------------------------------------Création du menu--------------------------------------------------------------- */

    /**** Création du menu ****/
 
    /* ÉTAPE 1 */
    pMenuBar = gtk_menu_bar_new();
    /** Premier sous-menu **/
    /* ÉTAPE 2 */
    pMenu = gtk_menu_new();
    /* ÉTAPE 3 */
    pMenuItem = gtk_menu_item_new_with_label("Nouvelle partie");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
 
    pMenuItem = gtk_menu_item_new_with_label("Résultats");
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

    pMenuItem = gtk_menu_item_new_with_label("Quitter le jeu");
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitter),(GtkWidget*) pWindow);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
    /* ÉTAPE 4 */
    pMenuItem = gtk_menu_item_new_with_label("Options");
    /* ÉTAPE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    /* ÉTAPE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

    /* Ajout du menu a la fenêtre */
    gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
 


    gtk_widget_show_all(pWindow);
 
    gtk_main();
 
    return status;
}

void OnQuitter(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;
 
    pQuestion = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez vous vraiment\n"
        "quitter le programme?");
 
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NONE:
        case GTK_RESPONSE_NO:
            gtk_widget_destroy(pQuestion);
            break;
    }
}

int timer_handler() {
    elapsed_time++;
    char txt[100];
    printf("timer running, time : %d\n", elapsed_time);
    GtkLabel *timelabel = GTK_LABEL(gtk_builder_get_object(builder, "time_display"));
    snprintf(txt, 100, "%04i", elapsed_time);
    gtk_label_set_text(timelabel, txt);
    return 1;
}