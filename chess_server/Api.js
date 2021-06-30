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
        this.post(`/api/challenge/${id}/decline`, reason);
    }

    beginGameStream(id, callback) {
        this.stream(`/api/bot/game/stream/${id}`, callback);
    }

    sendDrawRequest(id) {
        this.post(`/api/board/game/${id}/draw/yes`);
    }

    sendMove(id, move) {
        this.post(`/api/bot/game/${id}/move/${move}`);
    }

    post(path, reason) {
        let options = {
            hostname: this.hostname,
            port: 443,
            path: path,
            method: 'POST',
            headers: {
                'Content-Type': 'application/x-www-form-urlencoded',
                'Authorization': 'Bearer ' + this.bearerID
            }
            //json: true,

        };
        let req = https.request(options, (res) => {

            res.on('data', (d) => {
                //console.log("Response from challenge ".brightBlue + d);
            });
        })

        req.on('error', (error) => {
            console.error(error);
        });

        if (reason != null) {
            req.write(qs.stringify({
                'reason': reason
            }));
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