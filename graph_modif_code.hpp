#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

class Graphe {
    private:
        std::unordered_map<int, std::unordered_set<int>> A;
        bool oriente;

    public:
        Graphe(bool oriente = true) : oriente(oriente) {}

        void construire(std::unordered_map<int, std::unordered_set<int>> A) {
            this->A = A;
        }

        void ajouterSommet(int x) {
            if (A.find(x) == A.end()) {
                A[x] = std::unordered_set<int>();
            }
        }

        void ajouterArete(int x, int y) {
            ajouterSommet(x);
            ajouterSommet(y);
            A[x].insert(y);
            if (!oriente) {
                A[y].insert(x);
            }
        }

        std::unordered_set<int> voisins(int x) {
            return A[x];
        }

        std::vector<std::pair<int, int>> aretes() {
            std::vector<std::pair<int, int>> L;
            for (const auto& entry : A) {
                int x = entry.first;
                const auto& V = entry.second;
                for (int v : V) {
                    L.push_back(std::make_pair(x, v));
                }
            }
            return L;
        }

        bool arete(int x, int y) {
            return A[y].count(x) > 0;
        }

        std::unordered_set<int> parcoursProf(int s, std::unordered_set<int>& vus) {
            if (vus.count(s) == 0) {
                vus.insert(s);
                for (int v : voisins(s)) {
                    parcoursProf(v, vus);
                }
            }
            return vus;
        }

        std::unordered_map<int, int> parcoursCh(int s, std::unordered_map<int, int>& vus) {
            if (vus.count(s) == 0) {
                vus[s] = -1;
                for (int v : voisins(s)) {
                    parcoursCh(v, vus);
                }
            }
            return vus;
        }

        std::vector<int> chemins(int x, int y) {
            std::unordered_map<int, int> vus;
            vus = parcoursCh(x, vus);
            std::vector<int> c;
            if (vus.count(y) > 0) {
                int s = y;
                while (s != -1) {
                    c.push_back(s);
                    s = vus[s];
                }
            }
            std::reverse(c.begin(), c.end());
            return c;
        }

        bool existeChemin(int x, int y) {
            std::unordered_set<int> vus;
            vus = parcoursProf(x, vus);
            return vus.count(y) > 0;
        }

        std::unordered_map<int, int> parcoursLarg(int s) {
            std::unordered_map<int, int> dist;
            std::unordered_set<int> cour;
            std::unordered_set<int> suiv;
            cour.insert(s);
            int currentDist = 0;
            while (!cour.empty()) {
                int node = *(cour.begin());
                cour.erase(cour.begin());
                dist[node] = currentDist;
                currentDist++;
                for (int v : voisins(node)) {
                    if (dist.count(v) == 0) {
                        suiv.insert(v);
                    }
                }
                if (cour.empty()) {
                    cour = suiv;
                    suiv.clear();
                }
            }
            return dist;
        }

        std::unordered_map<int, int> parcoursLargChemin(int s) {
            std::unordered_map<int, int> vus;
            std::unordered_set<int> cour;
            std::unordered_set<int> suiv;
            cour.insert(s);
            while (!cour.empty()) {
                int node = *(cour.begin());
                cour.erase(cour.begin());
                for (int v : voisins(node)) {
                    if (vus.count(v) == 0) {
                        suiv.insert(v);
                        vus[v] = node;
                    }
                }
                if (cour.empty()) {
                    cour = suiv;
                    suiv.clear();
                }
            }
            return vus;
        }

        std::vector<int> cheminsLarg(int x, int y) {
            std::unordered_map<int, int> vus;
            vus = parcoursLargChemin(x);
            std::vector<int> c;
            if (vus.count(y) > 0) {
                int s = y;
                while (s != -1) {
                    c.push_back(s);
                    s = vus[s];
                }
            }
            std::reverse(c.begin(), c.end());
            return c;
        }

        int distance(int x, int y) {
            std::unordered_map<int, int> dist;
            dist = parcoursLarg(x);
            if (dist.count(y) > 0) {
                return dist[y];
            }
            return -1;
        }
};

int main() {
    Graphe graphe;
    graphe.ajouterArete(1, 2);
    graphe.ajouterArete(1, 3);
    graphe.ajouterArete(2, 4);
    graphe.ajouterArete(3, 4);
    graphe.ajouterArete(4, 5);
    std::vector<std::pair<int, int>> aretes = graphe.aretes();
    for (const auto& arete : aretes) {
        std::cout << "(" << arete.first << ", " << arete.second << ")" << std::endl;
    }
    std::unordered_set<int> voisins = graphe.voisins(4);
    for (int voisin : voisins) {
        std::cout << voisin << " ";
    }
    std::cout << std::endl;
    std::cout << graphe.arete(2, 4) << std::endl;
    std::unordered_set<int> parcoursProf = graphe.parcoursProf(1);
    for (int sommet : parcoursProf) {
        std::cout << sommet << " ";
    }
    std::cout << std::endl;
    std::unordered_map<int, int> parcoursCh = graphe.parcoursCh(1);
    for (const auto& entry : parcoursCh) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
    std::vector<int> chemins = graphe.chemins(1, 5);
    for (int sommet : chemins) {
        std::cout << sommet << " ";
    }
    std::cout << std::endl;
    std::cout << graphe.existeChemin(1, 5) << std::endl;
    std::unordered_map<int, int> parcoursLarg = graphe.parcoursLarg(1);
    for (const auto& entry : parcoursLarg) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
    std::unordered_map<int, int> parcoursLargChemin = graphe.parcoursLargChemin(1);
    for (const auto& entry : parcoursLargChemin) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
    std::vector<int> cheminsLarg = graphe.cheminsLarg(1, 5);
    for (int sommet : cheminsLarg) {
        std::cout << sommet << " ";
    }
    std::cout << std::endl;
    std::cout << graphe.distance(1, 5) << std::endl;
    return 0;
}
