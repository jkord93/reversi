//
//  HumanPlayer.cpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-19.
//  Copyright © 2018 Justin. All rights reserved.
//

#include "HumanPlayer.hpp"

//player is asked to select a move and the move is returned and used to play.
int makemove(){
    int mover;
    printf("Select a move: ");
    std::cin >> mover;
    return mover;
}
