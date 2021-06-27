const fs = require('fs');

let bearerID;
let botID;
readID();

function readID() {
    let ids = fs.readFileSync('id.txt', 'utf8').split('\n');
    bearerID = ids[0].split(' ')[1].trim();
    botID = ids[1].split(' ')[1].trim();
}


console.log(process.cwd());
