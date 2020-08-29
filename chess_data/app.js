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

                incrementByPGN(line);
                if (gameCount % 100 == 0)
                    printProgress();
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

    for (let i = 0; i < hashMovePairArray.length; i++) {
        incrementHashByMove(hashMovePairArray[i][0], hashMovePairArray[i][1]);
    }

    gameCount++;

}

let hashMovePairBuffer = [];

async function incrementHashByMove(hash, move) {

    if (hashMovePairBuffer.length >= 5) {
        //var sql = `INSERT INTO move_count(hash, move, count) VALUES (?, ?, ?) ON CONFLICT(hash, move) DO UPDATE SET count = count + 1`;
        
        let values = hashMovePairBuffer;
        let sql = `INSERT INTO move_count VALUES (?, ?, ?) ON CONFLICT(hash, move) DO UPDATE SET count = count + 1`;
        hashMovePairBuffer = [];

        db.run(sql, ...values, (err) => {
            if (err)
                console.log("Damn ", err);
        })

    } else {
        incrementCount++;
        hashMovePairBuffer.push([hash, move, 1]);
    }


}

function getHash(PGN) {
    let optionals = new Array(JSON.stringify(PGN));
    return execFileSync(path.resolve(__dirname, '../chess_engine/chess_engine.exe'), optionals, {
        "timeout": 5000
    })
}

function printProgress() {
    let maxGameCount = 697600;
    console.clear();
    console.log((gameCount / maxGameCount * 100).toFixed(3) + '%', gameCount, "/", maxGameCount);
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

//asyncMain();
printMostCommonMoves(10);