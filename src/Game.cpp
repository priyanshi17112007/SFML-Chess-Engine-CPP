#include "Game.h"
#include <iostream>

Game::Game() : currentTurn(PieceColor::White), hasSelection(false), selectedX(0), selectedY(0) {
    initWindow();
    
    // Board ke coordinates ko hamare 100x100 grid window dimensions ke sath sync karna
    // Taaki pieces sahi pixel grids par dikhein
    board.updateVisualPositions();
}

void Game::initWindow() {
    window.create(sf::VideoMode(800, 800), "C++ SFML Chess Architecture Engine", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
}

void Game::run() {
    while (window.isOpen()) {
        if (!isGameOver) {
            handleInput();
        }
        update();
        render();
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int file = event.mouseButton.x / 100;
            int rank = event.mouseButton.y / 100;

            if (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
                if (!hasSelection) {
                    const Piece* p = board.getPiece(file, rank);
                    // Select piece matching active user validation parameters
                    if (p && p->getColor() == currentTurn) {
                        hasSelection = true;
                        selectedX = file;
                        selectedY = rank;
                    }
                } else {
                    // Try to execute transaction movement
                    // ... existing code ...
if (board.movePiece(selectedX, selectedY, file, rank)) {
    // Check karo kya King capture hua hai?
    // Agar captured piece King hai, toh game over!
    const Piece* captured = board.getPiece(file, rank); // Ye tab null hoga agar move legal tha
    // Lekin hume move hone se pehle check karna hoga
    
    // Asaan tarika: Check karo kya King abhi bhi board par hai?
    bool whiteKingExists = false;
    bool blackKingExists = false;
    for(int i=0; i<8; i++) {
        for(int j=0; j<8; j++) {
            const Piece* p = board.getPiece(i, j);
            if(p && p->getType() == PieceType::King) {
                if(p->getColor() == PieceColor::White) whiteKingExists = true;
                else blackKingExists = true;
            }
        }
    }

    if (!whiteKingExists || !blackKingExists) {
        isGameOver = true;
        std::cout << "GAME OVER! " << (whiteKingExists ? "White" : "Black") << " Wins!" << std::endl;
    }

    currentTurn = (currentTurn == PieceColor::White) ? PieceColor::Black : PieceColor::White;
}
// ... rest of the code ...
                    hasSelection = false;
                }
            }
        }
    }
}

void Game::update() {
    // Dynamic logic update point (e.g., adding win/loss check evaluations)
}

void Game::drawBoard() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            sf::RectangleShape cell(sf::Vector2f(100.f, 100.f));
            cell.setPosition(x * 100.f, y * 100.f);

            // Establish standard wood texture styling palette array setup
            if ((x + y) % 2 == 0) {
                cell.setFillColor(sf::Color(240, 217, 181)); // Clean Light Sand Wood Tone
            } else {
                cell.setFillColor(sf::Color(181, 136, 99));  // Clean Dark Mahogany Wood Tone
            }

            // Visually flag selected asset context tracking (UNCHANGED)
            if (hasSelection && x == selectedX && y == selectedY) {
                cell.setFillColor(sf::Color(130, 151, 105)); // Subtle muted selection green color
            }

            window.draw(cell);
        }
    }
}

// --- PURANI GEOMETRIC FUNCTION KO HATAKAR NAYA CLEAN PIECE RENDERING KAAM ---
void Game::drawPieces() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            // Hum direct Piece* pointer grid se piece uthayenge
            // Kyunki Board data ke paas constant check access functions pehle se hain
            const Piece* p = board.getPiece(x, y);
            if (p) {
                // Humne jo Piece.h me naya safe draw() virtual wrapper banaya tha, use yahan execute karenge
                // Yeh function internally real sf::Sprite ko draw karega bina logic ko chhede
                p->draw(window);
            }
        }
    }
}

void Game::render() {
    window.clear();
    drawBoard();
    drawPieces(); // Naye sprites yahan se screen par aayenge
    if (isGameOver) {
        // 1. Dark Overlay (Game rukne ka visual)
        sf::RectangleShape overlay(sf::Vector2f(800.f, 800.f));
        overlay.setFillColor(sf::Color(0, 0, 0, 180));
        window.draw(overlay);

        // 2. Winner King Icon (Center mein)
        sf::Sprite winnerKing = getKingSprite(board.getWinner());
        winnerKing.setScale(4.f, 4.f);
        winnerKing.setPosition(360.f, 250.f);
        window.draw(winnerKing);

        // 3. Last Move Icon (Winner ke neeche)
        // Yahan aap 'lastMove' ke startX/Y aur endX/Y ka use karke 
        // us piece ka icon draw kar sakte ho jisne capture kiya
        sf::Sprite winningPiece = getPieceSprite(board.lastMove.startX, board.lastMove.startY);
        winningPiece.setPosition(380.f, 400.f);
        window.draw(winningPiece);
    }
    
    
    window.display();
}
sf::Sprite Game::getKingSprite(PieceColor color) {
    // Yahan wahi logic likho jo aap pieces load karne ke liye use kar rahe ho
    // Jaise: return (color == PieceColor::White) ? whiteKingSprite : blackKingSprite;
    sf::Sprite s; 
    // Apne sprite/texture ka reference yahan set karo
    s.setTexture(kingTexture); 
    
    // Yahan check karo ki texture loaded hai ya nahi
    if (kingTexture.getSize().x == 0) {
        std::cout << "DEBUG: Texture load nahi hua!" << std::endl;
    }
    
    return s;
}

sf::Sprite Game::getPieceSprite(int x, int y) {
    // Yahan us piece ka sprite return karo jo (x, y) position par hai
    sf::Sprite s;
    // ... logic ...
    return s;
}