const path = require('path');
const Instance = require(path.resolve('Instance'));

class InstanceManager {
    constructor(api) {
        this.api = api;
    }

    handleEvent(event) {
        switch (event.type) {
            case 'challenge':
                if (event.challenge.variant.key != 'standard') {
                    console.log(`Declining Challenge: ${event.challenge.id}`);
                    this.api.declineChallenge(event.challenge.id, 'standard');
                    break;
                }


                if (event.challenge.speed == 'rapid' || event.challenge.speed == 'blitz') {
                    console.log(`Accepting Challenge: ${event.challenge.id}`);
                    this.api.acceptChallenge(event.challenge.id);
                } else {
                    console.log(`Declining Challenge: ${event.challenge.id}`);
                    this.api.declineChallenge(event.challenge.id, 'timeControl');
                }

                break;
            case 'gameStart':
                console.log(`Starting Instance: ${event.game.id}`);
                const instance = new Instance(this.api, event.game.id);
                instance.start();
                break;
        }
    }
}

module.exports = InstanceManager;