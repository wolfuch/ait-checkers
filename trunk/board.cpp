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

#include <iostream>
#include "board.hpp"

//constructor
board::board() //READY!
{

	boardMatrix = new int*[9]; //creates a pointer array (matrix)
	for (int i=0; i<9; i++)//initializes the array in order to create a matrix
		boardMatrix[i] = new int[9];


	for(int i=0;i<9;i++) //fill it with zeros just in case
		for(int j=0;j<9;j++)
			boardMatrix[i][j]=0;

	for(int i=1;i<4;i++)//We put the white checkers on the board
	{
		for(int j=i%2+1;j<9;j+=2)
		{
			boardMatrix[i][j]=WHITEMAN;
			whiteCheckers.insert(i*10+j); //we add the checkers to the list
		}
	}

	for(int i=6;i<9;i++)//We put the black checkers on the board
	{

		for(int j=i%2+1;j<9;j+=2)
		{
			boardMatrix[i][j]=BLACKMAN;
			blackCheckers.insert(i*10+j);//we add the checkers to the blackCheckers list
		}
	}

	checkers[WHITE]=whiteCheckers;
	checkers[BLACK]=blackCheckers;

	kings[WHITE]=whiteKings;
	kings[BLACK]=blackKings;
}

//Prints the board
void board::printBoard()// READY!
{
	for(int i=8;i>0;i--)
	{
		for(int j=1;j<9;j++)
			std::cout<<boardMatrix[i][j]<<" ";
		std::cout<<std::endl;
	}

	std::cout<<"\n\n\n";
}

//returns the board
int** board::getBoard() // READY!
{
	return boardMatrix;
}

//checks if the position is inside the board
bool board::insideBoard(int i, int j) // READY
{
	if(i>0&&i<9&&j>0&&j<9)
		return true;

	return false;
}

//checks if the checker in position (i,j) can make a jump move. Looks if the ending position is inside the board, and if there is a checker to jump.
bool board::canJump(int directionI, int directionJ, int i, int j, int color) // READY
{
	if(insideBoard(i+directionI,j+directionJ)&&
			(boardMatrix[i+directionI][j+directionJ]==(2-color)||boardMatrix[i+directionI][j+directionJ]==(4-color))&&
			insideBoard(i+2*directionI,j+2*directionJ)&&
			boardMatrix[i+2*directionI][j+2*directionJ]==EMPTY)
		return true;
	else
		return false;
}

/* Returns the value of the termination state of the game
 * 0 = Not terminated
 * 1 = Draw
 * 2 = White won
 * 3 = Black won
 */
unsigned int board::terminal(){
   /*if(whiteCheckers.size()==0 && blackCheckers.size()==0 &&    // Draw
           whiteKings.size()==1 && blackKings.size()==1){
       return 1;
   } else if(getPossibleMoves(1).size()==0){        // White won
       return 2;
   } else if(getPossibleMoves(0).size()==0){        // Black won
       return 3;
   } else {  */                              // Not terminated
       return 0;
   //}
}

//how many jumps can be made in a single move, 0 = white and 1 = black
//sequence is the sequence of moves the player has to make
//type 0=man, 1=king
void board::calculateJumps(int i, int j, int sequence, int depth,int color, int type)// NO FIX NEEDED
{
	int start,shift;

	if(type==0&&depth!=1&&sequence/pow(10,depth)==(1+!(color)*7))//checks if the piece is at the end of the board
	{
		jumpMoves.insert(sequence);
		return;
	}

	if(type==0&&color==WHITE)
	{
		start=0;
		shift=2;
	}else if(type==0&&color==BLACK)
	{
		start=1;
		shift=2;
	}else
	{
		start=0;
		shift=1;
	}

	int directionI,directionJ; //to store in which direction we are going to move

	for(int loop=start;loop<4;loop=loop+shift) //we check the for possible jumping directions
	{
		directionI=1-(loop%2)*2;//it will take the values 1 and -1
		directionJ=1-(loop/2)*2;//it will take the values 1 and -1

		if(canJump(directionI,directionJ,i,j,color))//if there is a jumping move
		{

			calculateJumps(i+2*directionI,j+2*directionJ,sequence+(j+2*directionJ)*(pow(10,depth+1))+(i+2*directionI)*(pow(10,depth+2)),depth+2, color,type ); //recursively check if we can extend the move
		}
		else if(depth!=1)
		{
			jumpMoves.insert(sequence); //if no more jumps can be made we store the move
			forcedToMove=1;
		}
	}
}

