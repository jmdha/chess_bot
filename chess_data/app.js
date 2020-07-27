const fs = require('fs');
const path = require('path');
const readline = require('readline');



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
                line.indexOf('Result') < 0)  {
                console.log(line);
            }
        });
    }
    oldDir.closeSync();
    newDir.closeSync();
}