#include "../headers/lien.h"

// variable global qui fait le lien entre l'interface et la communication client
Lien lien;


// Creer le lien entre GUI et communication Socket
void create_link(){
    // Si le clique est autorisé
    lien.able_click = 0;
    lien.choice = -1;    
    // Joueur a appuyé sur un bouton Oui / Non
    lien.is_choice_ok = false;
    // Choix de fin de partie Recommencer / Quitter
    lien.restart_choice = false;
    // Choix de fin de partie cliqué Oui / Non
    lien.is_restart_clicked = false;
    // Gagnant
    lien.is_winner = false;
}
