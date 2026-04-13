// Guard Patrol
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

enum Direction {
    Haut,
    Bas,
    Droite,
    Gauche
};
 
struct Position {
    int x;
    int y;
 
    Position(int x, int y) : x(x), y(y) {}
 
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
            case Haut:   y -= 1; break;
            case Bas:    y += 1; break;
            case Droite: x += 1; break;
            case Gauche: x -= 1; break;
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
        return Droite;
        case Droite:
        return Bas;
        case Bas:
        return Gauche;
        case Gauche:
        return Haut;
    }
    return dir;
}
 
struct Input_Structure {
    Position garde_position;
    Direction garde_direction;
    std::vector<Position> obstacles;
};
 
bool est_obstacle(const Input_Structure& info, const Position& pos) {
    for (const Position& obs : info.obstacles) {
        if (obs == pos) return true;
    }
    return false;
}
 
Direction char_to_direction(char c) {
    switch (c) {
        case '^': return Haut;
        case 'v': return Bas;
        case '>': return Droite;
        case '<': return Gauche;
    }
    return Haut;
}
 
Input_Structure parse_input(std::istream& input_stream) {
    Input_Structure info {Position(0, 0), Haut, {}};
    int y = 0;
 
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != "";) {
        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];
 
            if (c == '#') {
                info.obstacles.push_back(Position(x, y));
            }
            else if (c == '^' || c == 'v' || c == '>' || c == '<') {
                info.garde_position  = Position(x, y);
                info.garde_direction = char_to_direction(c);
            }
        }
        y++;
    }
 
    return info;
}
 
int main() {
    Position pos(2, 3);
    Direction dir = Haut;
    Position newPos = pos + dir;
    std::cout << newPos << "\n";
    newPos += dir;
    std::cout << newPos << "\n";

    std::cout << "turn_right(Haut) = " << turn_right(Haut) << "\n";
    std::ifstream file("../src/map.txt");
    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir map.txt\n";
        return 1;
    }
     Input_Structure info = parse_input(file);
 
    std::cout << "Position du garde  : " << info.garde_position << "\n";
    std::cout << "Nombre d'obstacles : " << info.obstacles.size() << "\n";
 
    return 0;
}