/*
 ********************************************************
 *  Filename:   Heuristic.cpp
 ********************************************************
 *  Created on: Nov 5, 2008
 *      Author: marc
 ********************************************************
 */

#include "Heuristic.h"
#include <string.h>


Heuristic::Heuristic() {

}

Heuristic::Heuristic(AIPlayer *aiPlayer) {
	this->aiPlayer =  aiPlayer;

}

Heuristic::~Heuristic() {
	// TODO Auto-generated destructor stub
}


unsigned int Heuristic::bestMove(board* b, int color) {
	int iterativeMaxLevel = ARRAY_SIZE;		// max level for iterative deepening search
	this->b = b;
	this->color = color;
	unsigned long long upArray[ARRAY_SIZE];

	memset(upArray,0,sizeof(unsigned long long)*ARRAY_SIZE);

	int sum=0;
	timeoutMove = 0;

	//maxLevel = 4;
	iteration = 0;
	counter = 0;
	firstMove = false;
	for(int i=0; i<ARRAY_SIZE; ++i) {
		bestLeafPath[i] = 0;
	}

	b->calculatePossibleMoves(color);
	if (b->getPossibleMoves(color).size() == 1)
		return *(b->getPossibleMoves(color).begin());

	for (maxLevel=1; maxLevel <= iterativeMaxLevel; ++maxLevel) {
		memset(upArray,0,sizeof(unsigned long long)*ARRAY_SIZE);		// filling array with 0
		iteration = 0;
		minMax(0, MINUS_INFINITY, PLUS_INFINITY, upArray);
		for (int i=0; i<ARRAY_SIZE; ++i) {								// copy best move found in last minMax
			bestLeafPath[i] = upArray[i];
		}
		std::cout<<iteration<<std::endl;
		sum += iteration;
		firstMove = true;
	}
	std::cout<<std::endl<<"sum: "<<sum<<std::endl;
	if (timeoutMove > 0 ) {			// timeout occurred, get last best value
		return timeoutMove;
	}
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

int Heuristic::minMax(int level, int alpha, int beta, unsigned long long downArray[]) {
	int tmp = 0;    // temporary value which is compared to max value
	int winCheck=0;

	set<unsigned long long int> tempMoveSet;
	set<unsigned long long int>::iterator iter, iterEnd, iterTmp;


	if (!aiPlayer->working) {			// if timeout!
		return 0;		// value doesn't matter
	}


	winCheck = b->terminal();
	if (winCheck == color+2)     // computer wins
		return PLUS_INFINITY / level;
	if (winCheck == 1)     // draw
		return 0;
	if (winCheck != 0)              // opponent wins
		return MINUS_INFINITY;


	// Leaf
	if (level == maxLevel) {
		iteration++;
		return evaluation();
	}


	// MAX
	if (level % 2 == 0) {

		// getting possible moves
		b->calculatePossibleMoves(color);
		tempMoveSet = b->getPossibleMoves(color);


		if (firstMove) {
			if (level == maxLevel-2) {		// in next minMax call start exploring tree without first move path
				firstMove = false;
			}
			tempMoveSet.erase(bestLeafPath[level]);		// delete best move from the set

			// copied part from above
			b->movePiece(bestLeafPath[level], color);	// do the best move
			unsigned long long * upArray;		// array given to upper minMax call
			upArray = new unsigned long long [ARRAY_SIZE];
			memset(upArray,0,sizeof(unsigned long long)*ARRAY_SIZE);		// cleaning array with 0
			tmp = minMax(level+1, alpha, beta, upArray);
			b->undoMove();
			b->clean();
			b->calculatePossibleMoves(color);
			if (tmp > alpha) {
				alpha = tmp;
				downArray[level] = bestLeafPath[level];						// store best move so far (at current level)
				for(int i = level+1; i<maxLevel; ++i) {			// copy good moves from higher levels
					downArray[i] = upArray[i];
				}
				if (level == 0) {
					actualMoveMutex.acquire();
						actualMove = bestLeafPath[level];
					actualMoveMutex.release();
				}
			}
			delete[] upArray;
		}

		iter = tempMoveSet.begin();
		iterEnd = tempMoveSet.end();

		for (; iter != iterEnd; ++iter) {
			if (alpha >= beta)      // while (alpha < beta)
				break;
			b->movePiece(*iter, color);
			unsigned long long * upArray;		// array given to upper minMax call
			upArray = new unsigned long long [ARRAY_SIZE];
			memset(upArray,0,sizeof(unsigned long long)*ARRAY_SIZE);		// cleaning array with 0
			tmp = minMax(level+1, alpha, beta, upArray);
			b->undoMove();
			b->clean();
			b->calculatePossibleMoves(color);
			if (tmp > alpha) {
				alpha = tmp;
				downArray[level] = *iter;						// store best move so far (at current level)
//std::cout<<std::endl<<"level: "<<level<<" downArray: ";
				for(int i = level+1; i<maxLevel; ++i) {			// copy good moves from higher levels
					downArray[i] = upArray[i];
				}
//for (int i =0; i<ARRAY_SIZE; ++i) {
//	std::cout<<downArray[i]<<", ";
//}
				if (level == 0) {
					actualMoveMutex.acquire();
						actualMove = *iter;
					actualMoveMutex.release();
				}
			}
			delete[] upArray;
		}
		return alpha;
	}

	// MIN
	else {

		// getting possible moves
		b->calculatePossibleMoves(!color);
		tempMoveSet = b->getPossibleMoves(!color);


		if (firstMove) {
			if (level == maxLevel-2) {		// in next minMax call start exploring tree without first move path
				firstMove = false;
			}
			tempMoveSet.erase(bestLeafPath[level]);		// delete best move from the set

			// copied part from above
			b->movePiece(bestLeafPath[level], !color);	// do the best move
			unsigned long long * upArray;		// array given to upper minMax call
			upArray = new unsigned long long [ARRAY_SIZE];
			memset(upArray,0,sizeof(unsigned long long)*ARRAY_SIZE);		// cleaning array with 0
			tmp = minMax(level+1, alpha, beta, upArray);
			b->undoMove();
			b->clean();
			b->calculatePossibleMoves(!color);
			if (tmp < beta) {
				beta = tmp;
				downArray[level] = bestLeafPath[level];						// store best move so far (at current level)
				for(int i = level+1; i<maxLevel; ++i) {			// copy good moves from higher levels
					downArray[i] = upArray[i];
				}
			}
			delete[] upArray;
		}

		iter = tempMoveSet.begin();
		iterEnd = tempMoveSet.end();

		for (; iter != iterEnd; ++iter) {
			if (alpha >= beta)      // while (alpha < beta)
				break;
			b->movePiece(*iter, !color);
			unsigned long long * upArray;		// array given to upper minMax call
			upArray = new unsigned long long [ARRAY_SIZE];
			memset(upArray,0,sizeof(unsigned long long)*ARRAY_SIZE);		// cleaning array with 0
			tmp = minMax(level+1, alpha, beta, upArray);
			b->undoMove();
			b->clean();
			b->calculatePossibleMoves(!color);
			if (tmp < beta) {
				beta = tmp;
				downArray[level] = *iter;						// store best move so far (at current level)
				for(int i = level+1; i<maxLevel; ++i) {			// copy good moves from higher levels
					downArray[i] = upArray[i];
				}
			}
			delete[] upArray;
		}
		return beta;
	}

}



void Heuristic::timeoutOccured() {
	actualMoveMutex.acquire();
		timeoutMove = actualMove;
	actualMoveMutex.release();
}
