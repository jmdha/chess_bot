"use strict"

// ------------------ INIT -------------------

var config = {
    draggable: true,
    dropOffBoard: 'snapback', // this is the default
    position: 'start',
    onDrop: onDrop
}
var board = Chessboard('board', config);

// ------------------Chess Board Events-------------------
var currentSide = "b";
var oldMoves = "";

async function onDrop(source, target) {
    oldMoves += source + "-" + target + " ";
}

getNewMove();

async function commitMove(move) {
    console.log(currentSide);
    if (move == "O-O" || move == "O-O-O") {
        let y;
        if (currentSide == "w") 
            y = 1;
        else 
            y = 8;
        
        if (move == "O-O") {
            board.move("e" + y + "-g" + y);
            board.move("h" + y + "-f" + y);
        } else {
            board.move("e" + y + "-c" + y);
            board.move("a" + y + "-d" + y);
        }
    } else
        board.move(move);
}



async function getNewMove() {
    currentSide = ((currentSide == "w") ? "b" : "w");
    let response = await fetch('/move', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            fen: board.fen() + " " + currentSide,
            moves: oldMoves
        })

    });

    if (response.ok) {
        let move = await response.text();
        commitMove(move);
        setTimeout(function(){
            if (move == "draw" || move == "checkmate") {
                board = Chessboard('board', config);
                oldMoves = "";
                currentSide = "b";
            }  
            else {
                oldMoves += move + " ";
            }  
            getNewMove();
        }, 1000);  
    }
}