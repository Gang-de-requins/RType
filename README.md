# RType
> *This is an Epitech 3rd-year project.*

<h1 align="center">
  <img src="assets/rtype.jpg" alt="Depviz" title="Depviz" height="350px">
  <br>
</h1>

## Table of contents
- [Description](##Description)
  - [History of the game](###History-of-the-game)
  - [Goal of the project](###Goal-of-the-project)
  - [Librairies](###Librairies)
  - [Supported Platforms](###Supported-platforms )
- [Installation](##Installation)
  - [Clone the project](###Clone-the-project)
  - [Launch the script](###Launch-the-scipt)
    - [Linux](####Linux)
    - [Windows](####Windows)
- [Usage](##Usage)
  - [Server](###Server)
  - [Client](###Client)
- [How to play](##How-to-play)
  - [Settings](###Settings)
  - [Lobby](###Lobby)
  - [Move the player](###Move-the-player)
    - [Keyboard](####Keyboard)
    - [Controller](####Controller)
  - [Kill enemies](###Kill-enemies)
  - [Pause Game](###Pause-game)
  - [Lose condition](###Lose-condition)
- [About all the project](##About-all-the-project)
  - [Protocol documentation](###Protocol-documentation)
  - [GameEngine documentation](###Gameengine-documentation)
  - [Server documentation](###Server-documentation)
  - [Client documentation](###Client-documentation)
- [Contributors](##Contributors)


## 🚀 Description 🚀

### History of the game

R-Type is an emblematic series of video games of the shoot them up with horizontal scrolling, developed by Irem and begun in 1987 on terminal of arcade. It is probably inspired by the Konami Gradius series, whose first episode was released two years earlier.

### Goal of the project

This project aims to recreate the R-Type game with a multi-threaded server using Boost::asio for the network, udp protocol and graphical client. We using an engine of unity.
R-tpye is composed of two parts: the server and the client, both in C++.

### Librairies
- Graphical : Raylib.
- Network : asio


## 🔮 Installation 🔮

### Clone the project
    git@github.com:EpitechPromo2026/B-CPP-500-PAR-5-2-rtype-ethan.saux.git

### Launch the script

  #### Linux

  To get started, issue this command to root :
  ```bash
  ./scripts/install_dependencies.sh
  ```

  Then run this command, still as root :
  ```bash
  ./scripts/build_project.sh
  ```

  #### Windows


##Usage

After running the script you will have two executable: "./r-type_client" and "./r-type_server

### Server

  In the terminal launched:
  ```bash
  ./r-type_server.
  ```

### Client

  In an another terminal launched
  ```bash
  ./r-type_client
  ```
  > *You can change the [PORT] and the [ADRESSE] on the seetings of the game.*

## :brain: How to play :brain:

### Settings

    In the seetings you can change:
      - your name,
      - setup the volume of the game and the sound effect
      - fullscreen option

### Lobby
    Before the lobby you can add a room or join it.
    Then you are in the lobby you can choose your map and the level you want to play
    Once they have done so you can press start to begin the game.

### Move the player

#### Keyboard

  | Button    | Direction |
  | --------- | --------- |
  | Arrow Up  | Top       |
  | Arrow Down | Down     |
  | Arrow Left | Left     |
  | Arrow Right | Right   |

#### Controller

  | Button    | Direction |
  | --------- | --------- |
  |joystick(left) Up  | Top       |
  |joystick(left) Down | Down     |
  |joystick(left) Left | Left     |
  |joystick(left) Right | Right   |

### Attack

  | Button    | Action    |
  | --------- | --------- |
  | Space  Or button X(controller)   | Shoot     |

### Pause Game

In the pause game you can quit the game or start. The pause don't stop the game !

  | Button    | Action    |
  | --------- | --------- |
  | P         | Pause     |

### Lose condition

You have 3 hp if an enemy shoots at you you lose 1, so if you have no more hp you will die.
    If you let an enemy pass you lose the game too.
    If you play in multiplayer and you die the other player can continue the game

## :book: About all the project :book:

### Protocol documentation

[Check RFC](server/RFC.md)

### Game Engine documentation

[Check ECS documentation](ecs/README.md)

### Server documentation

[Check server documentation](server/README.md)

### Client documentation

[Check client documentation](client/README.md)

## Contributors

Game Engine:
- [Ethan Saux](https://github.com/Eowiin)
- [Justin Thibault](https://github.com/jThiba)

Server and Client:
- [Tony Tran](https://github.com/Troxifox)
- [Alexandre Jankovic](https://github.com/Acovic17)
- [Hugo Martins-Gandra](https://github.com/Masteruuuuu)

Dev-ops:
- [Hugo Martins-Gandra](https://github.com/Masteruuuuu)