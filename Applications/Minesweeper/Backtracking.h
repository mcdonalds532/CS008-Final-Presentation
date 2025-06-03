#ifndef BACKTRACKING_H
#define BACKTRACKING_H
#include <unordered_map>
#include "MinesweeperModel.h"
#include <stack>
#include <set>

class Backtracking
{
public:
    explicit Backtracking(MinesweeperModel& model);
    bool solve(const int& currentIndex);

private:
    std::set<std::pair<int, int>> placed;
    int bombsToBePlaced;
    int totalNodes;
    MinesweeperModel& model;

    // Helper functions used by solve.
    std::vector<std::pair<int, int>> placeBomb(const std::pair<int, int>& coordinates, const std::vector<std::pair<int, int>>& bombPlacements);
    void resetBombs(const std::pair<int, int>& coordinates, const std::vector<std::pair<int, int>>& bombPlacements);
    bool canPlaceBomb(const std::vector<std::pair<int, int>>& bombPlacements);
    bool isValidSolution() const;
};

#endif //BACKTRACKING_H