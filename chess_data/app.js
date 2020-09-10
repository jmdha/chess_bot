const fs = require('fs');
const path = require('path');
const readline = require('readline');
const {
    execSync,
    execFile,
    execFileSync
} = require('child_process');

const exec = require('child_process').execFile;

const sqlite3 = require('sqlite3').verbose();
let db = new sqlite3.Database('./data/new/data.db', (err) => {
    if (err) {
        return console.error(err.message);
    }
    console.log('Connected to the data.db SQlite database.');
});
db.run(`CREATE TABLE IF NOT EXISTS move_count (
    hash UNSIGNED INTEGER,
    move TEXT,
    count UNSIGNED INTEGER,
    PRIMARY KEY (hash, move)
)`);

let gameCount = 0;
let incrementCount = 0;

let startDate = new Date().getTime();

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

let PGNBuffer = [];
async function passFile(fileName) {
    return new Promise(resolve => {
        let rd = readline.createInterface({
            input: fs.createReadStream(fileName)
        });
        rd.on('line', function (PGN) {
            if (
                PGN.indexOf('Event') < 0 &&
                PGN.indexOf('Site') < 0 &&
                PGN.indexOf('UTC') < 0 &&
                PGN.indexOf('Title') < 0 &&
                PGN.indexOf('Termination') < 0 &&
                PGN.indexOf('TimeControl') < 0 &&
                PGN.indexOf('ECO') < 0 &&
                PGN.indexOf('Opening') < 0 &&
                PGN.indexOf('White \"') < 0 &&
                PGN.indexOf('Black \"') < 0 &&
                PGN.indexOf('Diff \"') < 0 &&
                PGN.indexOf('Elo \"') < 0 &&
                PGN.indexOf('Result') < 0 &&
                PGN.length > 4) {
                PGN = PGN.replace("…", "...");
                PGNBuffer.push(JSON.stringify(PGN));
                if (PGN.length >= 1) {
                    incrementByPGN(PGNBuffer);
                    PGNBuffer = [];
                }
                if (gameCount % 100 == 0)
                    printProgress();
                //console.log(incrementCount);
            }
        });
        // if any excess
        if (PGNBuffer.length > 0)
            incrementByPGN(PGNBuffer);
        rd.on('close', () => {
            resolve();
        })
    })
}

function incrementByPGN(PGNBuffer) {
    let hashMovePairArray = getHash(PGNBuffer).toString().split('\r\n').map((hashMovePair) => hashMovePair.split(' ')).filter((element) => element.length == 2);

    for (let i = 0; i < hashMovePairArray.length; i++) {
        incrementHashByMove(hashMovePairArray[i][0], hashMovePairArray[i][1]);
    }

    gameCount+= PGNBuffer.length;
}

let hashMovePairBuffer = [];

async function incrementHashByMove(hash, move) {

    if (hashMovePairBuffer.length >= 1) {
        //var sql = `INSERT INTO move_count(hash, move, count) VALUES (?, ?, ?) ON CONFLICT(hash, move) DO UPDATE SET count = count + 1`;

        let values = hashMovePairBuffer;
        let sql = `INSERT INTO move_count VALUES (?, ?, ?) ON CONFLICT(hash, move) DO UPDATE SET count = count + 1`;
        hashMovePairBuffer = [];

        insertValue(sql, values);


    } else {
        incrementCount++;
        hashMovePairBuffer.push([hash, move, 1]);
    }


}

async function insertValue(sql, values) {
    return new Promise((resolve, reject) => {
        db.run(sql, ...values, (err) => {
            if (err)
                reject(err);
            else
                resolve();
        })
    })
}

function getHash(PGNBuffer) {
    return execFileSync(path.resolve(__dirname, '../chess_engine/chess_engine.exe'), PGNBuffer, {
        "timeout": 5000
    })
}

async function printProgress() {
    let maxGameCount = 697600;

    let result = (await getSumOfCount())[0]['SUM(count)'];
    console.clear();
    let timePassed = ((new Date()).getTime() - startDate) / 1000;
    console.log("Time passed:", timePassed, "s");
    console.log("Entry success rate:", (result / incrementCount * 100).toFixed(3) + '%', result + "/" + incrementCount);
    console.log("Entry rate:", (result / timePassed).toFixed(3), "entries/s");
    console.log("Progress:", (gameCount / maxGameCount * 100).toFixed(3) + '%', gameCount + "/" + maxGameCount);


}

async function getSumOfCount() {
    return new Promise((resolve, reject) => {
        db.all('SELECT SUM(count) from move_count', (err, result) => {
            if (err) {
                reject(err);
            } else {
                resolve(result);
            }
        });
    });
}

async function asyncMain() {
    await cleanData();
    db.close((err) => {
        if (err) {
            return console.error(err.message);
        }
        console.log('Close the database connection.');
    });
}

function printMostCommonMoves(rowCount) {
    db.all(`SELECT Sum(count) FROM move_count`, (err, rows) => {
        if (err)
            throw new Error("");
        rows.forEach(element => {
            console.log(element.name)
        });
    })
}

asyncMain();
//printMostCommonMoves(10);