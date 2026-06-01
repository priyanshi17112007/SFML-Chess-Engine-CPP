#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board {
private:
    Piece* grid[8][8];
    sf::Texture piecesTexture; // <--- Texture store karne ke liye member variable
    bool isGameOver = false;
    PieceColor winnerColor;
public:
    Board();
    ~Board();

    void initialize();
    void clear();
    
    const Piece* getPiece(int x, int y) const { return grid[x][y]; }
    
    // Core game state mutator execution
    bool movePiece(int startX, int startY, int endX, int endY);
    
    const Piece* (*getRawGrid() const)[8] { return (const Piece* (*)[8])grid; }

    // --- Ek extra helper function visuals update karne ke liye ---
    void updateVisualPositions();
    bool getIsGameOver() const { return isGameOver; }
    PieceColor getWinner() const { return winnerColor; }
    struct Move { int startX, startY, endX, endY; };
    Move lastMove; // Ye move save rakhegi

};

#endif