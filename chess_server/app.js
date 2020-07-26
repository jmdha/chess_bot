var exec = require('child_process').execFile;
var path = require('path');

const express = require('express')
const app = express()
const port = 3000



app.use(express.static('public'));
app.use(express.json());

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/public/index.html');
});

app.post('/move', async function (req, res) {
    try {
        const output = await getAIMove(req.body.fen, req.body.moves);

        res.end(output);
    } catch(error) {
        console.error(error.toString());
        res.end();
    }
    
});

app.listen(port, () => console.log('Listening on port: ' + port));


function getAIMove(fen, moves) {
    let depth = 3;
    

    return new Promise(function(resolve, reject) {
        console.log(fen);
    console.log(moves);
        let optionals;

        if (moves.length > 0) 
            optionals = new Array(`${depth}`, fen, moves);
        else
            optionals = new Array(`${depth}`, fen);
        console.log("Getting Move...");
        exec(path.resolve(__dirname, './chess_engine/chess_engine.exe'), optionals, function (error, output) {
            console.log("Done.");
            let move = output.split("\n")[1].trim();
            console.log(move);
            if (output.split("\n").length > 3) {
                let outcome = output.split("\n")[2].trim();
                console.log(outcome);
                resolve(outcome);
            } else 
            resolve(move);
        });
    });
}