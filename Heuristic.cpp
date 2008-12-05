/*
 ********************************************************
 *  Filename:   Heuristic.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "Heuristic.h"

Heuristic::Heuristic() {
	// TODO Auto-generated constructor stub

}

Heuristic::~Heuristic() {
	// TODO Auto-generated destructor stub
}


unsigned int Heuristic::bestMove(board* b, int color) {
	int iterativeMaxLevel = 7;		// max level for iterative deepening search
	this->b = b;
	this->color = color;

	maxLevel = 7;
	iteration = 0;
	counter = 0;
	firstMove = false;
	for(int i=0; i<ARRAY_SIZE; ++i) {
		bestLeafPath[i] = 0;
		tmpLeafPath[i] = 0;
	}

	working = true;
//	for (maxLevel=1; maxLevel <= iterativeMaxLevel; ++maxLevel) {
		if (maxLevel % 2 == 0)
			bestLeafValue = PLUS_INFINITY;
		else
			bestLeafValue = MINUS_INFINITY;
		iteration = 0;
		minMax(0, MINUS_INFINITY, PLUS_INFINITY);
		std::cout<<iteration<<std::endl;
//		firstMove = true;
//	}
	working = false;
	return actualMove;
}

int Heuristic::evaluation() {
	int sumWhite = 0;
	int sumBlack = 0;
	int x,y;
	std::set<int>::iterator setIterator;


	// white pieces
	for(setIterator = b->checkers[0].begin(); setIterator != b->checkers[0].end(); ++setIterator)
	{
		y = *setIterator / 10;
		// x = *setIterator % 10;    // maybe used in future
		sumWhite += PIECE_VALUE + y*y;
	}

	// white kings
	if(!(b->getWhiteKings()).empty())
		for(setIterator = b->kings[0].begin(); setIterator != b->kings[0].end(); ++setIterator)
		{
			y = *setIterator / 10;
			x = *setIterator % 10;
			sumWhite += KING_VALUE + y*y;
			if (y == 1 || y == 8 || x == 1 || x == 8) {		// king in the edge
				if (x == y)	{	// king in one of corners (11, 88)
					sumWhite -= CORNER_PENALTY;
				}
				else {
					sumWhite -= EDGE_PENALTY;
				}
			}
		}

	// black pieces
	for(setIterator = b->checkers[1].begin(); setIterator != b->checkers[1].end(); ++setIterator)
	{
		y = 9 - (*setIterator / 10);
		// x = *setIterator % 10;    // maybe used in future
		sumBlack += PIECE_VALUE + y*y;
	}

	// black kings
	if(!(b->getBlackKings()).empty())
		for(setIterator = b->kings[1].begin(); setIterator != b->kings[1].end(); ++setIterator)
		{
			y = 9 - (*setIterator / 10);
			x = *setIterator % 10;
			sumBlack += KING_VALUE + y*y;
			if (y == 1 || y == 8 || x == 1 || x == 8) {		// king in the edge
				if (x == y)	{	// king in one of corners (11, 88)
					sumBlack -= CORNER_PENALTY;
				}
				else {
					sumBlack -= EDGE_PENALTY;
				}
			}
		}

	// checking which player AI is playing
	if (color == WHITE) {
		return sumWhite - sumBlack;
	}
	else {
		return sumBlack - sumWhite;
	}

}

int Heuristic::minMax(int level, int alpha, int beta) {
	int tmp = 0;    // temporary value which is compared to max value
	int winCheck=0;

	set<unsigned long long int> tempMoveSet;
	set<unsigned long long int>::iterator iter, iterEnd, iterTmp;




	winCheck = b->terminal();
	if (winCheck == color+2)     // computer wins
		return PLUS_INFINITY;
	if (winCheck == 1)     // draw
		return 0;
	if (winCheck != 0)              // opponent wins
		return MINUS_INFINITY;


	// Leaf
	if (level == maxLevel) {
		tmp = evaluation();
		iteration++;
		if (level % 2 == 0) {		// min of evaluation function
			if (tmp < bestLeafValue) {
				bestLeafValue = tmp;
				for(int i=0; i<ARRAY_SIZE; ++i) {
						bestLeafPath[i] = tmpLeafPath[i];
				}
			}
		}
		else						// max of evaluation function
		{
			if (tmp > bestLeafValue) {
				bestLeafValue = tmp;
				for(int i=0; i<ARRAY_SIZE; ++i) {
						bestLeafPath[i] = tmpLeafPath[i];
				}
			}
		}
		return tmp;
	}


	// MAX
	if (level % 2 == 0) {

		// getting possible moves
		b->calculatePossibleMoves(color);
		tempMoveSet = b->getPossibleMoves(color);

		// look for the best move already found and replace it with the first from the set
		if (firstMove) {
			if (level == maxLevel-2) {
				firstMove = false;
			}
			tempMoveSet.erase(bestLeafPath[level]);

			// copied part from above
			b->movePiece(bestLeafPath[level], color);
			tmpLeafPath[level] = bestLeafPath[level];
			tmp = minMax(level+1, alpha, beta);
			b->undoMove();
			tmpLeafPath[level] = 0;
			b->clean();
			b->calculatePossibleMoves(color);
			if (tmp > alpha) {
				alpha = tmp;
				if (level == 0) {
					actualMove = bestLeafPath[level];
				}
			}
		}

		iter = tempMoveSet.begin();
		iterEnd = tempMoveSet.end();

		for (; iter != iterEnd; ++iter) {
			if (alpha >= beta)      // while (alpha < beta)
				break;
			b->movePiece(*iter, color);
			tmpLeafPath[level] = *iter;
			tmp = minMax(level+1, alpha, beta);
			b->undoMove();
			tmpLeafPath[level] = 0;
			b->clean();
			b->calculatePossibleMoves(color);
			if (tmp > alpha) {
				alpha = tmp;
				if (level == 0) {
					actualMove = *iter;
				}
			}
		}
		return alpha;
	}

	// MIN
	else {

		// getting possible moves
		b->calculatePossibleMoves(!color);
		tempMoveSet = b->getPossibleMoves(!color);

		// look for the best move already found and replace it with the first from the set
		if (firstMove) {
			if (level == maxLevel-2) {
				firstMove = false;
			}
			tempMoveSet.erase(bestLeafPath[level]);

			// copied part from above
			b->movePiece(bestLeafPath[level], !color);
			tmpLeafPath[level] = bestLeafPath[level];
			tmp = minMax(level+1, alpha, beta);
			b->undoMove();
			tmpLeafPath[level] = 0;
			b->clean();
			b->calculatePossibleMoves(!color);
			if (tmp < beta) {
				beta = tmp;
			}
		}

		iter = tempMoveSet.begin();
		iterEnd = tempMoveSet.end();

		for (; iter != iterEnd; ++iter) {
			if (alpha >= beta)      // while (alpha < beta)
				break;
			b->movePiece(*iter, !color);
			tmpLeafPath[level] = *iter;
			tmp = minMax(level+1, alpha, beta);
			b->undoMove();
			tmpLeafPath[level] = 0;
			b->clean();
			b->calculatePossibleMoves(!color);
			if (tmp < beta) {
				beta = tmp;
			}
		}
		return beta;
	}

}


bool Heuristic::isWorking()
{
	return working;
}
