#include "MinesweeperModel.h"

MinesweeperModel::MinesweeperModel() : board(std::vector<std::vector<char>>(14, std::vector<char>(14, '0'))), nodes({}), numberOfBombs(40), width(14), height(14)
{
    generateRandomBoard();
}

void MinesweeperModel::generateRandomBoard()
{
    // Using <random> library to produce a unique board per instantiation.
    std::random_device randomDevice;
    std::mt19937 mersenneTwisterEngine(randomDevice());
    std::uniform_int_distribution distribution(0, 196);

    // Using an unordered set when generating bombs to avoid duplicates.
    std::unordered_set<int> bombs = {};
    while(bombs.size() < numberOfBombs)
        bombs.insert(distribution(mersenneTwisterEngine));

    // Marking the bombs on the board.
    for(const auto& bomb : bombs)
    {
        const int i = bomb / width;
        const int j = bomb % height;
        board[i][j] = 'X';
    }

    // Incrementing the neighboring elements if a bomb is present.
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            if(board[i][j] == 'X')
                incrementNeighboringElements(i, j);

    // Generate nodes for all the elements that are not equal to X or 0.
    generateNodes();
}

void MinesweeperModel::generateNodes()
{
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            if(board[i][j] != 'X' && board[i][j] != '0')
            {
                const int value = board[i][j] - '0';
                MinesweeperNode* newNode = new MinesweeperNode({i, j}, value);
                std::vector<std::pair<int, int>> current = {};
                newNode->generateValidNeighbors(board);
                newNode->generateValidCombinations(current, 0);
                nodes.push_back(newNode);
            }
}

void MinesweeperModel::incrementNeighboringElements(const int& x, const int& y)
{
    for(int i = x - 1; i <= x + 1; i++)
        for(int j = y - 1; j <= y + 1; j++)
            if(i >= 0 && j >= 0 && i < height && j < width && board[i][j] != 'X')
                board[i][j]++;
}

void MinesweeperModel::incrementNeighboringNodes(const std::pair<int, int>& placementCoordinates)
{
    std::vector<MinesweeperNode*> neighboringNodes = getNeighboringNodes(placementCoordinates);
    for(auto& node : neighboringNodes)
        node->increment();
}

void MinesweeperModel::decrementNeighboringNodes(const std::pair<int, int>& placementCoordinates)
{
    std::vector<MinesweeperNode*> neighboringNodes = getNeighboringNodes(placementCoordinates);
    for(auto& node : neighboringNodes)
        node->decrement();
}

std::vector<MinesweeperNode*> MinesweeperModel::getNeighboringNodes(const std::pair<int, int>& placementCoordinates)
{
    std::vector<MinesweeperNode*> neighbors;
    for(auto& node : nodes)
    {
        std::pair<int, int> coordinates = node->getCoordinates();
        if(abs(coordinates.first - placementCoordinates.first) <= 1 && abs(coordinates.second - placementCoordinates.second) <= 1)
            neighbors.push_back(node);
    }
    return neighbors;
}

const std::vector<std::vector<char>>& MinesweeperModel::getBoard() const
{
    return board;
}

void MinesweeperModel::addSolutionStep(const std::pair<int, int>& step)
{
    solutionSteps.push_back(step);
}

void MinesweeperModel::addHoveredBoxStep(const std::pair<int, int>& step)
{
    hoveredBox.push_back(step);
}

void MinesweeperModel::addRemovalStep(const std::pair<int, int>& step)
{
    removalOrder.push(step);
}

const std::vector<std::pair<int, int>>& MinesweeperModel::getSolutionSteps() const
{
    return solutionSteps;
}

const std::vector<std::pair<int, int>>& MinesweeperModel::getHoveredBoxSteps() const
{
    return hoveredBox;
}

std::queue<std::pair<int, int>> MinesweeperModel::getRemovalSteps() const
{
    return removalOrder;
}

MinesweeperNode* MinesweeperModel::getNode(const int& index)
{
    return nodes[index];
}

int MinesweeperModel::getNumberOfNodes() const
{
    return nodes.size();
}

int MinesweeperModel::getWidth() const
{
    return width;
}

int MinesweeperModel::getHeight() const
{
    return height;
}

int MinesweeperModel::getNumberOfBombs() const
{
    return numberOfBombs;
}