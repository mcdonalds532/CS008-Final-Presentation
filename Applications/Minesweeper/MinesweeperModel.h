#ifndef MINESWEEPERMODEL_H
#define MINESWEEPERMODEL_H
#include <unordered_set>
#include <vector>
#include <random>
#include <queue>
#include "MinesweeperNode.h"
#include <cmath>

class MinesweeperModel
{
public:
    MinesweeperModel();

    // Setters.
    void addSolutionStep(const std::pair<int, int>& step);
    void addHoveredBoxStep(const std::pair<int, int>& step);
    void addRemovalStep(const std::pair<int, int>& step);
    const std::vector<std::pair<int, int>>& getSolutionSteps() const;
    const std::vector<std::pair<int, int>>& getHoveredBoxSteps() const;
    std::queue<std::pair<int, int>> getRemovalSteps() const;
    // Getters.
    const std::vector<std::vector<char>>& getBoard() const;
    MinesweeperNode* getNode(const int& index);
    int getNumberOfNodes() const;
    int getWidth() const;
    int getHeight() const;
    int getNumberOfBombs() const;

    // Returns pointers to the neighboring nodes of a non-node coordinate.
    std::vector<MinesweeperNode*> getNeighboringNodes(const std::pair<int, int>& placementCoordinates);
    // Increments/decrements the value of the neighboring nodes.
    void incrementNeighboringNodes(const std::pair<int, int>& placementCoordinates);
    void decrementNeighboringNodes(const std::pair<int, int>& placementCoordinates);

private:
    std::vector<std::vector<char>> board;
    std::vector<MinesweeperNode*> nodes;
    int numberOfBombs;
    int width;
    int height;
    // Initializes a board; called in constructor.
    void generateRandomBoard();
    // Helper function to determine amount of surrounding bombs per box.
    void incrementNeighboringElements(const int& x, const int& y);
    // Generates nodes for the non-zero and non-bomb boxes; stored in nodes.
    void generateNodes();
    // {-1, -1} - Bomb already at location; {-2, -2} - Erase last placed bomb; {-3, -3} - Cannot move; {-4, -4} - Completed; Any other combination is a placement.
    std::vector<std::pair<int, int>> solutionSteps;
    // Coordinates of the hovered box.
    std::vector<std::pair<int, int>> hoveredBox;
    // Since removal steps do not match solution steps, we need to store the order in a queue.
    std::queue<std::pair<int, int>> removalOrder;
};

#endif //MINESWEEPERMODEL_H