//calculates all the possible moves
void board::calculatePossibleMoves(int color) //READY!
{
	int i,j;
	forcedToMove=0;
	std::set<int>::iterator it;
	std::set<int> *auxiliaryCheckerList;

	//depending on the color is the list it's going to check
	auxiliaryCheckerList=&(checkers[color]);//this should be right, have to check it later


	//checks the moves for all white checkers
	for ( it=auxiliaryCheckerList->begin() ; it != auxiliaryCheckerList->end(); it++ )
	{
		i=(*it) /10;
		j=(*it) %10;


		if(!forcedToMove)//checks for no jumping moves
		{
			if(insideBoard(i+1-2*color,j+1)&&boardMatrix[i+1-2*color][j+1]==0)//if next position is inside the board and is unoccupied we store the move
				moves.insert((i*10)+j+((i+1-2*color)*1000)+(j+1)*100);

			if(insideBoard(i+1-2*color,j-1)&&boardMatrix[i+1-2*color][j-1]==0)//if next position is inside the board and is unoccupied we store the move
				moves.insert((i*10)+j+((i+1-2*color)*1000)+(j-1)*100);
		}

		calculateJumps(i,j,(*it),1,color,0);
	}

	auxiliaryCheckerList=&(kings[color]);//this should be right, have to check it later


	//checks the moves for all white kings
	for ( it=auxiliaryCheckerList->begin() ; it != auxiliaryCheckerList->end(); it++ )
	{
		i=(*it) /10;
		j=(*it) %10;

		//checks for no jumping moves
		if(!forcedToMove)
		{
			if(i+1<9&&j+1<9&&boardMatrix[i+1][j+1]==0)//if next position is inside the board and is unoccupied we store the move
				moves.insert((i*10)+j+((i+1)*1000)+(j+1)*100);

			if(i+1<9&&j-1>0&&boardMatrix[i+1][j-1]==0)//if next position is inside the board and is unoccupied we store the move
				moves.insert((i*10)+j+((i+1)*1000)+(j-1)*100);

			if(i-1>0&&j+1<9&&boardMatrix[i-1][j+1]==0)//if next position is inside the board and is unoccupied we store the move
				moves.insert((i*10)+j+((i-1)*1000)+(j+1)*100);

			if(i-1>0&&j-1>0&&boardMatrix[i-1][j-1]==0)//if next position is inside the board and is unoccupied we store the move
				moves.insert((i*10)+j+((i-1)*1000)+(j-1)*100);
		}

		calculateJumps(i,j,(*it),1,color,1);
	}

	if(!jumpMoves.empty())
	{
		moves = jumpMoves;
	}
}

std::set<unsigned int> board::getPossibleMoves(int color)// READY
{
	//if(moves.empty())
	//{
		clean();
		calculatePossibleMoves(color);
	//}

	//printSet(moves);

	return moves;
}

void board::clean()//READY!
{
	forcedToMove=0;
	moves.clear();
	jumpMoves.clear();
}

