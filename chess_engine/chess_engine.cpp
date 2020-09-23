#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include "sqlite3.h"
#include "Classes/Headers/board.h"
#include "Classes/Headers/move.h"
#include "Classes/Pieces/Headers/knight.h"
#include "Classes/Headers/generic_helper_functions.h"
#include "Classes/Headers/ai.h"
#include "Classes/Headers/database.h"

int getChessMove(int argc, char* argv[])
{
	auto t1 = std::chrono::high_resolution_clock::now();
	int depth;
	Board board(WHITE);
	if (argc < 2)
	{
		return 1;
	}
	else
	{
		depth = atoi(argv[1]);
	}

	if (argc > 3)
	{
		std::string moves = argv[3];
		moves.erase(
			remove(moves.begin(), moves.end(), '\"'),
			moves.end());
		if (isNumber(moves[0]))
			board.importPGN(moves, false, nullptr);
		else
			board.importFakePGN(moves);
	}
	else if (argc > 2)
	{
		std::string fen = argv[2];
		fen.erase(
			remove(fen.begin(), fen.end(), '\"'),
			fen.end());
		board.importFEN(fen);
	}
	board.printBoard();

	Move bestMove = getBestMove(&board, depth);
	board.commitMove(&bestMove);

	printf("%s\n", bestMove.getMoveAsString().c_str());
	if (static_cast<int>(getAllMoves(board, board.turn).size()) == 0)
	{
		printf("draw\n");
	}
	else if (!board.kingAlive[WHITE] || !board.kingAlive[BLACK])
	{
		printf("checkmate\n");
	}

	auto t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
	return 0;
}

void getHash(char* PGN, Database* db)
{

	Board board(WHITE);
	std::string moves = PGN;
	bool printPerMove = true;
	moves.erase(
		remove(moves.begin(), moves.end(), '\"'),
		moves.end());
	if (isNumber(moves[0]))
		board.importPGN(moves, printPerMove, db);
	else
		board.importFakePGN(moves);
	if (!printPerMove)
		printf("%lu\n", board.zobrist->getHash());
}

void goThroughFile(const char* path, Database* db) {
	std::ifstream file(path);
	std::string str;
	long gameCount = 0;
	while (std::getline(file, str)) {
		if (str.length() > 4 && str[0] != '[') {
			char* ch = const_cast<char*>(str.c_str());
			getHash(ch, db);
			gameCount++;
			if (gameCount % 10 == 0) {
				db->printProgress();
				printf("Progress %f\%\n", gameCount / 697600.0f * 100.0f);
			}
		}

	}
}

void goThroughAllPGNFIles(const char* path, Database* db) {
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		const auto filePath = entry.path().string();
		goThroughFile(filePath.c_str(), db);
	}
}

int main(int argc, char* argv[]) {
	const char* path = "data.db";
	Database db = Database(path);
	std::string sql = "";

	goThroughAllPGNFIles("./Data/", &db);

	db.closeDatabase();
	return 0;

	/*
		Board board = Board();
		board.clearBoard();
		board.importFEN("8/8/8/8/1Pp5/8/8/8 w - - 0 1");
		board.enPassant = 1;
		board.turn = BLACK;
		std::vector<Move> moves = getAllMoves(board, board.turn);
		board.printBoard();
		printf("-----------------\n");
		board.doMove(&moves[0]);
		board.printBoard();


	return 0;
	*/
}

