const fs = require('fs');
const path = require('path');
const readline = require('readline');

var exec = require('child_process').execFile;


cleanData();

function cleanData() {
    let oldDir = fs.opendirSync("./data/old");
    let newDir = fs.opendirSync("./data/new");
    let dirent;
    while ((dirent = oldDir.readSync()) !== null) {
        let rd = readline.createInterface({
            input: fs.createReadStream("./data/old/" + dirent.name)
        });
        rd.on('line', function (line) {
            if (
                line.indexOf('Event') < 0 &&
                line.indexOf('Site') < 0 &&
                line.indexOf('UTC') < 0 &&
                line.indexOf('Termination') < 0 &&
                line.indexOf('TimeControl') < 0 &&
                line.indexOf('ECO') < 0 &&
                line.indexOf('Opening') < 0 &&
                line.indexOf('White \"') < 0 &&
                line.indexOf('Black \"') < 0 &&
                line.indexOf('Diff \"') < 0 &&
                line.indexOf('Elo \"') < 0 &&
                line.indexOf('Result') < 0) {

                incrementByPGN(line);
            }
        });
    }
    oldDir.closeSync();
    newDir.closeSync();
}

async function incrementByPGN(PGN) {
    const hash = await getHash(PGN);
    //console.log(hash);
}

function getHash(PGN) {
    return new Promise(function (resolve, reject) {
        let optionals = new Array(PGN);
        console.log("Running " + PGN);
        exec(path.resolve(__dirname, './chess_engine/chess_engine.exe'), optionals, function (error, output) {
            let hash = output.split("\n")[0].trim();
            console.log("Done " + output[0]);
            resolve(hash);
        });
    });
}