void board::undoMove()
{
	std::list<int> movesMade = moveRecords.back();
	std::list<int>::iterator myIterator;

	int i,j,type;

	for(myIterator=movesMade.begin();myIterator!=movesMade.end();myIterator++)
	{
		i=(*myIterator)/100;
		j=((*myIterator)/10)%10;
		type=(*myIterator)%10;
		boardMatrix[i][j]=type;

		//std::cout<<"\nUNDOING!"<<std::endl;

		if(type==0)
		{
			checkers[0].erase(i*10+j);
			checkers[1].erase(i*10+j);
			kings[0].erase(i*10+j);
			kings[1].erase(i*10+j);

		//	std::cout<<"Erasing piece in position :"<<i<<","<<j<<")"<<std::endl;
		}

		if(type==1)
		{
			checkers[0].insert(i*10+j);
			//std::cout<<"Inserting white man in position :"<<i<<","<<j<<")"<<std::endl;
		}

		if(type==2)
		{
			checkers[1].insert(i*10+j);
			//std::cout<<"Inserting black man in position :"<<i<<","<<j<<")"<<std::endl;
		}

		if(type==3)
		{
			kings[0].insert(i*10+j);
			//std::cout<<"Inserting white king in position :"<<i<<","<<j<<")"<<std::endl;
		}

		if(type==4)
		{
			kings[1].insert(i*10+j);
		//	std::cout<<"Inserting black king in position :"<<i<<","<<j<<")"<<std::endl;
		}
	}

	moveRecords.pop_back();
}

