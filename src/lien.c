#include "../headers/lien.h"

// variable global qui fait le lien entre l'interface et la communication client
Lien lien;


// Creer le lien entre GUI et communication Socket
void create_link(){
    // Choix Trahir (0) / Collaborer (1) des deux joueurs
    lien.choix_j1 = -1;
    lien.choix_j2 = -1;
    // Score des 2 joueurs
    lien.score_j1 = 0;
    lien.score_j2 = 0;
    // Numero du round
    lien.nb_round = 0;
    // Si le clique est autorisé
    lien.able_click = 0;
    
    // Resultat du round reçue Oui / Non
    lien.is_answer_ok = 0;
    // Joueur a appuyé sur un bouton Oui / Non
    lien.is_choice_ok = 0;
    // Partie finie Oui / Non
    lien.is_game_end = 0;
    // Choix de fin de partie Recommencer / Quitter
    lien.restart_choice = false;
    // Choix de fin de partie cliqué Oui / Non
    lien.is_restart_clicked = false;
    // Gagnant
    lien.is_winner = false;
}
