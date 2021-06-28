const exec = require('child_process');

class Instance {
    constructor(api, instanceID) {
        this.api = api;
        this.instanceID = instanceID;
    }

    start() {
        this.api.beginGameStream(this.instanceID, (res) => this.gameStream(res));
    }

    gameStream(res) {
        let instance = this;
        res.on('data', function (chunk) {
            let data;
            try {
                data = JSON.parse(String(chunk))
            } catch (error) { return };
            instance.handleEvent(data);
        });
        res.on('end', function (msg) {

        });
    }

    handleEvent(event) {
        switch (event.type) {
            // on initial state
            case 'gameFull':
                this.setInstanceColor(event.white.id == this.api.botID);
                this.playMove(event);
                break;
            case 'gameState':
                this.playMove(event);
                break;
        }
    }

    playMove(data) {
        if (!this.isInstanceColor(data.state.moves))
            return;
        let move = this.getMove(data.state.moves);
    }

    setInstanceColor(isWhite) {
        if (isWhite)
            this.instanceColor = 'white';
        else
            this.instanceColor = 'black';
    }

    isInstanceColor(moves) {
        return (this.instanceColor == (1 - (moves.length == 0) - moves.split(' ').length % 2) ? "white" : "black");
    }

    getMove(moves) {
        return exec.exec('./chess_engine.out' + "\"" + moves + "\"", function (err, data) {
            if (err != null) {
                console.log("engine error ".red, err);
                //resignGame();
                //createAIChallange();
            }
            let segmentedData = data.split('\n');

            console.log("----");
            console.log("Engine Output: ".grey);
            console.log("Move: ", segmentedData[0].green);
            for (let i = 1; i < segmentedData.length; i++)
                console.log(segmentedData[i]);
            console.log("----");


            //if (data.includes('draw'))
            //  return sendDrawRequest;
            //else
            return segmentedData[0];
        });
    }
}

module.exports = Instance;