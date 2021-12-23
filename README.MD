<h1 align="center">CPE Lyon - 3ICS - Année 2021/22
Développement informatique – 2
Projet </h1>

<div align="center">

[![CTF](https://img.shields.io/badge/CPE_LYON-2021-blue.svg)](https://france-cybersecurity-challenge.fr/)
[![CTF](https://img.shields.io/badge/Language-C-yellow.svg)](#)
[![CTF](https://img.shields.io/badge/Category-Network/C-red.svg)](#)

</div>

--- 

## 📝 Table des matières

Consignes de l'épreuve
- [Contexte](#context)
- [Fonctionnalités du système](#features)
- [Serveur](#features_server)
- [Client](#features_client)
- [Architecture du système informatisé](#archi)
- [Gestion des données](#data_monitoring)
- [Gestion des échanges client/serveur](#communication)
- [Consignes](#consignes)
- [Travail de base demandé](#consigne_base)
- [Support](#consigne_support)
- [Évaluation du travail](#eval)
- [Soutenance](#eval_oral)
- [Rapport](#eval_rapport)

Travail effectué
- [L'équipe](#team)
- [Répartition du travail](#work_distribution)
- [Méthodologie](#methodology)
- [Justification des choix](#justify)
- [Régles de communication](#communications_rules)
- [Les difficultés](#difficulties)
- [Bilan](#bilan)

Fonctionnement
- [Build](#build)
- [Configuration Serveur](#config_server)
- [Configuration Client](#config_client)
- [Documentation](#doc)

## 🧐 Enoncé <a name = "context"></a>

l’ICS (institue of Cognitives Sciences) est un laboratoire interdisciplinaire qui intègre l'expertise de
chercheurs des Sciences de la Vie (psychologie cognitive, neurosciences) et de médecine (pédopsychiatrie, neuro-pediatrie) avec celle de chercheurs des Sciences Humaines et Sociales
(linguistique computationelle et théorique et philosophie) pour étudier la nature et la spécificité de
l'esprit humain.

L’un des doctorants travaille sur la théorie des jeux, à la frontière de la psychologie et des
mathématiques, et notamment sur les jeux a somme non constante. Une des illustrations la plus
connue de ces jeux est le dilemme du prisonnier :
 - https://fr.wikipedia.org/wiki/Dilemme_du_prisonnier

Ces deux vidéos devraient vous éclairer sur la théorie des jeux :
 - https://www.youtube.com/watch?v=StRqGx9ri2I, notamment à partir de 7’15’’.
 - https://www.youtube.com/watch?v=uijJJ2OczNs&t=913s

Le doctorant, qui n’est pas un développeur, a besoin d’accumuler des données expérimentales. Il a
besoin que des volontaires jouent l’un contre l’autre un nombre de fois à définir, sans jamais savoir
qui sont leurs adversaires.

On définira une partie comme étant un certain nombre de rounds. Un round est défini comme une
confrontation trahison-collaboration entre les deux volontaires.

Le doctorant a travaillé avec l’ingénieur d’études du laboratoire pour définir un cahier des charges.
L’ingénieur d’études à un planning très chargé, mais il a amorcé les projets (le code du serveur et le
code du client). Il a aussi prévu quelques heures pour vous exposer l’état des projets et le principe
de fonctionnement (gestion des sockets, gestion des connexions, communication asynchrone,
multitâche). Il vous présentera aussi les outils nécessaires pour développer une interface graphique
avec GTK pour l’application cliente.

Vous (le chef de projet) avez été contacté pour mettre en place une équipe (2 dev + 2 réseaux) afin
de développer les deux applications le plus rapidement possible.


## 🧐 Fonctionnalités du système <a name = "features"></a>

Le système informatique doit être paramétrable par un non-informaticien et doit permettre d’obtenir
et conserver les résultats des multiples expérimentations.

Vous devez tenir compte du fait qu’il peut y avoir plusieurs parties simultanément (deux
actuellement, étant tenu compte du matériel dont dispose le laboratoire) et que prochainement le
laboratoire disposera encore de quelques ordinateurs supplémentaires.

## 🧐 Serveur <a name = "features_server"></a>

Le serveur doit être paramétrable. Le fichier de paramétrage permettra de définir l’adresse IP et le
port sur lequel l’application serveur sera à l’écoute.

Le fichier contiendra aussi le paramétrage nécessaire pour définir les réglés du jeu : somme engagée
a chaque partie, le nombre de parties et d’autres informations qui vous sembleront nécessaires.

A la fin de la partie, le serveur doit garder dans un fichier (le format est à définir) les choix de
chacun des joueurs, ainsi que le temps de décision et les montants accumulés ou perdus.

## 🧐 Client <a name = "features_client"></a>

Le fichier de paramétrage du client doit contenir l’adresse IP du serveur ainsi que le port et tout
autre paramétrage qui vous sembleront pertinents.

L’interface graphique des clients doit rester très simple : le cobaye ne doit pas être déconcentré par
des fioritures :
- deux boutons cliquables (Trahir, Collaborer)
- le résultat du round (il doit savoir s’il a gagné ou perdu)
- Il doit être informé du début de chaque round.

## 🧐 Architecture du système informatisé <a name = "archi"></a>

Le laboratoire dispose de plusieurs ordinateurs connectés entre eux, chacun dans un box afin que les
volontaires ne se rencontrent pas, d’un ordinateur pour la supervision, d’un serveur et d’une
imprimante en réseau.

## 🧐 Gestion des données <a name = "data_monitoring"></a>

Le serveur central a la charge de l’ensemble des données. Les données manipulées par le serveur
sont de nature persistante, c’est-à-dire qu’elles doivent survivre à l’exécution de l’application

## 🧐 Gestion des échanges client/serveur <a name = "communication"></a>

Les échanges entre les clients et le serveur doivent suivre un protocole bien défini pour que le
serveur comprenne les requêtes des clients et pour que les clients comprennent les résultats
renvoyés par le serveur. Les échanges doivent être considérés au niveau applicatif et au niveau
transport.

Au niveau applicatif, vous devrez définir la structure des messages qui sont échangés. Vous êtes
invité à voir la définition d’un RFC. Le RFC pour le protocole HTTP est l’un des plus simple a
appréhender (https://tools.ietf.org/html/rfc2616).

Au niveau transport, il est imposé d’utiliser le protocole TCP/IP. 

## 🧐 Consignes <a name = "consigne"></a>
## 🧐 Travail de base demandé <a name = "consigne_base"></a>

Vous disposez d’un squelette de programme pour l’application serveur et un autre pour l’application
client. Après lecture des différents documents, il faudra le compléter pour fournir :

Aspect réseau : un client et un serveur en mode TCP (le squelette de base est opérationnel)

Aspect système :
- un serveur parallèle. Le code qui vous est fourni utilise des threads pour pouvoir
  gérer des connexions en parallèle et faire du multitâche pour le traitement des requêtes.
- un client asynchrone capable de traiter les messages du serveur dès leurs réceptions.
  Dans tous les cas, avant de commencer à coder ces questions, faites une analyse des problèmes
  que vous voulez résoudre et des solutions que vous allez proposer. Si cette analyse est bien faite, le
  codage sera facile. Une bonne analyse (même sans implémentation) dans le rapport et la soutenance
  sera fortement valorisée.

  Nous vous conseillons de :
– bien respecter le cahier des charges 
- bien gérer le temps qui vous est imparti 
- bien discuter dans le quadrinome 
- réfléchir avant de programmer. 
- structurer votre code pour le rendre le plus évolutif possible. 
- utiliser des assertions 
- bien formalisez le protocole (faite des simulations entre vous). 
- penser aux évolutions possibles du projet : par exemple l’état du serveur et des clients
  pourra être supervisé depuis un poste de… supervision.

  Tout le code doit bien sur être versionné. Comme toujours vous donnerez un accès à votre dépôt a
  votre enseignant.

  Vous serez très attentif aux commentaires et annotations. Il est impératif de fournir une
  documentation (Javadoc ou Doxygen).

  La présence d’assertion dans le code est un impératif, cependant les tests unitaires ne sont pas
  nécessaires.

## 🧐 Support <a name = "consigne_support"></a>

Vous serez encadré pendant tout le projet. Souvenez-vous cependant que votre enseignant n’est pas
un ‘degugger’. Vous pouvez le contacter par mail, mais l’enseignant n’est pas 24h/24 devant son
ordinateur : prévoyez donc un certain délai dans les réponses. Plus la question est précise
(nécessitant donc une réponse courte), plus la réponse sera rapide.

## 🧐 Évaluation du travail <a name = "eval"></a>

## 🧐 Soutenance <a name = "eval_oral"></a>

Chaque groupe aura 20 minutes, diapositives à l’appui, pour présenter son travail. Le groupe
expliquera brièvement la répartition du travail dans le quadrinôme, l’avancement du projet et les
problèmes rencontrés. Il devra aussi expliquer et justifier les choix effectués pour les
implémentations. Le jury posera ensuite des questions et demandera éventuellement des
démonstrations. 

## 🧐 Rapport <a name = "eval_rapport"></a>

Le quadrinome doit rendre avant la soutenance un rapport de 4 pages (+2 pages d’annexes)
maximum donnant :
- l’organisation du travail dans le groupe ; 
- la méthodologie utilisée dans le développement ; 
- La justification de certains choix et l’évaluation de la pertinence à posteriori; 
- l’état courant du projet et ce qu’il reste à réaliser ; 
- les difficultés rencontrées ; 
- un rapide bilan de ce que vous a apporté ce projet.

Le rapport ne doit pas redonner des informations présentes dans ce document. Il doit contenir
suffisamment d’élément pour permettre au doctorant de prendre en main l’application. Le
README.md contiendra les éléments nécessaires pour utiliser les programmes, avec les formats
des fichiers de paramétrages, les formats des fichiers de données, les commandes nécessaires pour
compiler le code source.

Toutes les informations nécessaires à la poursuite du développement devront être stockées dans des
fichiers de documentation (répertoire doc) présent dans le projet (description du protocole par
exemple)



## 🧐 L'équipe <a name = "team"></a>

Notre équipe est composée de 4 étudiants : 
 - Nicola : Originaire de BTS ...
 - Alexis : Originaire de BTS ...
 - Tarik : Originaire de BTS ...
 - Yannis : Originaire de BTS SIO Option SLAM

## 🧐 Répartition du travail <a name = "work_distribution"></a>

Pour commencer, nous avons constitué deux groupes de travail : 
 - Tarik et Alexis : Partie client
 - Yannis et Nicola : Partie serveur

Pour la partie client, Tarik s'est occupé de la partie GUI et Alexis de la partie de communication.

Pour la partie serveur, Nicola s'est occupé de la partie logique du jeu, et Yannis de la communication.


## 🧐 Méthodologie <a name = "methodology"></a>

Afin de s'organiser et de réaliser le projet, nous avons commencé par écrire les différents points à réaliser.

```

graphisme :

- timer visuel pour début de round
- fenetre de choix avec timer, numero de round (bloquer les boutons lorsque choix est deja fait)
- afficher le resultat + timer
- afficher resultat fin de round
- fin de partie (se reconnecter)

envoi depuis le client:

- connexion config serveur (ip port)
- mise en forme des communications

reception coté serveur:

- setup config serveur (ip port)
- interpretation des communications

regles du jeu:

- lire la config
- gerer le nombre de joueurs
- envoyer les instructions de début si nb joueurs ok
- attendre la reponse
- afficher les resultats
- stocker en fichier les resultats
- relance un round si nb round < nb round config
```

Dans un second temps, nous nous sommes organisés sur Github à l'aide de différentes branches.

Une branche main vide dans le cas ou une mauvaise manipulation venait à être faite.
Une branche client pour la partie production client.
Une branche serveur pour la partie production serveur.

Une branche par personne pour la partie de développement.

Nous avons également créée un serveur discord afin de communiquer efficacement sur le projet.

Notre approche du travail s'est basée sur une méthodologie de développement agile personnalisée.

Les heures de cours étaient principalement utilisées pour la correction de bug, la discussion, le code review et la rédaction des points à réaliser et des améliorations à apporter.

Pour la partie développement, nous avons utilisé nos heures libre.

Dans le cas ou un bug était détecté, deux solutions ont été proposées :
- Résolution directe par la personne ayant detécté le bug
- Résolution par la personne ayant développé le code

Régulièrement, nous faisions des codes reviews nous permettant de voir les changements effectués par les autres membres. 


## 🧐 Justification des choix <a name = "justify"></a>
## 🧐 Régles de communication <a name = "communications_rules"></a>

Pour la communication, nous avons défini un protocole personnalisé.

```
Permet d'envoyer au client un identifiant pour le serveur et un identifiant local servant dans la partie client afin de définir le joueur 1 et le joueur 2 
id <id_client>:<id_local>

Permet d'envoyer le numéro de partie au client
party <id_party>

Permet d'envoyer un status (status de la partie ou status du client)
status <status>

Permet de communiquer les réponses des clients au serveur 
<answer_struct>

Permet de communiquer le recapitulatif d'un round au client
<round_struct>

Permet de communiquer l'id du winner au client
winner <int>

Permet de communiquer le recapitualtif de la partie au client
<recap_party>
```

## 🧐 Les difficultés <a name = "difficulties"></a>

Difficultés liées au code :
- Différentes manières d'écrire le code
- L'adaptation du code de chaque personne au projet
- Les différents types de bugs de mémoire
- L'envoi de structures complexes 

Difficultés liées à la communication :
- Les différents types de communication existant
- Définir un protocole personnalisé clair et simple

Difficultés liées à la méthodologie :
- Se coordonner avec les autres membres
- Se tenir à jour avec les autres membres
- Vérifier les changements des autres membres afin de pouvoir réaliser les changements

Difficultés liées à la nouveauté :
- La mise en place d'un serveur
- La mise en place d'un client
- La communication avec le serveur et le client
- Mise en place d'une interface graphique

Difficultés liées à la partie graphique :
- Choix du style de l'interface graphique
- Simplicité de l'interface graphique
- Brancher l'interface graphique au client

## 🧐 Bilan <a name = "bilan"></a>

Malgré les différentes difficultés rencontrées, nous avons réussi à réaliser le projet.
Nous en tirerons des bénéfices, et nous adopterons une méthodologie différente en tirant profit des différentes difficultés rencontrées.

Ce projet nous aura appris à traduire un concept en programme, en se basant sur le développement d'un client, un serveur et un interface graphique.

Nous partions de simples connaissances basique en c et aujourd'hui nous avons été capable de mettre à l'épreuve nos connaissances afin de fournir un rendu final.

## 🧐 Build <a name = "build"></a>

Préparation du build :
- Installation de la librairie GTK+3
- Installation de cmake
- Installation de make
- Installation de GCC ou un autre compilateur
- Installation de git
- Installation de Doxygen

Afin de compiler le projet nous vous proposons deux solutions :

Via un script adapté à la machine que vous utilisez (Linux, MacOS)

Pour Linux et MacOS, il faut choisir le script "build_unix.sh"

Il faut ensuite ouvrir un terminal et lancer le script.
```bash
./build_<environnement>.sh
```

Dans le dossier *output*, il y aura un executable "client" et un executable "server".

Dans le dossier "client_config", vous y trouverez les fichiers de configuration du client.

Et dans le dossier "server_config", vous y trouverez les fichiers de configuration du serveur.

Via la ligne de commande.

Unix
```
cd server
mkdir build
cd build
cmake ..
make all
cp server ../server

cd ..

cd client
mkdir build
cd build
cmake ..
make all
cp client ../client
```

## 🧐 Configuration Serveur <a name = "config_server"></a>

Il existe deux fichiers de configurations pour le serveur :
- server_config/rules_config.json
- server_config/server_config.json

Le fichier *server_config.json* permet de configurer la partie écoute du serveur.

````json
{
  "ip_address": "127.0.0.1",
  "port": "30000"
}
````

Il suffit de modifier les valeurs de l'ip_address avec l'ip d'écoute et du port avec le port d'écoute.

Le fichier *rules_config.json* permet de configurer les règles du jeu.

````json
{
    "nb_round": "3",
    "default_wallet": "0",

    "trahison_win": "-5",
    "trahison_loose": "-5",

    "collab_win": "-1",
    "collab_loose": "-1",
    
    "trahison_collab_win": "0",
    "trahison_collab_loose": "-10"    
}
````

*nb_round* correspond au nombre de round que la partie aura.
```
"nb_round": "3"
```

*default_wallet* correspond à la valeur de départ du porte-monnaie de chaque joueur.
```
"default_wallet": "0"
```

*trahison_win* correspond à la valeur de gain du joueur en cas de victoire contre un trahison.
```
"trahison_win": "-5"
```

*trahison_loose* correspond à la valeur de perte du joueur en cas de défaite contre un trahison.
```
"trahison_loose": "-5"
```

*collab_win* correspond à la valeur de gain du joueur en cas de victoire contre un collab.
```
"collab_win": "-1"
```

*collab_loose* correspond à la valeur de perte du joueur en cas de défaite contre un collab.
```
"collab_loose": "-1"
```

*trahison_collab_win* correspond à la valeur de gain du joueur en cas de victoire contre un trahison et un collab.
```
"trahison_collab_win": "0"
```

*trahison_collab_loose* correspond à la valeur de perte du joueur en cas de défaite contre un trahison et un collab.
```
"trahison_collab_loose": "-10"
```

## 🧐 Configuration Client <a name = "config_client"></a>
Pour la configuration du client il n'existe qu'un seul fichier de configuration:
- client_config/config.json

Le fichier *config.json* permet de configurer la partie connexion au serveur.

````json
{
  "ip_address": "127.0.0.1",
  "port": "30000"
}
````

Il suffit de modifier les valeurs de l'ip_address avec l'ip du serveur et du port du serveur.

## 🧐 Documentation <a name = "doc"></a>

Pour générer la documentation du projet, il suffit de lancer la commande suivante :
```bash
./build_unix_doc.sh
```

Pour accéder à la documentation, il suffit de lancer le fichier *index.html* du dossier *documentation/client* ou *documentation/server* dans un navigateur web.
