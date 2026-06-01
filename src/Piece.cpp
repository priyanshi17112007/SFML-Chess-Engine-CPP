#include "Piece.h"

// Helper method to verify clear straight lines for path analysis
bool checkStraightPath(int startX, int startY, int endX, int endY, const Piece* board[8][8]) {
    int dx = (endX == startX) ? 0 : ((endX > startX) ? 1 : -1);
    int dy = (endY == startY) ? 0 : ((endY > startY) ? 1 : -1);
    
    int x = startX + dx;
    int y = startY + dy;
    while (x != endX || y != endY) {
        if (board[x][y] != nullptr) return false; // Path obstructed
        x += dx;
        y += dy;
    }
    return true;
}

bool Pawn::isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const {
    int direction = (color == PieceColor::White) ? -1 : 1; // White moves up (negative Y)
    int startRow = (color == PieceColor::White) ? 6 : 1;

    // Standard single-step forward forward vertical pathing
    if (startX == endX && endY == startY + direction) {
        return (board[endX][endY] == nullptr);
    }
    // Initial optional double-step configuration
    if (startX == endX && startY == startRow && endY == startY + 2 * direction) {
        return (board[startX][startY + direction] == nullptr && board[endX][endY] == nullptr);
    }
    // Diagonal Capture validation verification logic
    if (std::abs(endX - startX) == 1 && endY == startY + direction) {
        return (board[endX][endY] != nullptr && board[endX][endY]->getColor() != color);
    }
    return false;
}

bool Rook::isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const {
    if (startX != endX && startY != endY) return false;
    return checkStraightPath(startX, startY, endX, endY, board);
}

bool Knight::isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const {
    int dx = std::abs(endX - startX);
    int dy = std::abs(endY - startY);
    return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
}

bool Bishop::isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const {
    if (std::abs(endX - startX) != std::abs(endY - startY)) return false;
    return checkStraightPath(startX, startY, endX, endY, board);
}

bool Queen::isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const {
    if (startX != endX && startY != endY && std::abs(endX - startX) != std::abs(endY - startY)) return false;
    return checkStraightPath(startX, startY, endX, endY, board);
}

bool King::isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const {
    return (std::abs(endX - startX) <= 1 && std::abs(endY - startY) <= 1);
}