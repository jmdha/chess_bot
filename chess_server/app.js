const path = require('path');
const InstanceManager = require(path.resolve('InstanceManager'));
const Api = require(path.resolve('Api'));
const UI = require(path.resolve('UI'));

// used for reading id
const fs = require('fs');

let bearerID;
let botID;
readID();
function readID() {
    let ids = fs.readFileSync('id.txt', 'utf8').split('\n');
    bearerID = ids[0].split(' ')[1].trim();
    botID = ids[1].split(' ')[1].trim();
}

function lichessStream(res) {
    let ui = new UI();
    let instanceManager = new InstanceManager(new Api(bearerID, botID), ui);
    ui.display(instanceManager.instances);
    res.on('data', function (chunk) {
        let data;
        try {
            data = JSON.parse(String(chunk))
        } catch (error) { return };

        
        instanceManager.handleEvent(data);
    });
    res.on('end', function (msg) {
        // all data has been downloaded
    });
}

function start() {
    const https = require('https');
    https.get('https://lichess.org/api/stream/event', {
        headers: {
            Authorization: `Bearer ${bearerID}`
        }
    }, lichessStream);
}

start();