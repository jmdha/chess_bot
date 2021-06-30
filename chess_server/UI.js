const colors = require('colors');

class UI {
    constructor() {
    }

    display(instances) {
        console.clear();
        this.outputStateToConsole(instances);
    }

    outputStateToConsole(instances) {
        console.log(`${instances.length} active games`);
        console.log(`Games:`);
        instances.forEach(this.outputInstanceInformation);
    }

    outputInstanceInformation(instance, index) {
        console.log(`-`);
        console.log(`Game ${index}`);
        console.log(`ID :${instance.instanceID}`);
        console.log(`State :${instance.state}`);
    }

}

module.exports = UI;