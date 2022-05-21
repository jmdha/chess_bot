# chess_bot
Requires [Node.js](https://nodejs.org)

Place a chess engine in the containing server project with name chess_engine.out

Create and fill out the file config.env in root of the server (Replace ... with values):
```properties
# see https://lichess.org/api#operation/apiStreamEvent
BEARER_ID=...
# name of the bot on lichess.org
BOT_ID=...

# relative engine path e.g. ./chess_engine.out
ENGINE_PATH=...

# which time controls to accept e.g. rapid,blitz
VALID_TIME_CONTROLS=...

# whether it should challenge the AI when having no ongoing games, 1 = true, 0 = false
AUTO_CHALLENGE_AI=...
# the level of AI to challenge in above option, 1-8 - higher is more difficult
AI_LEVEL=...
# the initial amount of time (sec) on the clock e.g. 300
CLOCK_LIMIT=...
# how much time (sec) is added after each move e.g. 5
CLOCK_INCREMENT=...
```
Bearer ID is generated on lichess following their [API](https://lichess.org/api#operation/botAccountUpgrade) for a bot
Bot ID is the name of the user on [lichess](https://lichess.org)

#### Running
Navigate to file containing server project, then run command
``` 
node app.js
```
