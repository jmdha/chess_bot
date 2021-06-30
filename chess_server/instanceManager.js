const path = require('path');
const Instance = require(path.resolve('Instance'));
const UI = require(path.resolve('UI'));
const EventEmitter = require('events');

class InstanceManager extends EventEmitter {
    constructor(api, ui) {
        super();
        this.api = api;
        this.ui = ui;
        this.instances = [];

        this.on('instanceStateUpdate', () => {
            this.ui.display(this.instances);
        });
        ui.display(this.instances);
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
                //console.log(`Starting Instance: ${event.game.id}`);
                const instance = new Instance(this.api, event.game.id, this);
                instance.start();
                this.instances.push(instance);
                this.ui.display(this.instances);
                break;

            case 'gameFinish':
                this.instances.pop(this.instances.filter(item => item.instanceID == event.game.id));
                this.ui.display(this.instances);
                break;
        }
    }

    updateInstance() {
        this.ui.display(this.instances);
    }
}

module.exports = InstanceManager;