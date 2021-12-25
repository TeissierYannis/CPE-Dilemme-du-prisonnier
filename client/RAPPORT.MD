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

- [Présentation de l'équipe](#team)
- [Organisation du travail dans le groupe](#work_distribution)
- [Méthodologie de développement](#methodology)
- [Avancement du projet et justification des choix](#justify)
- [ Difficultés rencontrées](#difficulties)
- [Bilan](#bilan)

<hr>

<h1>Travail effectué</h1>

## 🧐 Présentation de l'équipe <a name = "team"></a>

Notre équipe est composée de 4 étudiants :
- Nicola : Originaire de BTS ...
- Alexis : Originaire de BTS ...
- Tarik : Originaire de BTS ...
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

## 🧐 Méthodologie de développement <a name = "methodology"></a>

Afin de s'organiser et de réaliser le projet, nous avons commencé par écrire les différents points à réaliser. ( Cf Annexe 1)

Dans un second temps, nous nous sommes organisés sur Github à l'aide de différentes branches.

Une branche main vide dans le cas où une mauvaise manipulation venait à être faite. Une branche client pour la partie production client. Une branche serveur pour la partie production serveur. Une branche par personne pour la partie de développement.
Nous avons également créé un serveur discord afin de communiquer efficacement sur le projet.

Notre approche du travail s'est basée sur une méthodologie de développement agile personnalisée. Les heures de cours étaient principalement utilisées pour la correction de bug, la discussion, le code review et la rédaction des points à réaliser et des améliorations à apporter. Pour la partie développement, nous avons utilisé nos heures libres.
Dans le cas ou un bug était détecté, deux solutions ont été proposées :
- Résolution directe par la personne ayant détecté le bug
- Résolution par la personne ayant développé le code

Régulièrement, nous faisions des codes reviews nous permettant de mettre en commun le travail réalisé et de voir les changements effectués par les autres membres.

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

