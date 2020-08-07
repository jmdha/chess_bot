const fs = require('fs');
const path = require('path');
const readline = require('readline');
const {
    execSync,
    execFile,
    execFileSync
} = require('child_process');

var exec = require('child_process').execFile;


cleanData();

let gameCount = 0;
let lineCount = 0;

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
                line.indexOf('Title') < 0 &&
                line.indexOf('Termination') < 0 &&
                line.indexOf('TimeControl') < 0 &&
                line.indexOf('ECO') < 0 &&
                line.indexOf('Opening') < 0 &&
                line.indexOf('White \"') < 0 &&
                line.indexOf('Black \"') < 0 &&
                line.indexOf('Diff \"') < 0 &&
                line.indexOf('Elo \"') < 0 &&
                line.indexOf('Result') < 0 &&
                line.length > 4) {
                line = line.replace("…", "...");
                
                for (let i = 0; i < line.length; i++) {
                    if (line[i] === ' ') {

                    }
                }

                lineCount++;
                if (lineCount % 100 == 0)
                    console.log(lineCount);
                incrementByPGN(line);
            }
        });
    }
    oldDir.closeSync();
    newDir.closeSync();
}

async function incrementByPGN(PGN) {
    const hash = getHash(PGN);
    gameCount++;

}

function getHash(PGN) {
    let optionals = new Array(JSON.stringify(PGN));
    return execFileSync(path.resolve(__dirname, '../chess_engine/chess_engine.exe'), optionals, {
        "timeout": 5000
    })
}