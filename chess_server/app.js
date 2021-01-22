const https = require('https');
const port = 3000;
const exec = require('child_process');
const fs = require('fs');
const qs = require('querystring');

let bearerId = fs.readFileSync('id.txt', 'utf8');

const botId = "sun_bird";

//const connection = new websocket('https://lichess.org/api/stream/event');

let currentGame = null;

https.get('https://lichess.org/api/stream/event', {
    headers: {
        Authorization: 'Bearer ' + bearerId
    }
}, function (res) {
    res.on('data', function (chunk) {
        let data;
        if (String(chunk).length > 5) {
            console.log("Chunk ", String(chunk))
            data = JSON.parse(String((chunk)));
            
            switch (data.type) {
                case 'challenge':
                    console.log("received challenge by " + data.challenge.challenger.id);
                    if (currentGame == null && data.challenge.challenger.id == 'laggus' && !data.challenge.rated)
                        acceptChallenge(data.challenge.id, data.challenge.url);
                    break;
                case 'gameStart':
                    if (currentGame != null)
                        break;
                    currentGame = {};
                    currentGame.id = data.game.id;
                    currentGame.turn = 'white';
                    console.log("Starting game " + currentGame.id);


                    beginGameStream(currentGame.id);
                    break;
                case 'gameFinish':
                    currentGame = null;
                    createAIChallange();
                    break;
            }
        }
    });
    res.on('end', function (msg) {
        // all data has been downloaded
    });
});

//createAIChallange();
//createChallenge('LeelaNovice');

function createUserChallenge(user) {
    let options = {
        hostname: 'lichess.org',
        port: 443,
        path: '/api/challenge/' + user,
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Authorization': 'Bearer ' + bearerId
        }
        //json: true,

    };
    let req = https.request(options, (res) => {

        res.on('data', (d) => {
            process.stdout.write(d);
        });
    })

    req.on('error', (error) => {
        console.error(error);
    });

    var postData = qs.stringify({
        'clock.limit': '300',
        'clock.increment': '5',
        'rated': 'false'
    });

    req.write(postData);
    req.end();
}

function createAIChallange() {
    let options = {
        hostname: 'lichess.org',
        port: 443,
        path: '/api/challenge/ai',
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Authorization': 'Bearer ' + bearerId
        }
        //json: true,

    };
    let req = https.request(options, (res) => {

        res.on('data', (d) => {
            process.stdout.write(d);
        });
    })

    req.on('error', (error) => {
        console.error(error);
    });

    var postData = qs.stringify({
        'clock.limit': '300',
        'clock.increment': '5',
        'level': '3'
    });

    req.write(postData);
    req.end();
}

function acceptChallenge(id) {
    let options = {
        hostname: 'lichess.org',
        port: 443,
        path: 'https://lichess.org/api/challenge/' + id + '/accept',
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Authorization': 'Bearer ' + bearerId
        }
    };
    let req = https.request(options, (res) => {})

    req.on('error', (error) => {
        console.error(error);
    });
    req.end();

}

function beginGameStream(id) {
    https.get('https://lichess.org/api/bot/game/stream/' + id, {
        headers: {
            Authorization: 'Bearer ' + bearerId
        }
    }, function (res) {
        res.on('data', function (chunk) {
            let data;
            if (chunk != null)
                console.log(String(chunk))
            if (String(chunk).length > 5) {
                console.log("chunk ", String(chunk));
                data = JSON.parse(String((chunk)));
                console.log("parsed: ", data);
                switch (data.type) {
                    case 'gameFull':
                        currentGame.state = data.state;
                        currentGame.white = data.white;
                        currentGame.black = data.black;
                    
                        if (currentGame.white.id == botId) {
                            currentGame.botSide = 'white';
                        } else
                            currentGame.botSide = 'black';

                        if (currentGame.state.moves != null && currentGame.state.moves.length > 0) {
                            currentGame.turn = (1 - (String(data.state.moves).split(' ').length % 2)) ? 'white' : 'black';

                            console.log("going into handle new move")
                            handleNewMove(data.state.moves);
                        }
                            

                        break;
                        
                    case 'gameState': {
                        console.log("gameState", data.status);
                        if (data.status == 'started') {
                            switchTurn();
                            handleNewMove(data.moves);
                        } else
                            currentGame = null;
                        break;
                    }
                }
            }
        });
        res.on('end', function (msg) {
            console.log("shit's done yo!")
            // all data has been downloaded
        });
    });
}

function handleNewMove(moves) {
    console.log("turn ", currentGame.turn);
    if (currentGame.turn == currentGame.botSide) {
        exec.exec('./chess_engine.out ' + "\"" + moves + "\"", function (err, data) {
            if (err != null)
                console.log("engine error ", err);

            console.log(data);
            let move = data.split('\n')[0];
            sendMove(move);
        });
    }
}

function sendMove(move) {

    let options = {
        hostname: 'lichess.org',
        port: 443,
        path: 'https://lichess.org/api/bot/game/' + currentGame.id + '/move/' + move,
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
            'Authorization': 'Bearer ' + bearerId
        }
    };
    let req = https.request(options, (res) => {
        console.log("move sent with statuscode ", res.statusCode);
        if (res.statusCode != 200) {
            console.log("sent to path ", options.path);
            if (res.statusCode == 429)
                setTimeout(sendMove, 61 * 1000, move);
            else
                setTimeout(sendMove, 5000, move);
        }
    })

    req.on('error', (error) => {
        console.log("lada");
        console.error("error3 ", error);
    });
    req.end();
}

function switchTurn() {
    if (currentGame.turn == 'white')
        currentGame.turn = 'black';
    else
        currentGame.turn = 'white';
}