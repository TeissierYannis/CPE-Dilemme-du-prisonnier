al envoi depuis le client
ya reception coté serveur
ni regles du jeu
ta graphisme

graphisme
- timer visuel pour début de round
- fenetre de choix avec timer, numero de round (bloquer les boutons lorsque choix est deja fait)
- afficher le resultat + timer
- afficher resultat fin de round
- fin de partie (se reconnecter)

envoi depuis le client
- connexion config serveur (ip port)
- mise en forme des communications

reception coté serveur
- setup config serveur (ip port)
- interpretation des communications

regles du jeu
- lire la config
- gerer le nombre de joueurs
- envoyer les instructions de début si nb joueurs ok
- attendre la reponse
- afficher les resultats
- stocker en fichier les resultats
- relance un round si nb round < nb round config

// Client
// connexion
join
// reponse
answer <no partie> <numero joueur> <reponse Trahir|Collaborer>
// disconnect
logout <no partie> <no joueur>
// Serveur
// validation connexion
connected <numero joueur> <numero de partie>

// debut de partie
start <numero de partie> <no round>
// resultats
result_round <no partie> <j1 sanction> <j2 sanction>
result_party <no partie> <LIST<j1 sanctions>> <LIST<j2 sanctions>>