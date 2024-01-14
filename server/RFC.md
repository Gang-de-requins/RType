# RType : RFC (CLient-Server Protocol)

Authors : Ethan Saux - Justin Thibault - Tony Tran - Hugo Martins Gandra - Alexandre Jankovic

## Introduction

This document details the R-TYPE Client-Server Protocol, a custom protocol tailored for the R-TYPE game project. It defines the structure of the messages exchanged between the client and the server, as well as the various message types. Additionally, it provides insights into the different server and client states, along with the distinct actions that can be executed by each party.

## Table of contents

- [Definitions](#message-structure)
- [Message structure](#message-structure)
- [Messages](#messages)
    - [PlayerJoined](#playerjoined)
    - [PlayerJoinedAccept](#playerjoinedaccept)
    - [NewPlayer](#newplayer)
    - [EntityList](#entitylist)
    - [Move](#move)
    - [NewMissile](#newmissile)
    - [StopX](#stopx)
    - [StopY](#stopy)
- [States](#states)

## Definitions

The following terms are used throughout this document:

- Client: The client is the graphical interface. It handles the user inputs and displays the game for the user.
- Server: The server is the hidden interface. It manages how the players interact with the game.
- Player: The player is an user using a client connected to the server.
- Game: A game is composed of a server and one or more players connected.

## Message structure

The messages are composed of 3 parts:

    +----------------+----------------+
    |  MessageType   |  Structure     |
    +----------------+----------------+

The type of the message is here to help the server what type of structure expecting.

- Message type: The message type identifies the type of the message. It can be one of the following values:

        PlayerJoinRequest = 1,
        PlayerJoinResponse = 2,
        PlayerJoined = 3,
        PlayerJoinedAccept = 4,
        NewPlayer = 5,
        EntityList = 6,
        Move = 7,
        GoRight = 8,
        GoLeft = 9,
        GoTop = 10,
        GoBottom = 11,
        StopRight = 12,
        StopLeft = 13,
        StopTop = 14,
        StopBottom = 15,
        Ping = 16,
        GetRooms = 17,
        CreateRoom = 18,
        NewMissile = 19,
        StopX = 19,
        StopY = 19,

The structure changes depending on the type of the message.
If the player sends a message to the server, with the MessageType = 7, the server will treat structured information and then send a message to all the players matching those informations.

## Messages

This section describes the main types of messages that can be exchanged between the client and the server. As the structures have different values, we use a serialization and deserialization method for every structure.
Each structure have their own serialization and deserialization method.

### PlayerJoined

The Player Joined message is sent by the server to all the clients
when a new player joins the game. It only contains the name of the new player. This message then triggers the messageType PlayerJoinedAccept.

### PlayerJoinedAccept

The Player Joined Accept message is sent by the server to the new player, with its name, its entity id, its position and its health.

### NewPlayer

The New Player message is sent by the server to all the other clients when a new player joins the game. It contains the name of the new player.

### EntityList

The Entity List message is sent by the server to all the clients,
32 times per second representing the tick value. It contains the list of all the entities in the game.

### Move

The Move message is sent by client to the server, It contains the direction of the entity with a structure composed of GoRight, GoLeft, GoTop, GoBottom.

### NewMissile

The New Missile message is sent by the client to the server, when the client creates use the space button. The server sends back the New Missile message to all the clients with the id and the position of the missile.

### StopX

The Stop X message is sent by the client to the server, when the client stops moving on the X axis. The server stops the entity on the X axis.

### StopY

The Stop Y message is sent by the client to the server, when the client stops moving on the Y axis. The server stops the entity on the Y axis.

## States

This section describes the different states of the server and the client,
and the different actions that can be performed by each of them.

The programs are composed of 2 states:

        - The game state
        - The finished state

- The game state is the state where the game is running, or when the server is waiting for players to join.

- The finished state is the state where the game is finished.

        A game can end in several ways:
            - All the players are dead
            - The level is finished
            - The host of the lobby disconnects