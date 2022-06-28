#ifndef SDIZO_2_EDGE_H
#define SDIZO_2_EDGE_H

struct Edge
{
    int start;
    int end;
    int weight;

    bool operator==(const Edge &item) {
        return (this->start == item.start && this->end == item.end && this->weight == item.weight) ||
               (this->start == item.end && this->end == item.start && this->weight == item.weight);
    }
    bool operator!=(const Edge &item) {
        return !this->operator==(item);
    }
    bool operator<(const Edge &item) {
        return this->weight < item.weight;
    }
    bool operator<=(const Edge &item) {
        return this->weight <= item.weight;
    }
    bool operator>(const Edge &item) {
        return this->weight > item.weight;
    }
};

#endif //SDIZO_2_EDGE_H
