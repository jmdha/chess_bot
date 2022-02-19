const path = require('path');
const Instance = require(path.resolve('Instance'));
const UI = require(path.resolve('UI'));
const EventEmitter = require('events');

class InstanceManager extends EventEmitter {
    constructor(api, ui, autoChallengeAI, validTimeControls, enginePath) {
        super();
        this.api = api;
        this.ui = ui;
        this.autoChallengeAI = autoChallengeAI;
        this.validTimeControls = validTimeControls;
        this.enginePath = enginePath;
        this.instances = [];

        this.on('instanceStateUpdate', () => {
            this.ui.display(this.instances);
        });
        if (autoChallengeAI) {
            if (this.instances.length == 0)
                api.challengeAI();
        } else
            ui.display(this.instances);
    }

    handleEvent(event) {
        switch (event.type) {
            case 'challenge':
                this.validateChallenge(event.challenge)
                break;

            case 'gameStart':
                //console.log(`Starting Instance: ${event.game.id}`);
                const instance = new Instance(this.api, event.game.id, this, this.enginePath);
                instance.start();
                this.instances.push(instance);
                this.ui.display(this.instances);
                break;

            case 'gameFinish':
                this.instances.pop(this.instances.filter(item => item.instanceID == event.game.id));
                this.ui.display(this.instances);
                if (this.autoChallengeAI)
                    if (this.instances.length == 0)
                        this.api.challengeAI();
                break;
        }
    }

    // check that it meets the requirements
    validateChallenge(challenge) {
        if (challenge.variant.key != 'standard') {
            console.log(`Declining Challenge: ${challenge.id}`);
            this.api.declineChallenge(challenge.id, 'standard');
            return;
        }
        if (this.validTimeControls.indexOf(challenge.speed) !== -1) {
            console.log(`Accepting Challenge: ${challenge.id}`);
            this.api.acceptChallenge(challenge.id);
            return;
        } else {
            console.log(`Declining Challenge: ${challenge.id}`);
            this.api.declineChallenge(challenge.id, 'timeControl');
            return;
        }
    }

    updateInstance() {
        this.ui.display(this.instances);
    }
}

module.exports = InstanceManager;