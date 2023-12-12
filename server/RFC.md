# RType : RFC (CLient-Server Protocol)

- [Description](#Description)
- [Message Structure](#Message-Structure)

#Description

R-TYPE est un jeu vidéo de type shoot-em-up en 2D où les joueurs pilotent un vaisseau spatial, participant à des batailles contre divers ennemis et redoutables boss. Les joueurs ont la possibilité d'améliorer leur vaisseau en collectant des améliorations tout au long du jeu. La fonctionnalité multijoueur permet une collaboration jusqu'à quatre joueurs.

L'architecture du jeu se compose de deux composants essentiels : le client et le serveur. Le serveur agit comme le centre névralgique, gérant les mécanismes du jeu et les interactions entre les joueurs. En revanche, le client fonctionne comme l'interface graphique, affichant l'environnement de jeu et traitant les entrées des utilisateurs.

Pour la communication, le protocole R-TYPE est conçu pour fonctionner de manière transparente sur TCP et UDP. TCP facilite la connexion entre le client et le serveur, tandis que UDP est utilisé pour la communication in-game.

L'objectif principal de ce protocole est de fournir une spécification complète du Protocole Client-Serveur R-TYPE.

The terms are used in this document:

- Client: The client is the graphical part of the game. It displays the
        game and handles the user inputs.
- Server: The server is the main part of the game. It manages the game
    and the players.
- Player: A player is a client connected to the server.
- Game: A game is a game session. It is composed of a server and one or
    more players.
- Lobby: A lobby is a waiting room. It is composed of a server and one or
    more players.

