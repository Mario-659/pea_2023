#include "TabuSearch.h"
#include <algorithm>
#include <limits>

TabuSearch::TabuSearch(int timeLimit)
        : timeLimit(timeLimit) {}

void TabuSearch::solve(AdjacencyMatrix &graph) {
    // Pobierz liczbę wierzchołków w grafie.
    verticesNumber = graph.getSize();

    // Inicjalizacja Tablicy Tabu (dwuwymiarowa tablica) z zerowymi wartościami.
    std::vector<std::vector<int>> tabuTable(verticesNumber, std::vector<int>(verticesNumber, 0));

    // Ustawienie początkowej ścieżki jako domyślnej permutacji wierzchołków (0, 1, 2, ...).
    std::vector<int> currentPath = getDefaultTabuPath();

    // Obliczenie kosztu początkowej ścieżki.
    int currentCost = getPathCost(currentPath, graph);

    // Zainicjowanie najlepszego kosztu i ścieżki jako początkowe rozwiązanie.
    int bestCost = currentCost;
    std::vector<int> bestPath = currentPath;

    // Wartość kary w Tablicy Tabu (określa czas trwania zakazu).
    int punishment = 10 * verticesNumber;

    // Rozpoczęcie liczenia czasu algorytmu.
    auto start = std::chrono::high_resolution_clock::now();

    // Pętla główna: działa do momentu osiągnięcia limitu czasu.
    while (std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count() < timeLimit) {
        // Generowanie losowej ścieżki jako punktu startowego dla tej iteracji.
        currentPath = generateRandomPath();

        // Przeszukiwanie sąsiedztwa: iteracja po wszystkich możliwych zamianach miast w ścieżce.
        for (int i = 0; i < verticesNumber - 1; ++i) {
            int bestNextCost = std::numeric_limits<int>::max(); // Najlepszy koszt sąsiedztwa.
            int bestK = -1, bestL = -1; // Indeksy wierzchołków do zamiany.

            // Dla każdej pary wierzchołków w bieżącej ścieżce.
            for (int k = 0; k < verticesNumber - 1; ++k) {
                for (int l = k + 1; l < verticesNumber; ++l) {
                    // Zamiana dwóch wierzchołków w ścieżce.
                    std::swap(currentPath[k], currentPath[l]);

                    // Obliczenie nowego kosztu ścieżki po zamianie.
                    int newCost = getPathCost(currentPath, graph);

                    // Sprawdzenie, czy nowy koszt jest lepszy i czy ruch nie jest zabroniony przez Tablicę Tabu.
                    if (newCost < bestNextCost && tabuTable[k][l] == 0) {
                        bestNextCost = newCost;
                        bestK = k;
                        bestL = l;
                    }

                    // Cofnięcie zamiany (przywrócenie poprzedniej ścieżki).
                    std::swap(currentPath[k], currentPath[l]);
                }
            }

            // Wykonanie najlepszej zamiany znalezionej w sąsiedztwie.
            std::swap(currentPath[bestK], currentPath[bestL]);

            // Dodanie zamiany do Tablicy Tabu z wartością kary.
            tabuTable[bestK][bestL] = punishment;

            // Aktualizacja najlepszego rozwiązania, jeśli znaleziono lepszy koszt.
            if (bestNextCost < bestCost) {
                bestCost = bestNextCost;
                bestPath = currentPath;
            }

            // Aktualizacja czasu trwania zakazów w Tablicy Tabu.
            for (auto &row: tabuTable) {
                for (auto &element: row) {
                    if (element > 0) --element; // Redukcja czasu trwania zakazów.
                }
            }
        }
    }

    // Przypisanie najlepszego rozwiązania do atrybutów klasy.
    shortestPathLength = bestCost;
    path = bestPath;
}

int TabuSearch::getPathCost(const std::vector<int> &pathInstance, const AdjacencyMatrix &graph) {
    int cost = 0;
    for (int i = 1; i < pathInstance.size(); ++i) {
        cost += graph.getEdgeWeight(pathInstance[i - 1], pathInstance[i]);
    }
    cost += graph.getEdgeWeight(pathInstance.back(), pathInstance[0]);
    return cost;
}

std::vector<int> TabuSearch::getDefaultTabuPath() {
    std::vector<int> newPath(verticesNumber);
    std::iota(newPath.begin(), newPath.end(), 0);
    return newPath;
}

std::vector<int> TabuSearch::generateRandomPath() {
    std::vector<int> randomPath = getDefaultTabuPath();
    std::shuffle(randomPath.begin(), randomPath.end(), std::mt19937{std::random_device{}()});
    return randomPath;
}

std::string TabuSearch::toString() {
    std::string result;
    for (int city: path) {
        result += std::to_string(city) + " -> ";
    }
    result += "0";
    return result;
}
