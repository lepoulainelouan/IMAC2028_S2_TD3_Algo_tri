//GUard patrol
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

enum Direction {
    Haut,
    Bas,
    Droite,
    Gauche
};

struct Position {
    int x;
    int y;

    Position(int x, int y) :x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    Position& operator+=(const Position& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position& operator+=(Direction dir) {
        switch (dir) {
            case Haut:    y -= 1; break;
            case Bas:     y += 1; break;
            case Droite:  x += 1; break;
            case Gauche:  x -= 1; break;
        }
        return *this;
    }
};

Position operator+(Position lhs, const Position& rhs) {
    lhs += rhs;
    return lhs;
}

Position operator+(Position pos, Direction dir) {
    pos += dir;
    return pos;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}

Direction turn_right(Direction dir) {
    switch (dir) {
        case Haut:
        case Droite:
        case Bas:
        case Gauche:
        
        return Haut;
        return Droite;
        return Bas;
        return Gauche;
    }
    return dir;
}

int main() {
    Position pos(2, 3);
    Direction dir = Haut;
    Position newPos { pos + dir }; 
    std::cout << newPos << "\n";

    newPos += dir;
    std::cout << newPos << "\n";
    return 0;
}