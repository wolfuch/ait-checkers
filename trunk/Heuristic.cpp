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


unsigned int Heuristic::bestMove(board* b, int color){
	int move;
	this->b = b;
	this->color = color;
	maxLevel = 7;
	iteration = 0;

	move = minMax(0, MINUS_INFINITY, PLUS_INFINITY);
	std::cout<<iteration;
	return move;
}

int Heuristic::evaluation() {
	int sumWhite = 0;
	int sumBlack = 0;
	int x,y;
	std::set<int>::iterator setIterator;
	std::set<int> set;
	
	
	// white pieces
	for(setIterator = set.begin(); setIterator != set.end(); ++setIterator)
	{
		y = *setIterator / 10;
		// x = *setIterator % 10;    // maybe used in future
		sumWhite += PIECE_VALUE + y*y;
	}
	
	// white kings
	for(setIterator = set.begin(); setIterator != set.end(); ++setIterator)
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
	for(setIterator = set.begin(); setIterator != set.end(); ++setIterator)
	{
		y = 9 - (*setIterator / 10);
		// x = *setIterator % 10;    // maybe used in future
		sumBlack += PIECE_VALUE + y*y;
	}

	// black kings
	for(setIterator = set.begin(); setIterator != set.end(); ++setIterator)
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
        set<unsigned int>::iterator iter, iterEnd;      
        
        iteration++;
        
        b->calculatePossibleMoves(color);
        winCheck = b->terminal();
        if (winCheck == color+2)     // computer wins
            return PLUS_INFINITY;
        if (winCheck == 1)     // draw
            return 0;
        if (winCheck != 0)              // opponent wins
            return MINUS_INFINITY;
        
        
        // Leaf
        if (level == maxLevel) {
        	return evaluation();
        }
        
        // getting possible moves  
		iter = (b->getPossibleMoves(color)).begin();
		iterEnd = (b->getPossibleMoves(color)).end();
        
        // MAX       
        if (level % 2 == 0) {
            for (; iter != iterEnd; ++iter) {
        	    if (alpha >= beta)      // while (alpha < beta)
                	break;
                b->movePiece(*iter, color);
                tmp = minMax(level+1, alpha, beta);
                b->undoMove();
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
            for (; iter != iterEnd; ++iter) {
        	    if (alpha >= beta)      // while (alpha < beta)
                	break;
                b->movePiece(*iter, color);
                tmp = minMax(level+1, alpha, beta);
                b->undoMove();
                if (tmp < beta) {
        	        beta = tmp;
                }                
            }
            return beta;
        }
        
}


