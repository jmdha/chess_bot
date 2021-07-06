const exec = require('child_process');
const EventEmitter = require('events');

class Instance {
    constructor(api, instanceID, manager) {
        this.api = api;
        this.instanceID = instanceID;
        this.manager = manager;
        this.updateState('Init');
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
        if (!this.isInstanceColor(moves)) {
            this.updateState('Waiting for Opponent');
            return;
        }
        
        this.generateMove(this, moves, this.playMove)
    }

    generateMove(instance, moves, callback) {
        this.updateState('Generating Move');
        exec.exec('./chess_engine.out ' + "\"" + moves + "\"", (err, stdout) => {
            callback(instance, err, stdout);
        });
    }

    playMove(instance, err, stdout) {
        instance.updateState('Sending Move');
        if (err != null) {
            console.log("engine error ", err);
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

    updateState(state) {
        this.state = state;
        this.manager.emit('instanceStateUpdate');
    }
}

module.exports = Instance;