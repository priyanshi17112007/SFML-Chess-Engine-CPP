#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class Game {
private:
    sf::RenderWindow window;
    Board board;
    PieceColor currentTurn;
    
    bool hasSelection;
    int selectedX, selectedY;

    // Internal initialization routines
    void initWindow();
    void handleInput();
    void update();
    void render();
    
    // Visual generation procedures
    void drawBoard();
    void drawPieces();
    void drawPieceVisual(PieceType type, PieceColor color, float centerX, float centerY);
    bool isGameOver = false; 
    private:
    // ... aapke purane variables ...
    sf::Sprite getKingSprite(PieceColor color);
    sf::Sprite getPieceSprite(int x, int y);
public:
    Game();
    void run();
};

#endif