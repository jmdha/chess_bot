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

function incrementByPGN(PGN) {
    let hashMovePairArray = getHash(PGN).toString().split('\r\n').map((hashMovePair) => hashMovePair.split(' ')).filter((element) => element.length == 2);

    // Should be noted that the following code does exactly the same as the code above
    /*
    let hashMovePairString = getHash(PGN).toString();
    let hashMovePairArray = [];

    let index = 0;
    let occuranceStartIndex;

    let currentLabel = 2;
    let runningHashMovePair = "";


    while (true) {
        let goto = null;
        switch (currentLabel) {
            case 1:
                if (occuranceStartIndex >= hashMovePairArray.length)
                    break;
                else if (hashMovePairArray[occuranceStartIndex][index] == ' ') {
                    let hash = runningHashMovePair;
                    runningHashMovePair = "";
                    goto = 1;
                    index++;
                    while (goto != -1) {
                        switch (goto) {
                            case 0:
                                hashMovePairArray[occuranceStartIndex] = [];
                                hashMovePairArray[occuranceStartIndex].push(hash);
                                hashMovePairArray[occuranceStartIndex].push(runningHashMovePair);
                                goto = -1;
                                break;
                            case 1:
                                if (index >= hashMovePairArray[occuranceStartIndex].length)
                                    goto = 0;
                                else {
                                    runningHashMovePair += hashMovePairArray[occuranceStartIndex][index];
                                    index++;
                                    goto = 1;
                                }
                        }
                    }
                    occuranceStartIndex++;
                    goto = 1;
                    index = 0;
                    runningHashMovePair = "";
                    break;
                } else {
                    runningHashMovePair += hashMovePairArray[occuranceStartIndex][index];
                    index++;
                    goto = 1;
                    break;
                }
                case 2:
                    occuranceStartIndex = index;
                case 3:
                    if (index >= hashMovePairString.length) {
                        index = 0;
                        occuranceStartIndex = 0;
                        runningHashMovePair = "";
                        goto = 1;
                    } else if (hashMovePairString[index] == '\r') {
                        hashMovePairArray.push(runningHashMovePair);
                        runningHashMovePair = "";
                        index += 4;
                        goto = 2;
                    } else {
                        runningHashMovePair += hashMovePairString[index];
                        index++;
                        goto = 3;
                    }
        }
        if (goto == null) break;
        currentLabel = goto;
    }

*/
    
        for (let i = 0; i < hashMovePairArray.length; i++) {
            incrementHashByMove(hashMovePairArray[i][0], hashMovePairArray[i][1]);
        }
    
    gameCount++;

}

function incrementHashByMove(hash, move) {

}



function getHash(PGN) {
    let optionals = new Array(JSON.stringify(PGN));
    return execFileSync(path.resolve(__dirname, '../chess_engine/chess_engine.exe'), optionals, {
        "timeout": 5000
    })
}