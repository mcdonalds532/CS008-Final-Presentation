#ifndef MINESWEEPERNODE_H
#define MINESWEEPERNODE_H
#include <algorithm>
#include <utility>
#include <vector>

class MinesweeperNode
{
public:
    // Constructor takes in a pair of coordinates and the number of surrounding bombs.
    MinesweeperNode(const std::pair<int, int>& coordinates, const int& value);
    // Generates all neighboring coordinates that are hidden and stores it in validNeighbors.
    void generateValidNeighbors(const std::vector<std::vector<char>>& board);
    // Generates all valid bomb placements and stores it in validCombinations.
    void generateValidCombinations(std::vector<std::pair<int, int>>& current, const int& index);
    // Returns the valid combinations of places.
    const std::vector<std::vector<std::pair<int, int>>>& getValidCombinations();
    // Returns the coordinates of the node.
    const std::pair<int, int>& getCoordinates() const;

    // Iterators.
    typedef std::vector<std::vector<std::pair<int, int>>>::iterator iterator;
    iterator begin();
    iterator end();

    // Operator overloads.
    MinesweeperNode& operator++();
    MinesweeperNode operator++(int);
    MinesweeperNode& operator--();
    MinesweeperNode operator--(int);

    // Increment and decrement.
    void increment();
    void decrement();
    int getValue() const;

private:
    int value;
    const std::pair<int, int> coordinates;
    std::vector<std::pair<int, int>> validNeighbors;
    std::vector<std::vector<std::pair<int, int>>> validCombinations;
};

#endif //MINESWEEPERNODE_H