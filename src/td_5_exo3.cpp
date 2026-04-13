// Guard Patrol
#include <map>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_set>

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
            case Haut: y -= 1; break;
            case Bas: y += 1; break;
            case Droite: x += 1; break;
            case Gauche: x -= 1; break;
        }
        return *this;
    }
};

namespace std {
    template <>
    struct hash<Position> {
        std::size_t operator()(const Position& pos) const {
            std::size_t hx = std::hash<int>()(pos.x);
            std::size_t hy = std::hash<int>()(pos.y);
            return hx ^ (hy * 2654435761);
        }
    };
}
 
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

struct GuardState {
    Position pos;
    Direction dir;

    bool operator==(const GuardState& other) const {
        return pos == other.pos && dir == other.dir;
    }
};

namespace std {
    template <>
    struct hash<GuardState> {
        std::size_t operator()(const GuardState& state) const {
            std::size_t hp = std::hash<Position>()(state.pos);
            std::size_t hd = std::hash<int>()(static_cast<int>(state.dir));
            return hp ^ (hd * 2654435761);
        }
    };
}

struct Input_Structure {
    Position garde_position;
    Direction garde_direction;
    std::vector<Position> obstacles;
    int largeur;
    int hauteur;
};
 
bool est_obstacle(const Input_Structure& info, const Position& pos) {
    for (const Position& obs : info.obstacles) {
        if (obs == pos) return true;
    }
    return false;
}

bool est_sur_carte(const Input_Structure& info, const Position& pos) {
    return pos.x >= 0 && pos.x < info.largeur
        && pos.y >= 0 && pos.y < info.hauteur;
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
    Input_Structure info {Position(0, 0), Haut, {}, 0, 0};
    int y = 0;
 
    for (std::string line{}; std::getline(input_stream, line, '\n') and line != "";) {
        if (y == 0) info.largeur = (int)line.size();

        for (int x = 0; x < (int)line.size(); x++) {
            char c = line[x];
 
            if (c == '#') {
                info.obstacles.push_back(Position(x, y));
            }
            else if (c == '^' || c == 'v' || c == '>' || c == '<') {
                info.garde_position = Position(x, y);
                info.garde_direction = char_to_direction(c);
            }
        }
        y++;
    }

    info.hauteur = y;
    return info;
}

struct WalkResult {
    Position final_position;
    size_t steps_taken;
    std::unordered_set<Position> visited_positions;
};

WalkResult simulate(const Input_Structure& info) {
    Position  pos = info.garde_position;
    Direction dir = info.garde_direction;

    std::unordered_set<Position> visited;
    size_t steps = 0;

    visited.insert(pos);

    while (true) {
        Position next = pos + dir;

        if (!est_sur_carte(info, next)) {
            steps++;
            break;
        }

        if (est_obstacle(info, next)) {
            dir = turn_right(dir);
        }
        else {
            pos = next;
            steps++;
            visited.insert(pos);
        }
    }

    return WalkResult {pos, steps, visited};
}

bool creates_loop(const Input_Structure& info, const Position& obstacle_pos) {
    Position  pos = info.garde_position;
    Direction dir = info.garde_direction;

    std::unordered_set<GuardState> visited_states;

    while (true) {
        GuardState state {pos, dir};

        if (visited_states.count(state)) {
            return true;
        }
        visited_states.insert(state);

        Position next = pos + dir;

        if (!est_sur_carte(info, next)) {
            return false;
        }

        if (est_obstacle(info, next) || next == obstacle_pos) {
            dir = turn_right(dir);
        }
        else {
            pos = next;
        }
    }
}


int count_loop_positions(const Input_Structure& info) {
    WalkResult walk = simulate(info);

    int count = 0;

    for (const Position& candidate : walk.visited_positions) {
        if (candidate == info.garde_position) continue;

        if (creates_loop(info, candidate)) {
            count++;
        }
    }

    return count;
}

int main() {
    Position pos(2, 3);
    Direction dir = Haut;
    Position newPos = pos + dir;
    std::cout << newPos << "\n";
    newPos += dir;
    std::cout << newPos << "\n";
    std::cout << "turn_right(Haut) = " << turn_right(Haut) << "\n";

    //std::ifstream file("../src/map.txt");
    std::ifstream file("../src/input_guard_patrol.txt");
    if (!file) {
        std::cerr << "Erreur : impossible d'ouvrir la carte\n";
        return 1;
    }

    Input_Structure info = parse_input(file);
    std::cout << "Position du garde : " << info.garde_position << "\n";
    std::cout << "Nombre d'obstacles : " << info.obstacles.size() << "\n";
    std::cout << "Taille de la carte : " << info.largeur << "x" << info.hauteur << "\n\n";

    WalkResult result = simulate(info);
    std::cout << "Position finale : " << result.final_position << "\n";
    std::cout << "Pas effectues : " << result.steps_taken << "\n";
    std::cout << "Positions visitées : " << result.visited_positions.size() << "\n\n";

    int loops = count_loop_positions(info);
    std::cout << "Positions creant une boucle : " << loops << "\n";

    return 0;
}