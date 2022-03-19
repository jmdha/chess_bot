#include "CppUnitTest.h"
#include <chess_engine/Classes/Headers/ai.h>
#include <chess_engine/Classes/Headers/board.h>
#include <chess_engine/Classes/Headers/move.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GenerateMoveTest
{
	TEST_CLASS(ForceCheckmateSequence)
	{
	public:
		TEST_METHOD(ForceCheckmateIn1_Depth1)
		{
            Board board = Board();
            board.ImportFEN("k7/8/1K6/8/8/8/8/2Q5");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 1, totalMoves);

            Assert::AreEqual("c1c8", move.GetMoveAsPlainString().c_str());
		}

        TEST_METHOD(ForceCheckmateIn1_Depth2)
        {
            Board board = Board();
            board.ImportFEN("k7/8/1K6/8/8/8/8/2Q5");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 2, totalMoves);

            Assert::AreEqual("c1c8", move.GetMoveAsPlainString().c_str());
        }

        TEST_METHOD(ForceCheckmateIn1_Depth1_2)
        {
            Board board = Board();
            board.ImportFEN("7k/1p5P/1p2P3/3pP3/1rbP4/2n5/8/K7 b");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 1, totalMoves);

            Assert::AreEqual("b4b1", move.GetMoveAsPlainString().c_str());
        }

        TEST_METHOD(ForceCheckmateIn1_Depth2_2)
        {
            Board board = Board();
            board.ImportFEN("7k/1p5P/1p2P3/3pP3/1rbP4/2n5/8/K7 b");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 2, totalMoves);

            Assert::AreEqual("b4b1", move.GetMoveAsPlainString().c_str());
        }

        TEST_METHOD(ForceCheckmateIn2_Depth2)
        {
            Board board = Board();
            board.ImportFEN("6k1/p7/1pn1N1r1/2pn3p/8/P1B1p3/1P6/2K2R2");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 2, totalMoves);

            Assert::AreEqual("f1f8", move.GetMoveAsPlainString().c_str());
        }

        TEST_METHOD(ForceCheckmateIn2_Depth3)
        {
            Board board = Board();
            board.ImportFEN("6k1/p7/1pn1N1r1/2pn3p/8/P1B1p3/1P6/2K2R2");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 3, totalMoves);

            Assert::AreEqual("f1f8", move.GetMoveAsPlainString().c_str());
        }

        TEST_METHOD(ForceCheckmateIn2_Depth4)
        {
            Board board = Board();
            board.ImportFEN("6k1/p7/1pn1N1r1/2pn3p/8/P1B1p3/1P6/2K2R2");
            for (int i = 0; i < 2; i++)
                for (int i2 = 0; i2 < 2; i2++)
                    board.castlingValid[i][i2] = false;

            int totalMoves = 0;

            Move move = GenerateMove(&board, 4, totalMoves);

            Assert::AreEqual("f1f8", move.GetMoveAsPlainString().c_str());
        }
	};
}
