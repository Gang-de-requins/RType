# RType : RFC (CLient-Server Protocol)

- [Description](#Description)
- [Message Structure](#Message-Structure)

#Description

R-TYPE is a 2D shoot-em-up video game where players pilot a spaceship, participating in battles against various enemies and fearsome bosses. Players have the ability to upgrade their ship by collecting power-ups throughout the game. The multiplayer feature allows for up to four players in the same game.

The game architecture consists of two essential components: the client and the server. The server acts as the brain, managing the game mechanics and interactions between players. On the other hand, the client functions as the graphical interface, displaying the game environment and processing user inputs. The client and server always communicate with each other to ensure the good functionning of the game.

Concerning the communication, the R-TYPE protocol is designed to work seamlessly on TCP and UDP. TCP facilitates the connection between the client and the server, while UDP is used for in-game communication.

The main objective of this protocol is to provide a complete specification of the R-TYPE Client-Server Protocol.

Definition of the terms used in this document:

- Client: The client is the graphical part of the game. It displays the game and handles the user inputs.

- Server: The server is the main part of the game. It manages the game and the players.

- Player: A player is a client connected to the server.

- Game: A game is a game session. It is composed of a server and one or more players.

- Lobby: A lobby is a waiting room. It is composed of a server and one or more players.