//
//  ComputerPlayer.cpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-19.
//  Copyright © 2018 Justin. All rights reserved.
//

#include "ComputerPlayer.hpp"

//MakeMove function returns a random # within the parameters of the number passed in
int MakeMove(int n){
    return rand() % n;
}
