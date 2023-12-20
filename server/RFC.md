# RType : RFC (CLient-Server Protocol)


##Table of Contents

- [Introduction](#introduction)
- [Basic-structures](#basic-structures)
      - [Packet-header](#packet-header)
- [Protocol-packets-definition](#protocol-packets-definition)
      - [Response](#response)
      - [Connect](#connect)
      - [Parameters](#packet)
      - [Action](#action)
      - [Position](#position)
      - [Ping](#ping)
      - [Pong](#pong)
      - [Disconnect](##disconnect)

#Introduction

This document describe the network protocol used in the ECS.

This protocol version is 1.


#Basic-structures

This section will define some basic structures used by the network
    protocol.

All size are in octet.

uintX_t is a unsigned integer of X bit

##Packet-header

This structure is present before any packet described in this
    protocol.

Each packet MUST be assigned to an opcode, as defined in each packet
description sections.

The maximum size of the data MUST be "2^16-1"


| Name   | type     | Description  |
|----------------|----------------|----------------|
| opcode |   | Opcode       |
| size   |  | Size of data |


* opcode : It's identify what is the packet type

* size : It's the number of argument after header.

#Protocol packets definition

##Response

The "Response" packet is used in response of any packet, containing the
    result of the operations.

| Name   | Value |
|--------|-------|
| opcode | 0     |
| size   | 1     |




| Name  | type    | Description  |
|-------|---------|--------------|
| error |  | Error code   |



| Error code | Description                           |
|------------|---------------------------------------|
| 0          | No error                              |
| 1          | Ignored                               |
| 2          | Unknown error                         |
| 3          | Client already started                |
| 4          | Client already stopped                |
| 5          | Connect fail                          |
| 6          | Start fail                            |



##Connect

The "Connect" packet is used by a client to connect to a server.

If the server has enough information to identify the client, he accept
    the connection.


| Name   | Value |
|--------|-------|
| opcode | 1     |
| size   | 1     |


##Parameters

The "Parameters" packet is used to send the parameters of the client
    game.

Each client must send it to begin a game.


| Name   | Value |
|--------|-------|
| Opcode | 2     |
| size   | 2     |


| Name       | Data type  | Description                      |
|------------|------------|----------------------------------|
| difficulty |     | the difficulty of the game       |
| nbPlayer   |     | the number of player in game     |


##Action

The "Action" packet is used to send the action of the client

Each client must send each time an action is done.

| Name   | Value |
|--------|-------|
| Opcode | 3     |
| size   | 2     |



|  Name  | Data type  | Description            |
|--------|------------|------------------------|
| action |     | the action of the game |
| nbGame |     | the number of the game |


##Position

The "Position" packet is used to send the position of each sprite which has moved.

Each position is composed of the name of the sprite, its position and its size.


| Name   | Value |
|--------|-------|
| Opcode | 4     |
| size   | 12    |



| Name   | Data type  | Description                  |
|--------|------------|------------------------------|
| pos_x  |    | the x position of the sprite |
| pos_y  |    | the y position of the sprite |
| size_x |    | the x size of the sprite     |
| size_y |    | the y size of the sprite     |
| sprite | string     | the sprite                   |



##Ping

When a "Ping" packet is sent, a "Pong" packet MUST be sent back to
the sender.

This packet is used to check if the other end of the connection is able to process packets or not.


| Name   | Value |
|--------|--------
| Opcode | 5     |
| size   | 0     |



##Pong


| Name   | Value |
|--------|-------|
| Opcode | 6     |
| size   | 0     |
| id     |     |



##Disconnect

The "Disconnect" packet is used by a client to disconnect to a server.

This packet must be send if a client want to disconnect from server.


| Name   | Value |
|--------|-------|
| opcode | 7     |
| size   | 0     |


