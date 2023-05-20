#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

class Labyrinthe : public Graphe {
private:
    static const std::vector<std::string> coins;
    int w;
    int h;
    std::vector<std::vector<char>> repr;
    std::vector<std::pair<int, int>> ouvertures;

public:
    Labyrinthe(int w = 0, int h = 0) : Graphe(false), w(w), h(h) {
        reset();
        repr = std::vector<std::vector<char>>(2 * h + 1, std::vector<char>(2 * w + 1, '*'));
        effacer_repr();
    }

    void reset() {
        A.clear();
        for (int l = 0; l < h; l++) {
            for (int c = 0; c < w; c++) {
                ajouterSommet(std::make_pair(l, c));
            }
        }
    }

    std::string toString() {
        construire_repr();
        std::string str;
        for (const auto& row : repr) {
            str += std::string(row.begin(), row.end()) + "\n";
        }
        return str;
    }

    void construire_repr() {
        for (int c = 0; c < w; c++) {
            repr[0][2 * c + 1] = coins[5][0];
        }
        for (int l = 0; l < h; l++) {
            repr[2 * l + 1][0] = coins[10][0];
            for (int c = 0; c < w; c++) {
                if (l + 1 < h && arete(std::make_pair(l, c), std::make_pair(l + 1, c))) {
                    repr[2 * l + 2][2 * c + 1] = coins[0][0];
                } else {
                    repr[2 * l + 2][2 * c + 1] = coins[5][0];
                }

                if (c + 1 < w && arete(std::make_pair(l, c), std::make_pair(l, c + 1))) {
                    repr[2 * l + 1][2 * c + 2] = coins[0][0];
                } else {
                    repr[2 * l + 1][2 * c + 2] = coins[10][0];
                }
            }
        }

        for (int l = 0; l < repr.size(); l += 2) {
            for (int c = 0; c < repr[0].size(); c += 2) {
                int code = 1 * (c + 1 < repr[0].size() && repr[l][c + 1] != ' ');
                code += 2 * (l != 0 && repr[l - 1][c] != ' ');
                code += 4 * (c != 0 && repr[l][c - 1] != ' ');
                code += 8 * (l + 1 < repr.size() && repr[l + 1][c] != ' ');
                repr[l][c] = coins[code][0];
            }
        }

        for (const auto& o : ouvertures) {
            int l = o.first;
            int c = o.second;
            if (c == 0) {
                repr[2 * l + 1][2 * c] = ' ';
            } else if (c == w - 1) {
                repr[2 * l + 1][2 * c + 2] = ' ';
            } else if (l == 0) {
                repr[2 * l][2 * c + 1] = ' ';
            } else if (l == h - 1) {
                repr[2 * l + 2][2 * c + 1] = ' ';
            }
        }
    }

    void effacer_repr() {
        for (int l = 0; l < h; l++) {
            for (int c = 0; c < w; c++) {
                repr[2 * l + 1][2 * c + 1] = ' ';
            }
        }
    }

    static const std::vector<std::string> coins;
};

const std::vector<std::string> Labyrinthe::coins = {
    " ", "═", "║", "╚", "═", "═", "╝", "╩", "║", "╔", "║", "╠", "╗", "╦", "╣", "╬"
};

int main() {
    Labyrinthe labyrinthe(5, 5);
    labyrinthe.ajouterArete(std::make_pair(0, 0), std::make_pair(0, 1));
    labyrinthe.ajouterArete(std::make_pair(0, 0), std::make_pair(1, 0));
    labyrinthe.ajouterArete(std::make_pair(1, 0), std::make_pair(1, 1));
    labyrinthe.ajouterArete(std::make_pair(1, 1), std::make_pair(2, 1));
    labyrinthe.ajouterArete(std::make_pair(2, 1), std::make_pair(2, 2));
    labyrinthe.ajouterArete(std::make_pair(2, 2), std::make_pair(3, 2));
    labyrinthe.ajouterArete(std::make_pair(3, 2), std::make_pair(3, 3));
    labyrinthe.ajouterArete(std::make_pair(3, 3), std::make_pair(4, 3));
    labyrinthe.ajouterArete(std::make_pair(4, 3), std::make_pair(4, 4));
    labyrinthe.ajouterArete(std::make_pair(0, 1), std::make_pair(0, 2));
    labyrinthe.ajouterArete(std::make_pair(0, 2), std::make_pair(1, 2));
    labyrinthe.ajouterArete(std::make_pair(1, 2), std::make_pair(1, 3));
    labyrinthe.ajouterArete(std::make_pair(1, 3), std::make_pair(2, 3));
    labyrinthe.ajouterArete(std::make_pair(2, 3), std::make_pair(2, 4));
    labyrinthe.ajouterArete(std::make_pair(0, 1), std::make_pair(1, 1));
    labyrinthe.ajouterArete(std::make_pair(0, 2), std::make_pair(0, 3));
    labyrinthe.ajouterArete(std::make_pair(0, 3), std::make_pair(1, 3));
    labyrinthe.ajouterArete(std::make_pair(0, 3), std::make_pair(0, 4));
    std::cout << labyrinthe.toString() << std::endl;
    return 0;
}
