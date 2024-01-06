# Modélisation simplifiée d’un système de transport de type « VAL

Projet CIR2 VAL.

## Table des matières

1. [Aperçu](#aperçu)
2. [Installation](#installation)
3. [Utilisation](#utilisation)
4. [Contact](#contact)

## Aperçu

Ce projet, développé en C++, se concentre sur la modélisation du fonctionnement du métro en utilisant des concepts de multithreading. Il vise à reproduire le système de gestion des rames de métro et des stations.

Chaque rame est conçue pour fonctionner de manière relativement autonome, suivant un circuit fermé comprenant des stations où elle effectue des arrêts. Les fonctionnalités principales de chaque rame incluent :

- **Circulation sur un circuit fermé** : Chaque rame suit un itinéraire prédéfini, s'arrêtant à des stations spécifiques.
- **Gestion de la vitesse et de l'accélération** : Les rames ajustent leur vitesse et leur accélération en fonction des paramètres définis.
- **Maintien d'une distance de sécurité** : Les rames maintiennent une distance de sécurité entre elles lorsqu'elles circulent sur des lignes séparées. Chaque rame effectue un trajet aller-retour sur des voies distinctes. Aux terminus, elles effectuent un demi-tour en utilisant une voie de réserve spécifique pour changer de direction et se positionner au départ de la ligne, sur le quai opposé.

Le système intègre également des stations autonomes qui gèrent l'afflux de passagers entrant et sortant de chaque rame. L'interaction entre les rames et les stations crée un réseau dynamique visant à simuler le fonctionnement réel d'un système de métro.

Ce projet met en avant la gestion autonome des rames en interaction avec un réseau de stations, visant à reproduire les principes fondamentaux de fonctionnement du métro dans un environnement modélisé en C++.


Si votre projet est déjà sur un dépôt GitHub, voici comment vous pourriez ajouter la section d'installation avec la commande `git clone` pour récupérer votre projet depuis le dépôt :

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

bouge

## Contact

  Adresse email de `Maxence` : maxence.gibaru@student.junia.com


  Adresse email de `Ugo` : ugo.warembourg@student.junia.com
