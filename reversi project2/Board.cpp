//
//  Board.cpp
//  project2
// @author Justin Kord
// Student Number 0360764
//  Created by Justin on 2018-11-16.
//  Copyright © 2018 Justin. All rights reserved.
//

#include "Board.hpp"
#include <time.h>

//creates a new board and sets the board spaces to empty
board CreateNewBoard()
{
    board Board = {};
    for(int col = 0; col < BOARD_SIZE; ++col)
    {
        for(int row = 0; row < BOARD_SIZE; ++row)
            Board.State[row][col] = COLOR_EMPTY;
    }
    
    Board.State[3][3] = COLOR_LIGHT;
    Board.State[3][4] = COLOR_DARK;
    Board.State[4][3] = COLOR_DARK;
    Board.State[4][4] = COLOR_LIGHT;
    Board.EmptyPieces = 60;
    
    return Board;
}
//returns the players whos turn it is
player *getPlayer(reversi *Reversi, piece_color PlayerTurn)
{
    return PlayerTurn == COLOR_DARK ? &Reversi->DarkPlayer : &Reversi->LightPlayer;
}
//counts the # of pieces the player has
void CountPiecesOfPlayer(board *Board, player *Player)
{
    Player->Pieces = 0;
    for(int Col = 0; Col < BOARD_SIZE; ++Col)
    {
        for(int Row = 0; Row < BOARD_SIZE; ++Row)
        {
            if(Board->State[Row][Col] == Player->Color)
                ++Player->Pieces;
        }
    }
}

// finds the Winner by finding the player with more pieces
player *getWinner(reversi *Reversi)
{
    if(Reversi->LightPlayer.Pieces > Reversi->DarkPlayer.Pieces)
        return &Reversi->LightPlayer;
    else if(Reversi->LightPlayer.Pieces < Reversi->DarkPlayer.Pieces)
        return &Reversi->DarkPlayer;
    else
        return NULL;
    
}

//returns a vector list of legal moves by calling isLegal to find legal moves to add to the vector
std::vector<position> genMoves(board *Board, player *Player)
{
    std::vector<position> Moves;
    for(int Col = 0; Col < BOARD_SIZE; ++Col)
    {
        for(int Row = 0; Row < BOARD_SIZE; ++Row)
        {
            position Pos = { Row, Col };
            if(isLegal(Board, &Pos, Player))
                Moves.push_back(Pos);
        }
    }
    
    return Moves;
}

//returns the count of moves availlable to the player by calling genMoves and counting the moves returned
int numMoves(board *B, player *P){
    int count = 0;
    std::vector<position> numMoves = genMoves(B, P);
    for(int i =0; i<numMoves.size(); i++){
        count++;
    }
    return count;
}

//uses checks to find spaces around the player that the player can legally move to
bool isLegal(board *Board, position *Pos, player *Player)
{
    if((Pos->Row >= BOARD_SIZE || Pos->Row < 0) ||
       (Pos->Col >= BOARD_SIZE || Pos->Col < 0) ||
       (Board->State[Pos->Row][Pos->Col] != COLOR_EMPTY))
        return false;
    
    bool Result = false;
    
    if(CheckNorth(Board, Pos, Player))
        Result = true;
    if(CheckEast(Board, Pos, Player))
        Result = true;
    if(CheckSouth(Board, Pos, Player))
        Result = true;
    if(CheckWest(Board, Pos, Player))
        Result = true;
    if(CheckNorthEast(Board, Pos, Player))
        Result = true;
    if(CheckNorthWest(Board, Pos, Player))
        Result = true;
    if(CheckSouthEast(Board, Pos, Player))
        Result = true;
    if(CheckSouthWest(Board, Pos, Player))
        Result = true;
    
    return Result;
}

// makes move to the pos specified by the function parameters
void makeMove(board *Board, position *Pos, player *Player)
{
    Board->State[Pos->Row][Pos->Col] = Player->Color;
    for(int Index = 0; Index < Pos->Captured.size(); ++Index)
    {
        position Piece = Pos->Captured[Index];
        Board->State[Piece.Row][Piece.Col] = Player->Color;
    }
    
    Pos->Captured.clear();
    --Board->EmptyPieces;
}

