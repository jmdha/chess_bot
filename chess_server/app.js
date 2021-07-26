const path = require('path');
const InstanceManager = require(path.resolve('InstanceManager'));
const Api = require(path.resolve('Api'));
const UI = require(path.resolve('UI'));
const result = require('dotenv').config({ path: path.resolve('config.env') });
// If the file doesn't exist ... or any other reason 
if (result.error)
    throw result.error;




function lichessStream(res) {
    let ui = new UI();
    let instanceManager = new InstanceManager(
        new Api(
            process.env.BEARER_ID,
            process.env.BOT_ID,
            process.env.AI_Level,
            process.env.CLOCK_LIMIT,
            process.env.CLOCK_INCREMENT),
        ui,
        process.env.AUTO_CHALLENGE_AI == true,
        process.env.ENGINE_PATH);
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
            Authorization: `Bearer ${process.env.BEARER_ID}`
        }
    }, lichessStream);
}

start();