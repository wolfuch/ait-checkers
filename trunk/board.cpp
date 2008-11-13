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
board::board()
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
			boardMatrix[i][j]=1;
			whiteCheckers.insert(i*10+j); //we add the checkers to the list
		}
	}
	
	for(int i=6;i<9;i++)//We put the black checkers on the board
	{
		
		for(int j=i%2+1;j<9;j+=2)
		{
			boardMatrix[i][j]=2;
			blackCheckers.insert(i*10+j);//we add the checkers to the blackCheckers list
		}
	}
	
}

//Prints the board
void board::printBoard()
{
	for(int i=8;i>0;i--)
	{
		for(int j=1;j<9;j++)
			std::cout<<boardMatrix[i][j]<<" ";
		std::cout<<std::endl;
	}
}

//returns the board
int** board::getBoard() 
{
	return boardMatrix;
}

//checks if the position is inside the board
bool board::insideBoard(int i, int j) 
{
	if(i>0&&i<9&&j>0&&j<9)
		return true;
	
	return false;
}

//checks if the checker in position (i,j) can make a jump move. Looks if the ending position is inside the board, and if there is a checker to jump.
bool board::canJump(int directionI, int directionJ, int i, int j, int color)
{
	if(insideBoard(i+directionI,j+directionJ)&&
	   (boardMatrix[i+directionI][j+directionJ]==(2-color)||boardMatrix[i+directionI][j+directionJ]==(4-color))&&
	   insideBoard(i+2*directionI,j+2*directionJ)&&
	   boardMatrix[i+2*directionI][j+2*directionJ]==0)
		return true;
	else
		return false;
}

//how many jumps can be made in a single move, 0 = white and 1 = black
//sequence is the sequence of moves the player has to make
//type 0=man, 1=king
int board::calculateJumps(int i, int j, int sequence, int depth,int color, int type)
{
	int start,shift;
	if(type==0&&color==0)
	{
		start=0;
		shift=2;
	}else if(type==0&&color==1)
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
			calculateJumps(i+2*directionI,j+2*directionJ,sequence+(j+2*directionJ)*(pow(10,depth+1))+(i+2*directionI)*(pow(10,depth+2)),depth+1, color,type ); //recursively check if we can extend the move 
		}
		else if(depth!=1)
		{
			jumpMoves.insert(sequence); //if no more jumps can be made we store the move
			forcedToMove=1;
		}
	}
}

//calculates all the possible moves
void board::calculatePossibleMoves(int color)
{
	int i,j;
	forcedToMove=0;
	std::set<int>::iterator it;
	std::set<int> *auxiliaryCheckerList;
	
	//depending on the color is the list it's going to check
	if(color==0)
		auxiliaryCheckerList=&whiteCheckers;//this should be right, have to check it later
	else
		auxiliaryCheckerList=&blackCheckers;
	
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
	
	if(color==0)
		auxiliaryCheckerList=&whiteKings;//this should be right, have to check it later
	else
		auxiliaryCheckerList=&blackKings;
	
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
}

std::set<int> board::getPossibleMoves(int color)
{
	calculatePossibleMoves(color);
	
	if(!jumpMoves.empty())
	{							
		return jumpMoves;			
	}
	
	return moves;
}

void board::clean()
{
	forcedToMove=0;
	moves.clear();
	jumpMoves.clear();
}

bool board::movePiece(int sequence, int color)//sequence is the sequence of numbers that represent the move, color=0 whiteMoves, color=1 blackMoves
{
	int initialPosition,finalPosition,enemyPosition;
	std::set<int> *auxiliaryCheckerList,*auxiliaryEnemyList;
	
	if(jumpMoves.empty()&&moves.count(sequence)>0)
	{
		initialPosition = (sequence%10)+((sequence/10)%10)*10;
		finalPosition = (sequence/100)%10+(sequence/1000)*10;
		
		if(boardMatrix[initialPosition/10][initialPosition%10]==(1+color))
		{
			if(color==0)
				auxiliaryCheckerList=&whiteCheckers;//this should be right, have to check it later
			else
				auxiliaryCheckerList=&blackCheckers;
			
			auxiliaryCheckerList->erase(initialPosition);
			auxiliaryCheckerList->insert(finalPosition);
			boardMatrix[initialPosition/10][initialPosition%10]=0;
			boardMatrix[finalPosition/10][finalPosition%10]=1+color;
		}
		else
		{
			if(color==0)
				auxiliaryCheckerList=&whiteKings;//this should be right, have to check it later
			else
				auxiliaryCheckerList=&blackKings;
			
			auxiliaryCheckerList->erase(initialPosition);
			auxiliaryCheckerList->insert(finalPosition);
			boardMatrix[initialPosition/10][initialPosition%10]=0;
			boardMatrix[finalPosition/10][finalPosition%10]=3+color;
		}
		
		clean();
		
		return true;
		
	}else if(jumpMoves.count(sequence)>0)
	{
		while(sequence/100>0)
		{
			initialPosition = (sequence%10)+((sequence/10)%10)*10;
			finalPosition = (sequence/100)%10+(sequence/1000)*10;
			enemyPosition = 10*((initialPosition/10+finalPosition/10)/2)+(initialPosition%10+finalPosition%10)/2;
			
			if(boardMatrix[initialPosition/10][initialPosition%10]==(1+color))
			{
				if(color==0)
					auxiliaryCheckerList=&whiteCheckers;//this should be right, have to check it later
				else
					auxiliaryCheckerList=&blackCheckers;
				
				
				auxiliaryCheckerList->erase(initialPosition);
				auxiliaryCheckerList->insert(finalPosition);
				boardMatrix[initialPosition/10][initialPosition%10]=0;
				boardMatrix[finalPosition/10][finalPosition%10]=1+color;
				
				if(boardMatrix[enemyPosition/10][enemyPosition%10]==2-color)
				{
					if(color==0)
						blackCheckers.erase(enemyPosition);
					else
						whiteCheckers.erase(enemyPosition);
				}
				else
				{
					if(color==0)
						blackKings.erase(enemyPosition);
					else
						whiteKings.erase(enemyPosition);
				}
				
				boardMatrix[enemyPosition/10][enemyPosition%10]=0;
			}
			else
			{
				if(color==0)
					auxiliaryCheckerList=&whiteKings;//this should be right, have to check it later
				else
					auxiliaryCheckerList=&blackKings;
				
				auxiliaryCheckerList->erase(initialPosition);
				auxiliaryCheckerList->insert(finalPosition);
				boardMatrix[initialPosition/10][initialPosition%10]=0;
				boardMatrix[finalPosition/10][finalPosition%10]=3+color;
				
				if(boardMatrix[enemyPosition/10][enemyPosition%10]==2-color)
				{
					if(color==0)
						blackCheckers.erase(enemyPosition);
					else
						whiteCheckers.erase(enemyPosition);
				}
				else
				{
					if(color==0)
						blackKings.erase(enemyPosition);
					else
						whiteKings.erase(enemyPosition);
				}
				
				boardMatrix[enemyPosition/10][enemyPosition%10]=0;
			}
			
			sequence=sequence/100;
		}
			
		clean();
		return true;
	}
	else
	{
		std::cout<<"You are not allowed to make that move!!"<<std::endl;
		return false;
	}
}