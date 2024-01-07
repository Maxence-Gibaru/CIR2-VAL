# Modélisation simplifiée d’un système de transport de type « VAL

Projet CIR2 VAL.

## Table des matières

1. [Aperçu](#aperçu)
2. [Chiffres Clés](#chiffres-clés)
3. [Installation](#installation)
4. [Utilisation](#utilisation)
    - [Prérequis](#prérequis)
    - [Étapes pour lancer le programme](#étapes-pour-lancer-le-programme)
    - [Fonctionnalités de l'interface](#fonctionnalités-de-linterface-sfml)
5. [Contact](#contact)

## Aperçu

Ce projet, développé en C++, se concentre sur la modélisation du fonctionnement du métro en utilisant des concepts de multithreading. Il vise à reproduire le système de gestion des rames de métro et des stations.

Chaque rame est conçue pour fonctionner de manière relativement autonome, suivant un circuit fermé comprenant des stations où elle effectue des arrêts. Les fonctionnalités principales de chaque rame incluent :

- **Circulation sur un circuit fermé** : Chaque rame suit un itinéraire prédéfini, s'arrêtant à des stations spécifiques.
- **Gestion de la vitesse et de l'accélération** : Les rames ajustent leur vitesse et leur accélération en fonction des paramètres définis.
- **Maintien d'une distance de sécurité** : Les rames maintiennent une distance de sécurité entre elles lorsqu'elles circulent sur des lignes séparées. Chaque rame effectue un trajet aller-retour sur des voies distinctes. Aux terminus, elles effectuent un demi-tour en utilisant une voie de réserve spécifique pour changer de direction et se positionner au départ de la ligne, sur le quai opposé.

Le système intègre également des stations autonomes qui gèrent l'afflux de passagers entrant et sortant de chaque rame. L'interaction entre les rames et les stations crée un réseau dynamique visant à simuler le fonctionnement réel d'un système de métro.

Ce projet met en avant la gestion autonome des rames en interaction avec un réseau de stations, visant à reproduire les principes fondamentaux de fonctionnement du métro dans un environnement modélisé en C++.


Si votre projet est déjà sur un dépôt GitHub, voici comment vous pourriez ajouter la section d'installation avec la commande `git clone` pour récupérer votre projet depuis le dépôt :


## Chiffres Clés

1. **Nombre de lignes de code** :
2. **Nombre d'heures de codage** :

## Installation

Pour utiliser ce projet, vous devez avoir le fichier SFML.exe fourni sur JUNIA Learning de `Monsieur Pascal Mosbah`

1. **Téléchargement de SFML**
    - Télécharger le fichier SFML.exe depuis junia learning ! A refaire

2. **Récupération du projet depuis GitHub**
    - Clonez le dépôt GitHub "CIR2-VAL" en utilisant la commande suivante dans votre terminal :
    ```bash
    $ git clone https://github.com/username/CIR2-VAL.git
    ```
    Assurez-vous de remplacer `username` par votre nom d'utilisateur GitHub.

## Utilisation

### Prérequis
Assurez-vous d'avoir le fichier SFML.exe fourni par JUNIA Learning installé sur votre système.

### Étapes pour lancer le programme

1. **Construction du projet**
   - Exécutez les commandes nécessaires pour construire le projet en utilisant le système de build.

2. **Lancement du programme**
   - Après la construction réussie du projet, lancez le programme en exécutant le fichier exécutable généré.

3. **Interface utilisateur SFML**
   - Lorsque le programme est lancé, l'interface utilisateur SFML devrait se charger.
   - Des informations supplémentaires peuvent être affichées dans la console, fournissant des détails sur le fonctionnement du programme et du système de métro simulé.

4. **Observation et utilisation**
   - Observez le fonctionnement de l'interface SFML pour visualiser la simulation du système de métro.
   - Interagissez avec les fonctionnalités.


### Fonctionnalités de l'interface SFML

1. **Bouton de redémarrage** : Permet de réinitialiser le système à son état initial, relançant la simulation du réseau de métro.

2. **Molette de gestion de la vitesse du temps** : Permet de régler la vitesse de la simulation, accélérant ou ralentissant le défilement du temps dans la simulation du système de métro.

3. **Arrêt d'urgence des trains** : En appuyant sur un train spécifique, cette action simule un arrêt d'urgence pour la rame concernée, illustrant ainsi la réaction du système en cas d'urgence.

4. **Molette de gestion du nombre de trains sur les voies** : Cette fonctionnalité permet de régler le nombre de trains présents sur les différentes voies de manière dynamique, permettant ainsi d'observer l'impact sur le fonctionnement du réseau.


## Contact

  Adresse email de `Maxence` : maxence.gibaru@student.junia.com


  Adresse email de `Ugo` : ugo.warembourg@student.junia.com
