//
//  Board.hpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-16.
//  Copyright © 2018 Justin. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include "Player.hpp"

//Constructor creates a new board
board CreateNewBoard();
//Returns the color of the Player whose turn it is.
player *getPlayer(reversi *Reversi, piece_color PlayerTurn);
//Counts # of pieces player has
void CountPiecesOfPlayer(board *Board, player *Player);
//Returns the winning side.
player *getWinner(reversi *Reversi);
//Generates a list of the moves that are possible in the current position
std::vector<position> genMoves(board *Board, player *Player);
//Checks whether it is legal to place the given Piece on the square named by the second parameter.
bool isLegal(board *Board, position *Pos, player *Player);
//Executes the move indicated by the function parameters
void makeMove(board *Board, position *Pos, player *Player);
//Displays the board.
void display(board *Board);
//Erases all pieces from the board.
void reset(board *Board);
//Returns the number of valid moves.
int numMoves(board *B, player *P);
//Checks board for legal moves used in isLegal
bool CheckNorth(board *Board, position *Pos, player *Player);
bool CheckSouth(board *Board, position *Pos, player *Player);
bool CheckEast(board *Board, position *Pos, player *Player);
bool CheckWest(board *Board, position *Pos, player *Player);
bool CheckNorthWest(board *Board, position *Pos, player *Player);
bool CheckNorthEast(board *Board, position *Pos, player *Player);
bool CheckSouthWest(board *Board, position *Pos, player *Player);
bool CheckSouthEast(board *Board, position *Pos, player *Player);

#endif /* Board_hpp */
