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
- [Présentation de l'équipe](#team)
- [Organisation du travail dans le groupe](#work_distribution)
- [Méthodologie de développement](#methodology)
- [Avancement du projet et justification des choix](#justify)
- [ Difficultés rencontrées](#difficulties)
- [Régles de communication](#communications_rules)
- [Les difficultés](#difficulties)
- [Bilan](#bilan)

Fonctionnement
- [Build](#build)
- [Configuration Serveur](#config_server)
- [Configuration Client](#config_client)
- [Documentation](#doc)

<hr>

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

<hr>

<h1>Travail effectué</h1>

## 🧐 Présentation de l'équipe <a name = "team"></a>

Notre équipe est composée de 4 étudiants : 
 - Nicola : Originaire de BTS SNIR
 - Alexis : Originaire de BTS SNIR
 - Tarik : Originaire de BTS SIO Option SLAM
 - Yannis : Originaire de BTS SIO Option SLAM

## 🧐 Organisation du travail dans le groupe <a name = "work_distribution"></a>

Avant de commencer à coder, nous avons écrit sur papier les différents points clés à réaliser afin d’établir les objectifs du projet. Une fois le cahier des charges rédigé, nous avons choisi de se répartir, entre chaque membre du groupe, les grandes parties du projet
- Partie client :
  - Réalisation de l’interface graphique - Tarik SAGLAMER
  - Réalisation de la communication client - Alexis REVOL
- Partie serveur :
  - Réalisation de la logistique du jeu - Nicola PIEMONTESE
  - Réalisation de la communication serveur - Yannis TEISSIER 
  
Ainsi chaque membre a pu se concentrer sur la réalisation de sa partie, cependant les parties étant étroitement liées, une communication permanente a été mise en place afin de s’assurer de la cohérence entre chaque branche du projet.

## 🧐 Méthodologie <a name = "methodology"></a>

Afin de s'organiser et de réaliser le projet, nous avons commencé par écrire les différents points à réaliser.

Dans un second temps, nous nous sommes organisés sur Github à l'aide de différentes branches.

Une branche main vide dans le cas où une mauvaise manipulation venait à être faite. Une branche client pour la partie production client. Une branche serveur pour la partie production serveur. Une branche par personne pour la partie de développement.
Nous avons également créé un serveur discord afin de communiquer efficacement sur le projet.

Notre approche du travail s'est basée sur une méthodologie de développement agile personnalisée. Les heures de cours étaient principalement utilisées pour la correction de bug, la discussion, le code review et la rédaction des points à réaliser et des améliorations à apporter. Pour la partie développement, nous avons utilisé nos heures libres.
Dans le cas ou un bug était détecté, deux solutions ont été proposées :
- Résolution directe par la personne ayant détecté le bug
- Résolution par la personne ayant développé le code

Régulièrement, nous faisions des codes reviews nous permettant de mettre en commun le travail réalisé et de voir les changements effectués par les autres membres.

<h5>Distribution des tâches</h5>
```

Partie Graphisme :

- timer visuel pour début de round
- fenetre de choix avec timer, numero de round (bloquer les boutons lorsque choix est deja fait)
- afficher le resultat + timer
- afficher resultat fin de round
- fin de partie (se reconnecter)

Partie communication client:

- connexion en fonction de la configuration du client pour la connexion au serveur (ip port)
- mise en forme des communications (protocole)

Partie communication serveur:

- Mettre en place une configuration pour le serveur (ip port)
- interpretation des communications (protocole)

Partie logique du jeu:

- lire la configuration du jeu
- gerer le nombre de joueurs
- envoyer les instructions de début si le nombre de joueurs est bon
- attendre la reponse
- afficher les resultats
- stocker dans un fichier les resultats
- relancer un round si le nombre de rounds est inferieur au nombre de rounds dans le fichier de configuration
```


## 🧐 Avancement du projet et justification des choix <a name = "justify"></a>

<h4>Justification des choix</h4>

Pour établir la communication entre un client et le serveur, nous avons choisi d’utiliser les sockets afin de transmettre des structures contenant les informations pertinentes à manipuler et traiter. Le client et le serveur possédants les mêmes structures cela permet de s’assurer que la forme de l’information envoyée sera la même que celle de l’information attendue à la réception. Nous avons choisi d’établir un protocole de communication entre le client et le serveur afin que la communication entre chaque partie suive une ligne identique.

Pour réaliser l’interface graphique, nous avons utilisé GTK qui permet de réaliser des fenêtres graphiques personnalisables ce qui est idéal pour la réalisation du plateau de jeu. L’interface est composée des boutons pour jouer (trahir et collaborer) ainsi que de zones de textes permettant d’afficher les informations utiles pour le joueur. Ainsi lorsque dans le protocole de communication client/serveur nous souhaitons transmettre le choix de jeu réalisé par le client nous écoutons sur quel bouton le joueur à cliqué afin d’enregistrer et de traiter l’information. Lorsque le client réceptionne des informations du serveur il peut alors les fournir à l’interface graphique afin de les afficher

Pour réaliser la logistique du jeu, nous avons choisi d’établir des règles qui permettent ainsi de traiter les informations  de manière efficace en s’assurant de conserver leur pertinence. Nous avons également choisi de réaliser des fichiers de configurations  lues au lancement du jeu, ceux-ci contenant des informations telles que l’adresse du serveur, le port, des règles du jeu... Cela permet, en cas de changement de l’adresse du serveur ou de certaines règles du jeu, de ne pas avoir à modifier les programmes ce qui facilite l’évolutivité et l’adaptation aux changements des programmes.

<h4>Justification des choix</h4>

Aujourd’hui le client et le serveur sont capables de lire leurs fichiers de configuration réceptifs, le serveur écoute les connexions entrantes et les place dans une file d’attente. Lorsque 2 clients sont disponibles dans la file d'attente, il lance la communication permettant de jouer en fournissant les informations de début de partie au client.

Ainsi lorsque le client lance le jeu il est informé par un message que la partie se charge le temps que le serveur lui informe qu’une partie va débuter. Une fois le jeu commencé le client indique que le joueur peut jouer en cliquant sur un bouton, puis lors d’un clic il envoie l’information au serveur. Le serveur attend de recevoir les réponses des 2 joueurs, le joueur est alors informé qu’il est en attente de la réponse de l’adversaire s’il n’a pas encore joué.

Lorsque le serveur a reçu les réponses des 2 joueurs, ils les traitent afin d’établir un score et il transmet au client le résultat du round, le client peut alors fournir à l’interface graphique le résultat du round (choix de l’adversaire, score de chaque joueur, etc…) afin de les afficher pour que le joueur soit informé du résultat du round et de ce qui a été effectué. Le joueur peut observer les résultats du round (durant 3 secondes) puis il est informé qu’un nouveau round commence et le schéma se répète.

Lorsque le serveur indique au client que la partie est terminée, le client affiché sur l’interface graphique un bouton pour rejouer ainsi que le nom du gagnant, si le joueur clique dessus alors le client est replacé dans la file d’attente du serveur, s’il quitte la partie le serveur ferme la connexion du client.

Ainsi plusieurs joueurs peuvent jouer au dilemme du prisonnier en réseau (multi-joueurs) et peuvent recommencer des parties afin de tomber contre d’autres adversaires !

Enfin les résultats d’une partie sont aussi stockés dans un fichier CSV pouvant être lu avec un logiciel de tableur comme Excel.

## 🧐 Règles de communication <a name = "communications_rules"></a>

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

## 🧐 Difficultés rencontrées <a name = "difficulties"></a>

Durant la réalisation du projet nous avons été confrontés à différentes difficultés. Tout d’abord nous avons rencontré des difficultés liées à la programmation. En effet nous avons dû nous coordonner puisque chacun d’entre nous à des manières différentes de programmer, ainsi nous avons dû adapter certaines parties du code afin qu'elles fonctionnent avec le reste du projet. De plus, nous avons dû résoudre plusieurs problèmes liés à des bugs de mémoire.

Nous avons aussi passé du temps à établir une communication entre le serveur et les clients stables . En effet, nous devions réaliser une connexion permettant l’envoi de structure complexe, avec un protocole clair et simple.

D'autres difficultés liées à la méthodologie sont aussi apparues. Ainsi puisque que toutes nos parties sont finalement liées entre elles, il nous est apparu nécessaire de bien se coordonner et de se tenir à jour des modifications des autres membres afin que les changements ne perturbent pas l'avancée des autres.

Concernant la partie graphique nous nous sommes mis d’accord sur une interface graphique qui soit simple et avons dû l'adapter afin de pouvoir la faire communiquer avec le client.

Finalement plusieurs difficultés étaient dues au fait qu’aucun de nous quatre n’avait auparavant déjà programmé d’interfaces graphiques ou de communication client-serveur en C.

## 🧐 Bilan <a name = "bilan"></a>

Au cours de ce projet nous avons su mettre en avant les compétences acquises au cours de ce module de développement et les compléter en recherchant des solutions pour résoudre des problèmes spécifiques au projet. Ce projet a nécessité de l’autonomie sur les réflexions et les choix des méthodes à apporter pour réaliser le travail demandé. Nous avons pu découvrir de nouvelles fonctionnalités telles que l'utilisation des sockets qui est une compétence nécessaire à maîtriser lorsqu’on souhaite réaliser des programmes en réseau, ou encore la gestion des événements qui est une notion importante à comprendre lors de la réalisation d’interface graphique.

Nous avons ainsi su réaliser une application structurée et évolutive où chaque élément a une organisation précise.

De plus, ce projet nous a permis de découvrir de nouvelles façons de développer en mettant la communication au cœur du projet, ce qui fut très enrichissant et valorisant.


<hr>

<h1>Fonctionnement</h1>

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
./build_unix>.sh
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

Via la ligne de commande.

Unix
```
cd client || exit
mkdir build
cd build || exit
cmake ..
make doc

cd ../..

cd server || exit
mkdir build
cd build || exit
cmake ..
make doc
cd ../..

mkdir documentation
mkdir -r documentation/client
cp -r client/doc/html documentation/client
mkdir -r documentation/server
cp -r server/doc/html documentation/server
```


Pour accéder à la documentation, il suffit de lancer le fichier *index.html* du dossier *documentation/client* ou *documentation/server* dans un navigateur web.
