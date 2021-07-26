# chess_bot
This project includes a chess engine and a server that can communicate with lichess.org. Therefore, it has all the code needed to run a bot on the page, or any other given API implementation.

## Table of Contents
* [Notes](#notes)
* [Goals](#goals)
* [Setup](#setup)

## Notes
This repository is used as a personal git repo, as such most of what is written is informal and for myself. 

That being said, anyone is welcome to contribute.

## Goals
This project is built upon a project from high school, where an exam project was to build a robot playing chess. Admittedly, that project didn't work. This is an attempt to succeed in that.
As such the goals are as following:
* Implement an engine which can output a meaningful move as a response to given input(Board state / move sequence) ✓
* Implement a server which allows playing against the engine on a website ✓ (https://lichess.org/@/sun_bird)
* Build a robot which can play the moves on an actual board ✗
* Allow playing against robot ✗
  * Offline
  * Online | Move is played on board => Robot registers the move => Engine translates it to a the correct move => Server sends it to website

## Setup
Only works on Linux right now

### Data

Requires [MYSQL](https://dev.mysql.com/downloads/connector/cpp/) C++ Connector

Create and fill out the file config.txt in root of the program(Replace ... with values):

```properties
# Any line with a # as first character is ignored
# Any empty line is ignored

# DB connection IP e.g. 127.0.0.1
IP=...
# DB connection port e.g. 3306
PORT=...

# Name of DB schema e.g. chess_data
SCHEMA_NAME=...
# Name of DB table e.g. move_frequency
TABLE_NAME=...

# Username of account e.g. admin
USER_NAME=...
# Password of account e.g. password
USER_PASSWORD=...
```

### Server
Requires [Node.js](https://nodejs.org)

Place the chess engine in the containing server project with name chess_engine.out

Create and fill out the file config.env in root of the server (Replace ... with values):
```properties
# see https://lichess.org/api#operation/apiStreamEvent
BEARER_ID=...
# name of the bot on lichess.org
BOT_ID=...

# whether it should challenge the AI when having no ongoing games, 1 = true, 0 = false
AUTO_CHALLENGE_AI=0
```
Bearer ID is generated on lichess following their [API](https://lichess.org/api#operation/botAccountUpgrade) for a bot
Bot ID is the name of the user on [lichess](https://lichess.org)

#### Running
Navigate to file containing server project, then run command
``` 
node app.js
```