//Displays the board in a 8 by 8 square board game
void display(board *Board)
{
    printf("\n");
    printf("  ");
    for(char Col = 'a'; Col <= 'h'; ++Col)
        printf("%c ", Col);
    
    printf("\n");
    for(int Row = 0; Row < BOARD_SIZE; ++Row)
    {
        printf("%d ", Row+1);
        for(int Col = 0; Col < BOARD_SIZE; ++Col)
        {
            char Output = ' ';
            if(Board->State[Row][Col] == COLOR_LIGHT)
                Output = 'L';
            else if(Board->State[Row][Col] == COLOR_DARK)
                Output = 'D';
            
            printf("%c ", Output);
        }
        printf("\n");
    }
    printf("\n");
}

//creates a new empty board and resets the board to the empty board
void reset(board *Board){
    board Board2 = {};
    for(int col = 0; col < BOARD_SIZE; ++col)
    {
        for(int row = 0; row < BOARD_SIZE; ++row)
            Board2.State[row][col] = COLOR_EMPTY;
    }
    
    Board2.State[3][3] = COLOR_LIGHT;
    Board2.State[3][4] = COLOR_DARK;
    Board2.State[4][3] = COLOR_DARK;
    Board2.State[4][4] = COLOR_LIGHT;
    Board2.EmptyPieces = 60;
    
    Board = &Board2;
    
}

//check if it is legal for the player to make the move North
bool CheckNorth(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Row - 2 < 0)
        return false;
    
    std::vector<position> Captured;
    for(int Row = Pos->Row - 1; Row >= 0; --Row)
    {
        position CheckPosition = { Row, Pos->Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move South
bool CheckSouth(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Row + 2 >= BOARD_SIZE)
        return false;
    
    std::vector<position> Captured;
    for(int Row = Pos->Row + 1; Row < BOARD_SIZE; ++Row)
    {
        position CheckPosition = { Row, Pos->Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move East
bool CheckEast(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Col + 2 >= BOARD_SIZE)
        return false;
    
    std::vector<position> Captured;
    for(int Col = Pos->Col + 1; Col < BOARD_SIZE; ++Col)
    {
        position CheckPosition = { Pos->Row, Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move West
bool CheckWest(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Col - 2 < 0)
        return false;
    
    std::vector<position> Captured;
    for(int Col = Pos->Col - 1; Col >= 0; --Col)
    {
        position CheckPosition = { Pos->Row, Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move NorthEast
bool CheckNorthEast(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Row - 2 < 0 || Pos->Col + 2 >= BOARD_SIZE)
        return false;
    
    std::vector<position> Captured;
    for(int Row = Pos->Row - 1, Col = Pos->Col + 1;
        Row >= 0 && Col < BOARD_SIZE;
        --Row, ++Col)
    {
        position CheckPosition = { Row, Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move NorthWest
bool CheckNorthWest(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Row - 2 < 0 || Pos->Col - 2 < 0)
        return false;
    
    std::vector<position> Captured;
    for(int Row = Pos->Row - 1, Col = Pos->Col - 1;
        Row >= 0 && Col >= 0;
        --Row, --Col)
    {
        position CheckPosition = { Row, Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move SouthEast
bool CheckSouthEast(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Row + 2 >= BOARD_SIZE || Pos->Col + 2 >= BOARD_SIZE)
        return false;
    
    std::vector<position> Captured;
    for(int Row = Pos->Row + 1, Col = Pos->Col + 1;
        Row < BOARD_SIZE && Col < BOARD_SIZE;
        ++Row, ++Col)
    {
        position CheckPosition = { Row, Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}

//check if it is legal for the player to make the move SouthWest
bool CheckSouthWest(board *Board, position *Pos, player *Player)
{
    piece_color OpponentColor = Player->Color == COLOR_LIGHT ? COLOR_DARK : COLOR_LIGHT;
    
    int PlayerCount = 0;
    int OpponentCount = 0;
    
    if(Pos->Row + 2 >= BOARD_SIZE || Pos->Col - 2 < 0)
        return false;
    
    std::vector<position> Captured;
    for(int Row = Pos->Row + 1, Col = Pos->Col - 1;
        Row < BOARD_SIZE && Col >= 0;
        ++Row, --Col)
    {
        position CheckPosition = { Row, Col };
        piece_color Piece = Board->State[CheckPosition.Row][CheckPosition.Col];
        if(Piece == OpponentColor)
        {
            Captured.push_back(CheckPosition);
            ++OpponentCount;
        }
        else if(Piece == Player->Color)
        {
            ++PlayerCount;
            break;
        }
        else if(Piece == COLOR_EMPTY)
        {
            Captured.clear();
            break;
        }
    }
    
    bool Result = OpponentCount > 0 && PlayerCount == 1;
    if(Result)
    {
        for(int Index = 0; Index < Captured.size(); ++Index)
            Pos->Captured.push_back(Captured[Index]);
    }
    
    return Result;
}
