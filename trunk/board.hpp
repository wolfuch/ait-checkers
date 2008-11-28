/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * checkers
 * Copyright (C)  2008 <>
 *
 * checkers is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * checkers is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _BOARD_HPP_
#define _BOARD_HPP_

#define WHITEMAN 1
#define BLACKMAN 2
#define WHITEKING 3
#define BLACKKING 4
#define WHITE 0
#define BLACK 1
#define EMPTY 0

#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <math.h>

class board
{
public:
		board();// board constructor
		~board(){delete [] boardMatrix;}
		const board &operator=( const board & rhs); //not implemented
		void printBoard(); //prints the board to screen
		void printBoardAlternative(); //prints the board to screen
		std::set <unsigned int> getPossibleMoves(int color); //get the possible moves, if input is 0 all possible white moves, if input is 1 all possible black moves
		void calculatePossibleMoves(int color); //calculates the moves but doesn't return them, it's used by get PossibleMoves
		int** getBoard();//returns the board in the form of an array
		bool movePiece(int sequence,int color);//moves a checker (not implemented, YET)
		void undoMove();//undo the last move, erasing the current state;
		std::set<int> getWhiteCheckers(){return checkers[0];};
		std::set<int> getBlackCheckers(){return checkers[1];};
		std::set<int> getWhiteKings(){return kings[0];};
		std::set<int> getBlackKings(){return kings[1];};
		unsigned int terminal();
		void clean();
		void printSet(std::set<unsigned int> &set);

protected:

private:
		bool canJump(int directionI, int directionJ, int i, int j,int color);//sees if there is a possibility for a jump
		bool insideBoard(int i, int j); //checks if the postion is inside the board
		void calculateJumps(int i, int j,int sequence, int depth, int color, int type);//how many jumps can be made in a single move
		int forcedToMove; //if one there is at least one move were there is a jump
		std::set<unsigned int> moves; //list of all moves
		std::set<unsigned int> jumpMoves; //list of jumps moves
		int **boardMatrix; //0 = free position, 1 = normal white, 2 = normal black, 3 = king white, 4 = king black
		std::set<int> whiteCheckers; //all whiteCheckers positions
		std::set<int> whiteKings; //all whiteKings positions
		std::set<int> blackCheckers; //all blackCheckers positions
		std::set<int> blackKings; //all blackKings positions
		std::set<int> checkers[2]; //all checkers positions, 0 is all the white checkers, 1 all black checkers
		std::set<int> kings[2]; //all kings position, 0 is all the white kings, 1 all the black kings
		std::list< std::list<int> > moveRecords; //necessary to undo moves
};

#endif // _BOARD_HPP_
