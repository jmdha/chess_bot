const exec = require('child_process');
const colors = require('colors');

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
        console.log(event);
        switch (event.type) {
            // on initial state
            case 'gameFull':
                this.setInstanceColor(event.white.id == this.api.botID);
                this.handleMove(event.state.moves);
                break;
            case 'gameState':
                this.handleMove(event.state.moves);
                break;
        }
    }

    handleMove(moves) {
        let a = this.isInstanceColor(moves);
        if (!a)
            return;
        console.log("moves: ".grey, moves);
        console.log("Generating move".grey);
        let output = this.generateMove(this, moves, this.playMove)
    }

    generateMove(instance, moves, callback) {
        exec.exec('./chess_engine.out ' + "\"" + moves + "\"", (err, stdout) => {
            callback(instance, err, stdout);
        });
    }

    playMove(instance, err, stdout) {
        console.log("Plating move")
        if (err != null) {
            console.log("engine error ".red, err);
        }
        let segmentedData = stdout.split('\n');

        console.log("----");
        console.log("Engine Output: ".grey);
        console.log("Move: ", segmentedData[0].green);
        for (let i = 1; i < segmentedData.length; i++)
            console.log(segmentedData[i]);
        console.log("----");


        if (stdout.includes('draw'))
            instance.api.sendDrawRequest(instance.instanceID);
        else
            instance.api.sendMove(instance.instanceID, segmentedData[0]);
    }

    setInstanceColor(isWhite) {
        if (isWhite)
            this.instanceColor = 'white';
        else
            this.instanceColor = 'black';
    }

    isInstanceColor(moves) {
        return (this.instanceColor == ((1 - (moves.length == 0) - moves.split(' ').length % 2) ? "white" : "black"));
    }

    getMove(moves) {

    }
}

module.exports = Instance;