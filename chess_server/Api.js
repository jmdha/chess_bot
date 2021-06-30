const https = require('https');
const qs = require('querystring');

class Api {
    
    constructor(bearerID, botID) {
        this.bearerID = bearerID;
        this.botID = botID;
        this.hostname = "lichess.org";
    }

    acceptChallenge(id) {
        this.post(`/api/challenge/${id}/accept`);
    }

    declineChallenge(id, reason) {
        this.post(`/api/challenge/${id}/decline`, {'reason': reason});
    }

    beginGameStream(id, callback) {
        this.stream(`/api/bot/game/stream/${id}`, callback);
    }

    challengeAI() {
        this.post(`/api/challenge/ai`, {
            'clock.limit': '300',
            'clock.increment': '5',
            'level': '5'
        });
    }

    sendDrawRequest(id) {
        this.post(`/api/board/game/${id}/draw/yes`);
    }

    sendMove(id, move) {
        this.post(`/api/bot/game/${id}/move/${move}`);
    }

    post(path, body) {
        let options = {
            hostname: this.hostname,
            port: 443,
            path: path,
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'Authorization': 'Bearer ' + this.bearerID
            }

        };
        let req = https.request(options, (res) => {

            res.on('data', (d) => {
                //console.log("Response from challenge ".brightBlue + d);
            });
        })

        req.on('error', (error) => {
            console.error(error);
        });

        if (body != null) {
            req.write(qs.stringify(body));
        }

        req.end();
    }

    stream(path, callback) {
        https.get("https://" + this.hostname + path, {
            headers: {
                Authorization: 'Bearer ' + this.bearerID
            }
        }, callback);
    }
}

module.exports = Api;