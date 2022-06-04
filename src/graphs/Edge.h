#ifndef SDIZO_2_EDGE_H
#define SDIZO_2_EDGE_H

#pragma once

/// Struktura opisująca krawędź.
struct Edge
{
    /// Wierzchołek początkowy krawędzi.
    int start;
    /// Wierzchołek końcowy krawędzi.
    int end;
    /// Waga krawędzi.
    int weight;
    /// Sprawdza czy krawędzie są równe (w przypadku MST są nieskierowane).
    /// \param item - krawędź do porównania.
    /// \return true jeśli krawędzie są równe, w przeciwnym wypadku false.
    bool operator==(const Edge &item)
    {
        return (this->start == item.start && this->end == item.end && this->weight == item.weight) ||
               (this->start == item.end && this->end == item.start && this->weight == item.weight);
    }
    /// Sprawdza czy krawędzie są różne.
    /// \param item - krawędź do porównania.
    /// \return true jeśli krawędzie są różne, w przeciwnym wypadku false.
    bool operator!=(const Edge &item)
    {
        return !this->operator==(item);
    }
    /// Sprawdza czy waga krawędzi jest mniejsza od danej.
    /// \param item - krawędź do porównania.
    /// \return true jeśli waga krawędzi jest mniejsza, w przeciwnym wypadku false.
    bool operator<(const Edge &item)
    {
        return this->weight < item.weight;
    }
    /// Sprawdza czy waga krawędzi jest mniejsza bądź równa od danej.
    /// \param item - krawędź do porównania.
    /// \return true jest waga krawędzi jest mniejsza lub równa, w przeciwnym wypadku false.
    bool operator<=(const Edge &item)
    {
        return this->weight <= item.weight;
    }
    /// Sprawdza czy waga krawędzi jest większa od danej.
    /// \param item - krawędź do porównania.
    /// \return true jest waga krawędzi jest większa, w przeciwnym wypadku false.
    bool operator>(const Edge &item)
    {
        return this->weight > item.weight;
    }
};

#endif //SDIZO_2_EDGE_H
