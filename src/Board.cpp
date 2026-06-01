#include "Board.h"
#include <iostream>

Board::Board() {
    // Constructor mein hi hum texture ko load kar lenge
    // Path: "../images/chess_pieces.png" kyunki executable 'build' folder ke andar se chalti hai
    if (!piecesTexture.loadFromFile("../images/chess_pieces.png")) {
        // Safe fallback agar build folder se na chale toh direct check karein
        piecesTexture.loadFromFile("images/chess_pieces.png");
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            grid[i][j] = nullptr;
        }
    }
    initialize();
}

Board::~Board() {
    clear();
}

void Board::clear() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete grid[i][j];
            grid[i][j] = nullptr;
        }
    }
}

void Board::initialize() {
    clear();

    // Spawn Pawns
    for (int i = 0; i < 8; ++i) {
        grid[i][1] = new Pawn(PieceColor::Black);
        grid[i][6] = new Pawn(PieceColor::White);
    }

    // Spawn Rooks
    grid[0][0] = new Rook(PieceColor::Black); grid[7][0] = new Rook(PieceColor::Black);
    grid[0][7] = new Rook(PieceColor::White); grid[7][7] = new Rook(PieceColor::White);

    // Spawn Knights
    grid[1][0] = new Knight(PieceColor::Black); grid[6][0] = new Knight(PieceColor::Black);
    grid[1][7] = new Knight(PieceColor::White); grid[6][7] = new Knight(PieceColor::White);

    // Spawn Bishops
    grid[2][0] = new Bishop(PieceColor::Black); grid[5][0] = new Bishop(PieceColor::Black);
    grid[2][7] = new Bishop(PieceColor::White); grid[5][7] = new Bishop(PieceColor::White);

    // Spawn Queens and Kings
    grid[3][0] = new Queen(PieceColor::Black); grid[4][0] = new King(PieceColor::Black);
    grid[3][7] = new Queen(PieceColor::White); grid[4][7] = new King(PieceColor::White);

    // --- VISUAL INITIALIZATION ---
    // Saare pieces banne ke baad unhe unka standard visual asset aur initial screen position dete hain
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->initVisual(piecesTexture);
            }
        }
    }
    updateVisualPositions();
}

// Move hone ke baad sprites ki pixel positions screen par update karne ke liye function
void Board::updateVisualPositions() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (grid[i][j] != nullptr) {
                // Agar aapka board square size 80x80 pixel hai:
                grid[i][j]->setVisualPosition(i * 100.0f, j * 100.0f);
            }
        }
    }
}

bool Board::movePiece(int startX, int startY, int endX, int endY) {
    Piece* p = grid[startX][startY];
    if (!p) return false;

    if (p->isValidMove(startX, startY, endX, endY, (const Piece* (*)[8])grid)) {
        Piece* target = grid[endX][endY];
        
        // Agar target King hai, toh game over!
        if (target && target->getType() == PieceType::King) {
            isGameOver = true;
            winnerColor = p->getColor(); // Jo piece King ko maar raha hai, wo winner
            lastMove = {startX, startY, endX, endY}; // Yahan move save ho gayi
        }

        delete target;
        grid[endX][endY] = p;
        grid[startX][startY] = nullptr;
        
        updateVisualPositions();
        return true;
    }
    return false;
}