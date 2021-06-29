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
        switch (event.type) {
            case 'gameFull':
                this.setInstanceColor(event.white.id == this.api.botID);
                this.handleMove(event.state.moves);
                break;
            case 'gameState':
                this.handleMove(event.moves);
                break;
        }
    }

    handleMove(moves) {
        if (!this.isInstanceColor(moves)) 
            return;
        
        this.generateMove(this, moves, this.playMove)
    }

    generateMove(instance, moves, callback) {
        exec.exec('./chess_engine.out ' + "\"" + moves + "\"", (err, stdout) => {
            callback(instance, err, stdout);
        });
    }

    playMove(instance, err, stdout) {
        if (err != null) {
            console.log("engine error ".red, err);
        }
        let segmentedData = stdout.split('\n');

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
}

module.exports = Instance;