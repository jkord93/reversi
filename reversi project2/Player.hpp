//
//  Player.hpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-16.
//  Copyright © 2018 Justin. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <unistd.h>


#define BOARD_SIZE 8
//enum to store the color of piece each player is using to play the game
enum piece_color
{
    COLOR_LIGHT,
    COLOR_DARK,
    COLOR_EMPTY
};

// struct to store the position of the player and positions on the board
struct position
{
    int Row;
    int Col;
    
    std::vector<position> Captured;
};

//struct to initialize the board and count free space on the board
struct board
{
    piece_color State[BOARD_SIZE][BOARD_SIZE];
    int EmptyPieces;
};

// struct for the functionality of the player which constructs the player and stores the players name, color, player type and defines the getPiece method which returns the players piece color
struct player
{
    std::string Name;
    piece_color Color;
    bool OutOfMoves;
    int Pieces;
    
    bool AIPlayer;
    
    player(){}
    player(const std::string s,piece_color c){
        Name = s;
        Color = c;
    }
    
    piece_color getPiece() const{
        return Color;
    }
};

// reversi struct used to play the game by creating a board and 2 players.
struct reversi
{
    board Board;
    player LightPlayer;
    player DarkPlayer;
};


#endif /* Player_hpp */
