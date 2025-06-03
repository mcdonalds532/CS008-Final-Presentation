#include "Backtracking.h"

Backtracking::Backtracking(MinesweeperModel& model) : model(model), placed({})
{
    totalNodes = model.getNumberOfNodes();
    bombsToBePlaced = model.getNumberOfBombs();
}

bool Backtracking::solve(const int& currentIndex)
{
    // Base cases
    if(bombsToBePlaced == 0)
        return isValidSolution();
    if(currentIndex == totalNodes)
        return false;

    MinesweeperNode* currentNode = model.getNode(currentIndex);
    std::pair<int, int> coordinates = currentNode->getCoordinates();
    std::vector<std::vector<std::pair<int, int>>> validCombinations = currentNode->getValidCombinations();
    for(const auto& combination : validCombinations)
    {
        if(canPlaceBomb(combination))
        {
            // Need to store the placed combinations in a vector so we can reset them after.
            std::vector<std::pair<int, int>> bombPlacements = placeBomb(coordinates, combination);
            if(solve(currentIndex + 1))
                return true;
            resetBombs(coordinates, bombPlacements);
        }
        else
        {
            model.addHoveredBoxStep(coordinates);
            model.addSolutionStep({-3, -3});
        }
    }
    return false;
}

bool Backtracking::canPlaceBomb(const std::vector<std::pair<int, int>>& bombPlacements)
{
    // Maps each affected node to the amount it will be decremented by.
    std::unordered_map<MinesweeperNode*, int> affectedNodes;
    for(const auto& bombPlacement : bombPlacements)
    {
        if(placed.find(bombPlacement) == placed.end())
        {
            std::vector<MinesweeperNode*> neighbors = model.getNeighboringNodes(bombPlacement);
            for(const auto& neighbor : neighbors)
                affectedNodes[neighbor]++;
        }
    }
    for(const auto&[fst, snd] : affectedNodes)
    {
        if(fst->getValue() < snd)
            return false;
    }
    return true;
}

std::vector<std::pair<int, int>> Backtracking::placeBomb(const std::pair<int, int>& coordinates, const std::vector<std::pair<int, int>>& bombPlacements)
{
    std::vector<std::pair<int, int>> placements = {};
    for(const auto& bombPlacement : bombPlacements)
    {
        model.addHoveredBoxStep(coordinates);
        if(placed.find(bombPlacement) == placed.end())
        {
            model.addSolutionStep(bombPlacement);
            placed.insert(bombPlacement);
            model.decrementNeighboringNodes(bombPlacement);
            bombsToBePlaced--;
            placements.push_back(bombPlacement);
        }
        else
        {
            model.addSolutionStep({-1, -1});
        }
    }
    return placements;
}

void Backtracking::resetBombs(const std::pair<int, int>& coordinates, const std::vector<std::pair<int, int>>& bombPlacements)
{
    for(const auto& bombPlacement : bombPlacements)
    {
        model.addHoveredBoxStep(coordinates);
        model.addSolutionStep({-2, -2});
        placed.erase(bombPlacement);
        model.incrementNeighboringNodes(bombPlacement);
        model.addRemovalStep(bombPlacement);
        bombsToBePlaced++;
    }
}

bool Backtracking::isValidSolution() const
{
    for(int i = 0; i < totalNodes; i++)
    {
        MinesweeperNode* node = model.getNode(i);
        if(node->getValue() != 0)
            return false;
    }
    model.addSolutionStep({-4, -4});
    return true;
}