bool board::movePiece(int sequence, int color)//sequence is the sequence of numbers that represent the move, color=0 whiteMoves, color=1 blackMoves
{
	int initialPosition,finalPosition,enemyPosition;
	std::set<int> *auxiliaryCheckerList,*auxiliaryEnemyList;
	std::list<int> movesMade;

	if(jumpMoves.empty()&&moves.count(sequence)>0)
	{
		initialPosition = (sequence%10)+((sequence/10)%10)*10;
		finalPosition = (sequence/100)%10+(sequence/1000)*10;

		//std::cout<<"Moving piece, NO JUMPS in this move"<<std::endl;

		if(boardMatrix[initialPosition/10][initialPosition%10]==(1+color))
		{
			auxiliaryCheckerList=&(checkers[color]);//this should be right, have to check it later

			auxiliaryCheckerList->erase(initialPosition);

			movesMade.push_back(initialPosition*10+1+color);

			//std::cout<<"Erased man of color :"<<color<<" ,in position ("<<initialPosition/10<<","<<initialPosition%10<<")"<<std::endl;

			movesMade.push_back(finalPosition*10+0);

			//std::cout<<"Inserted man of color :"<<color<<" ,in position ("<<finalPosition/10<<","<<finalPosition%10<<")"<<std::endl;

			if(finalPosition/10==(1+!(color)*7))
			{
				(kings[color]).insert(finalPosition);
				boardMatrix[finalPosition/10][finalPosition%10]=3+color;

			}else
			{
				auxiliaryCheckerList->insert(finalPosition);
				boardMatrix[finalPosition/10][finalPosition%10]=1+color;
			}
			boardMatrix[initialPosition/10][initialPosition%10]=0;
		}
		else
		{

			auxiliaryCheckerList=&(kings[color]);//this should be right, have to check it later

			auxiliaryCheckerList->erase(initialPosition);
			auxiliaryCheckerList->insert(finalPosition);
			boardMatrix[initialPosition/10][initialPosition%10]=0;
			boardMatrix[finalPosition/10][finalPosition%10]=3+color;

			movesMade.push_back(initialPosition*10+2+color);
			movesMade.push_back(finalPosition*10+0);
		}

		clean();

		moveRecords.push_back(movesMade);

		return true;

	}else if(jumpMoves.count(sequence)>0)
	{
		//std::cout<<"Moving piece, THERE ARE JUMPS in this move"<<std::endl;

		int auxiliarySequence=sequence;

		while(sequence/100>0)
		{
			initialPosition = sequence%100;
			finalPosition = (sequence/100)%100;
			enemyPosition = 10*((initialPosition/10+finalPosition/10)/2)+(initialPosition%10+finalPosition%10)/2;

			if(boardMatrix[initialPosition/10][initialPosition%10]==(1+color))
			{
				auxiliaryCheckerList=&(checkers[color]);//this should be right, have to check it later

				auxiliaryCheckerList->erase(initialPosition);
				if(auxiliarySequence==sequence)
					movesMade.push_back(initialPosition*10+1+color);

				movesMade.push_back(finalPosition*10+0);
				movesMade.push_back(enemyPosition*10+boardMatrix[enemyPosition/10][enemyPosition%10]);

				//std::cout<<"Erased man of color :"<<color<<" ,in position ("<<initialPosition/10<<","<<initialPosition%10<<")"<<std::endl;

		//		std::cout<<"Inserted man of color :"<<color<<" ,in position ("<<finalPosition/10<<","<<finalPosition%10<<")"<<std::endl;

//				std::cout<<"Erased enemy man of color :"<<!color<<" ,in position ("<<enemyPosition/10<<","<<enemyPosition%10<<")"<<std::endl;


				if(finalPosition/10==(1+!(color)*7))
				{
					(kings[color]).insert(finalPosition);
					boardMatrix[finalPosition/10][finalPosition%10]=3+color;

				}else
				{
					auxiliaryCheckerList->insert(finalPosition);
					boardMatrix[finalPosition/10][finalPosition%10]=1+color;
				}

				boardMatrix[initialPosition/10][initialPosition%10]=0;

				if(boardMatrix[enemyPosition/10][enemyPosition%10]==2-color)
				{
					(checkers[!color]).erase(enemyPosition);
				}
				else
				{
					kings[!color].erase(enemyPosition);
				}

				boardMatrix[enemyPosition/10][enemyPosition%10]=0;
			}
			else
			{
				auxiliaryCheckerList=&(kings[color]);//this should be right, have to check it later

				auxiliaryCheckerList->erase(initialPosition);
				auxiliaryCheckerList->insert(finalPosition);
				boardMatrix[initialPosition/10][initialPosition%10]=0;
				boardMatrix[finalPosition/10][finalPosition%10]=3+color;

				movesMade.push_back(initialPosition*10+2+color);
				movesMade.push_back(finalPosition*10+0);
				movesMade.push_back(enemyPosition*10+boardMatrix[enemyPosition/10][enemyPosition%10]);

				if(boardMatrix[enemyPosition/10][enemyPosition%10]==2-color)
				{
					(checkers[!color]).erase(enemyPosition);
				}
				else
				{
					(kings[!color]).erase(enemyPosition);
				}

				boardMatrix[enemyPosition/10][enemyPosition%10]=0;
			}

			sequence=sequence/100;
		}

		moveRecords.push_back(movesMade);
		clean();
		return true;
	}
	else
	{
		std::cout<<"You are not allowed to make that move!!\nSequence is:"<<sequence<<"\nColor is:"<<color<<std::endl;

		return false;
	}
}

/* ===========================================================
 * Just an alternative methode to display the board (marc)
 * =========================================================== */

void board::printBoardAlternative(){
	std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
	for(int i=8;i>0;i--) {
		std::cout << i << " | ";
		for(int j=1;j<9;j++){
			if(boardMatrix[i][j]!=0){
			std::cout<<boardMatrix[i][j]<<" | ";
			} else {
				std::cout<< " " <<" | ";
			}
		}
		std::cout << std::endl << "  +---+---+---+---+---+---+---+---+" << std::endl;
	//	std::cout<<std::endl;
	}
	std::cout << "    1   2   3   4   5   6   7   8" << std::endl;
	std::cout<<"\n\n\n";
}

void board::printSet(std::set<unsigned int> &set) {
	std::set<unsigned int>::iterator iter = set.begin();
	for(; iter != set.end(); ++iter) {
		std::cout<<*iter<<" ";
	}
	std::cout<<std::endl;
}



