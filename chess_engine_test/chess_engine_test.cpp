#include "pch.h"
#include "CppUnitTest.h"
#include "Headers/board.h"
#include "Headers/constants.h"
#include "Headers/piece.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EngineTest
{
	TEST_CLASS(BoardTest)
	{
	public:

		TEST_METHOD(InitialState)
		{
			Board board = Board();
			// tests blank squares
			for (int y = 2; y < 6; y++)
				for (int x = 0; x < 8; x++)
					Assert::IsTrue(board.isSquareEmpty(x, y));

			// tests for pawn placement
			for (int x = 0; x < 8; x++) {
				Assert::IsTrue(PAWNWHITE == board.getPiece(x, PAWNROWWHITE)->getPieceChar());
				Assert::IsTrue(PAWNBLACK == board.getPiece(x, PAWNROWBLACK)->getPieceChar());
			}
			// tests rooks
			Assert::IsTrue(ROOKWHITE == board.getPiece(0, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(ROOKWHITE == board.getPiece(7, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(ROOKBLACK == board.getPiece(0, BACKROWBLACK)->getPieceChar());
			Assert::IsTrue(ROOKBLACK == board.getPiece(7, BACKROWBLACK)->getPieceChar());
			// tests knights
			Assert::IsTrue(KNIGHTWHITE == board.getPiece(1, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(KNIGHTWHITE == board.getPiece(6, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(KNIGHTBLACK == board.getPiece(1, BACKROWBLACK)->getPieceChar());
			Assert::IsTrue(KNIGHTBLACK == board.getPiece(6, BACKROWBLACK)->getPieceChar());
			// tests bishops
			Assert::IsTrue(BISHOPWHITE == board.getPiece(2, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(BISHOPWHITE == board.getPiece(5, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(BISHOPBLACK == board.getPiece(2, BACKROWBLACK)->getPieceChar());
			Assert::IsTrue(BISHOPBLACK == board.getPiece(5, BACKROWBLACK)->getPieceChar());
			// tests queens
			Assert::IsTrue(QUEENWHITE == board.getPiece(3, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(QUEENBLACK == board.getPiece(3, BACKROWBLACK)->getPieceChar());
			// tests kings
			Assert::IsTrue(KINGWHITE == board.getPiece(4, BACKROWWHITE)->getPieceChar());
			Assert::IsTrue(KINGBLACK == board.getPiece(4, BACKROWBLACK)->getPieceChar());
		}

		TEST_METHOD(ClearBoard) {
			Board board = Board();
			board.clearBoard();
			for (int y = 0; y < 8; y++)
				for (int x = 0; x < 8; x++)
					Assert::IsTrue(board.isSquareEmpty(x, y));
		}

		TEST_METHOD(GetPiece) {
			Board board = Board();
			Assert::IsTrue(nullptr == board.getPiece(-1, -1));
			Assert::IsTrue(nullptr == board.getPiece(4, 4));
			Assert::IsTrue(nullptr != board.getPiece(0, 0));
		}

		TEST_METHOD(IsSquareEmpty) {
			Board board = Board();
			Assert::IsTrue(board.isSquareEmpty(-1, -1));
			Assert::IsTrue(board.isSquareEmpty(4, 4));
			Assert::IsTrue(!board.isSquareEmpty(0, 0));
		}
	};
}
