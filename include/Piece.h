#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <cmath>

enum class PieceType { Pawn, Rook, Knight, Bishop, Queen, King };
enum class PieceColor { White, Black };

class Piece {
protected:
    PieceType type;
    PieceColor color;
    sf::Sprite sprite; // <--- Geometrical shape ki jagah real image ke liye sprite

public:
    Piece(PieceType t, PieceColor c) : type(t), color(c) {}
    virtual ~Piece() = default;

    PieceType getType() const { return type; }
    PieceColor getColor() const { return color; }

    // --- SPRITE ASSIGNMENT & DRAW FUNCTIONS (Sirf visuals ke liye extra joda hai) ---
    void initVisual(sf::Texture& texture) {
        sprite.setTexture(texture);

        // Sprite sheet (1280x427) ke hisab se index aur dimensions nikalna
        int typeIndex = 0;
        switch (type) {
            case PieceType::King:   typeIndex = 0; break;
            case PieceType::Queen:  typeIndex = 1; break;
            case PieceType::Bishop: typeIndex = 2; break;
            case PieceType::Knight: typeIndex = 3; break;
            case PieceType::Rook:   typeIndex = 4; break;
            case PieceType::Pawn:   typeIndex = 5; break;
        }
        int colorIndex = (color == PieceColor::White) ? 0 : 1;

        int sourceWidth = texture.getSize().x / 6;  // 6 pieces ek row me
        int sourceHeight = texture.getSize().y / 2; // 2 rows (White aur Black)

        // Exact piece ko rect cut karke assign karna
        sprite.setTextureRect(sf::IntRect(typeIndex * sourceWidth, colorIndex * sourceHeight, sourceWidth, sourceHeight));
        
        // Scale down karna taaki board ke squares (~80x80) me perfectly fit ho sake
        float scaleX = 100.0f / sourceWidth;
        float scaleY = 100.0f / sourceHeight;
        sprite.setScale(scaleX, scaleY);
    }

    void setVisualPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
    // ---------------------------------------------------------------------------------

    // Polymorphic method overridden by specific pieces to validate trajectory rules (UNCHANGED)
    virtual bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const = 0;
};

// Derived Piece Implementations (Aapki saari puraani functions ekdum same hain)
class Pawn : public Piece {
public:
    Pawn(PieceColor c) : Piece(PieceType::Pawn, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const override;
};

class Rook : public Piece {
public:
    Rook(PieceColor c) : Piece(PieceType::Rook, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const override;
};

class Knight : public Piece {
public:
    Knight(PieceColor c) : Piece(PieceType::Knight, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const override;
};

class Bishop : public Piece {
public:
    Bishop(PieceColor c) : Piece(PieceType::Bishop, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const override;
};

class Queen : public Piece {
public:
    Queen(PieceColor c) : Piece(PieceType::Queen, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const override;
};

class King : public Piece {
public:
    King(PieceColor c) : Piece(PieceType::King, c) {}
    bool isValidMove(int startX, int startY, int endX, int endY, const Piece* board[8][8]) const override;
};

#endif