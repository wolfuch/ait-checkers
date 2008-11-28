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
	int iterativeMaxLevel = 3;		// max level for iterative deepening search
	this->b = b;
	this->color = color;
	maxLevel = 2;
	iteration = 0;


	//for (maxLevel=0; maxLevel <= iterativeMaxLevel; ++maxLevel) {
		minMax(0, MINUS_INFINITY, PLUS_INFINITY);
	//}
	return actualMove;
}

int Heuristic::evaluation() {
	int sumWhite = 0;
	int sumBlack = 0;
	int x,y;
	std::set<int>::iterator setIterator;


	// white pieces
	for(setIterator = (b->getWhiteCheckers()).begin(); setIterator != (b->getWhiteCheckers()).end(); ++setIterator)
	{
		y = *setIterator / 10;
		// x = *setIterator % 10;    // maybe used in future
		sumWhite += PIECE_VALUE + y*y;
	}

	// white kings
	if(!(b->getWhiteKings()).empty())
	for(setIterator = (b->getWhiteKings()).begin(); setIterator != (b->getWhiteKings()).end(); ++setIterator)
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
	for(setIterator = (b->getBlackCheckers()).begin(); setIterator != (b->getBlackCheckers()).end(); ++setIterator)
	{
		y = 9 - (*setIterator / 10);
		// x = *setIterator % 10;    // maybe used in future
		sumBlack += PIECE_VALUE + y*y;
	}

	// black kings
	if(!(b->getBlackKings()).empty())
	for(setIterator = (b->getBlackKings()).begin(); setIterator != (b->getBlackKings()).end(); ++setIterator)
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
        set<unsigned int> tempMoveSet,tempMoveSet2;
        set<unsigned int>::iterator iter, iterEnd;

        iteration++;
       // std::cout<<"iteration "<<iteration;
        std::cout<<std::endl<<"level: "<<level<<" ";

        winCheck = b->terminal();
        if (winCheck == color+2)     // computer wins
            return PLUS_INFINITY;
        if (winCheck == 1)     // draw
            return 0;
        if (winCheck != 0)              // opponent wins
            return MINUS_INFINITY;


        // Leaf
        if (level == maxLevel) {
        	//evaluation();
        	return evaluation();
        }

        // MAX
        if (level % 2 == 0) {

        	// getting possible moves
        	b->calculatePossibleMoves(color);
        	tempMoveSet = b->getPossibleMoves(color);
       		iter = tempMoveSet.begin();
   			iterEnd = tempMoveSet.end();

            for (; iter != iterEnd; ++iter) {
        	    if (alpha >= beta)      // while (alpha < beta)
                	break;
                b->movePiece(*iter, color);
                b->printBoardAlternative();
                tempMoveSet2 = b->getPossibleMoves(color);
                b->printSet(tempMoveSet);
                tmp = minMax(level+1, alpha, beta);
                b->undoMove();
                b->printBoardAlternative();
                tempMoveSet2 = b->getPossibleMoves(color);
                b->printSet(tempMoveSet);
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
    	   	iter = tempMoveSet.begin();
    	   	iterEnd = tempMoveSet.end();

            for (; iter != iterEnd; ++iter) {
        	    if (alpha >= beta)      // while (alpha < beta)
                	break;
                b->movePiece(*iter, !color);
                b->printBoardAlternative();
                b->printSet(b->getPossibleMoves(!color));
                b->printSet(tempMoveSet);
                tmp = minMax(level+1, alpha, beta);
                b->undoMove();
                b->printBoardAlternative();
                b->printSet(b->getPossibleMoves(!color));
                b->printSet(tempMoveSet);
                b->calculatePossibleMoves(!color);
                if (tmp < beta) {
        	        beta = tmp;
                }
            }
            return beta;
        }

}


