//
//  Game.hpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-16.
//  Copyright © 2018 Justin. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Player.hpp"

// Create new game method used as constructor to create the game
reversi CreateNewGame();
// Creates new player with Name, Color and Type
player CreateNewPlayer(std::string Name, piece_color Color, bool AI);
//Prompts the user for each of the two players for the type (human/computer) of the player. For a human player the function also asks for the player's name.
void selectPlayers();
//The function returns the pointer to the player whose move it is.
player* nextPlayer();
//the function displays the boards and invokes the makeMove() member function of the player whose move it is
void play();
//Announces the end of the game and the name of the winner (or a tie).
void announceWinner(player *Winner);
#endif /* Game_hpp */
