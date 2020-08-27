const fs = require('fs');
const path = require('path');
const readline = require('readline');
const {
    execSync,
    execFile,
    execFileSync
} = require('child_process');

const exec = require('child_process').execFile;

const mysql = require('mysql');
const pool = mysql.createPool({
    connectionLimit: 100,
    host: "localhost",
    user: "root",
    password: "password",
    database: "chessData"
});

let gameCount = 0;
let lineCount = 0;
let incrementCount = 0;

//cleanData();
//incrementHashByMove(1, 'd4');



async function cleanData() {
    return new Promise(async (resolve) => {
        let oldDir = fs.opendirSync("./data/old");
        let newDir = fs.opendirSync("./data/new");
        let dirent;
        while ((dirent = oldDir.readSync()) !== null) {
            await passFile("./data/old/" + dirent.name)
        }
        oldDir.closeSync();
        newDir.closeSync();
        resolve();
    });
}

async function passFile(fileName) { 
    return new Promise(resolve => {
        let rd = readline.createInterface({
            input: fs.createReadStream(fileName)
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
    
                lineCount++;
                incrementByPGN(line);
                //console.log(incrementCount);
            }
        });
        rd.on('close', () => {
            resolve();
        })
    })
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

let hashMovePairBuffer = [];

async function incrementHashByMove(hash, move) {

    if (hashMovePairBuffer.length > 1) {
        var sql = `INSERT INTO move_count (hash, move, count) VALUES ? ON DUPLICATE KEY UPDATE count = count + 1;`;
        let values = hashMovePairBuffer;
        hashMovePairBuffer = [];

        await sqlAsync(sql, values);
        
    } else {
        incrementCount++;
        hashMovePairBuffer.push([hash, move, 1]);
    }


}

async function sqlAsync(sql, values) {
    return new Promise((resolve, reject) => {
        pool.query(sql, [values], (err, data) => {
            if(err) {
                throw (err);
                reject(err, data);
            }
            else {
                resolve(data);
            }
        });
    })
}

function getHash(PGN) {
    let optionals = new Array(JSON.stringify(PGN));
    return execFileSync(path.resolve(__dirname, '../chess_engine/chess_engine.exe'), optionals, {
        "timeout": 5000
    })
}

async function asyncMain() {
    await cleanData();
    pool.end();
}

asyncMain();

