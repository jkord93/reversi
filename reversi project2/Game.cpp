//
//  Game.cpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-16.
//  Copyright © 2018 Justin. All rights reserved.
//

#include "Game.hpp"
#include "Board.hpp"
#include "HumanPlayer.hpp"
#include "ComputerPlayer.hpp"

// char c used to get players choice for Human or CPU
char c;
//Strings to store up to 2 players names
std::string name1, name2;
//bool p1 and p2 to store player type (false for Human, true for CPU)
bool p1 = false;
bool p2 = false;

//CreateNewGame method creates a game of Reversi by setting the board and selecting the players.
reversi CreateNewGame()
{
    reversi Reversi = {};
    
    Reversi.Board = CreateNewBoard();
    selectPlayers();
    Reversi.LightPlayer = CreateNewPlayer(name1, COLOR_LIGHT, p1);
    Reversi.DarkPlayer = CreateNewPlayer(name2, COLOR_DARK, p2);
    
    return Reversi;
}

//CreateNewPlayer method creates a new Player and stores the name, color and type of player
player CreateNewPlayer(std::string Name, piece_color Color, bool AI)
{
    player Player = {};
    
    Player.Name = Name;
    Player.Color = Color;
    Player.Pieces = 0;
    Player.OutOfMoves = false;
    Player.AIPlayer = AI;
    
    return Player;
}

//selectPlayers method asks for a type and name of player used in CreateNewPlayer method
void selectPlayers(){
    std::cout<<"Player 1 CPU or HUMAN?" << std::endl;
    std::cout<<"1. Human" << std::endl;
    std::cout<<"2. CPU" << std::endl;
    std::cin>>c;
    if(c=='1'){
        std::cout<<"Enter name"<<std::endl;
        std::cin>>name1;
        p1=false;
    }
    else if(c=='2'){
        name1="AI";
        p1=true;
    }
    std::cout<<"Player 2 CPU or HUMAN?" << std::endl;
    std::cout<<"1. Human" << std::endl;
    std::cout<<"2. CPU" << std::endl;
    std::cin>>c;
    if(c=='1'){
        std::cout<<"Enter name"<<std::endl;
        std::cin>>name2;
        p2=false;
    }
    else if(c=='2'){
        name2="AI";
        p2=true;
    }
}

//returns the pointer to the player whose move it is.
player* nextPlayer(reversi *r, piece_color pc){
    return getPlayer(r, pc);
}

//creates a new game, displays the board and calls makeMove() of the player whose move it is.
void play(){
    reversi Reversi = CreateNewGame();
    srand(time(NULL));
    
    piece_color PlayerTurn = COLOR_DARK;
    while(Reversi.Board.EmptyPieces != 0)
    {
        //if we end up out of moves, break and display the board
        
        if(Reversi.LightPlayer.OutOfMoves && Reversi.DarkPlayer.OutOfMoves)
            break;
        
        display(&Reversi.Board);
        
        //get active player whos turn it is
        player *ActivePlayer = getPlayer(&Reversi, PlayerTurn);
        std::vector<position> Moves = genMoves(&Reversi.Board, ActivePlayer);
        //if we have legal moves availlable to us then proceed
        if(!Moves.empty())
        {
            ActivePlayer->OutOfMoves = false;
            printf("%s, Legal Moves\n", PlayerTurn == COLOR_LIGHT ? "Light" : "Dark");
            for(int Move = 0; Move < Moves.size(); ++Move)
                printf("%d:    Move - (%d,%c)\n", Move, Moves[Move].Row+1, Moves[Move].Col+'a');
            
            if(ActivePlayer->AIPlayer)
            {
                /* TODO: Replace with generated move */
                int Choice = MakeMove(Moves.size());
                makeMove(&Reversi.Board, &Moves[Choice], ActivePlayer);
                sleep(1);
                printf("Selected move: %d\n", Choice);
            }
            else
            {
                int Choice = -1;
                do{
                    Choice = makemove();
                } while(Choice < 0 || Choice >= Moves.size());
                makeMove(&Reversi.Board, &Moves[Choice], ActivePlayer);
            }
        }
        else
        {
            printf("Player %s are out of legal moves\n", ActivePlayer->Name.c_str());
            ActivePlayer->OutOfMoves = true;
        }
        
        PlayerTurn = PlayerTurn == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    }
    
    //Display the final board, count each players pieces and anounce the winner!
    
    display(&Reversi.Board);
    
    CountPiecesOfPlayer(&Reversi.Board, &Reversi.LightPlayer);
    CountPiecesOfPlayer(&Reversi.Board, &Reversi.DarkPlayer);
    //player *Winner = getWinner(&Othello);
    announceWinner(getWinner(&Reversi));
}

//announceWinner function displays the winner if there is no winner it displays Draw
void announceWinner(player *Winner){
    if(!Winner)
        std::cout << "Draw!" << std::endl;
    else
        std::cout << Winner->Name << " won with " << std::to_string(Winner->Pieces) << " pieces!" << std::endl;
}
