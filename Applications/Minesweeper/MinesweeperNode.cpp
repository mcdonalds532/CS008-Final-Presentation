#include "MinesweeperNode.h"

MinesweeperNode::MinesweeperNode(const std::pair<int, int>& coordinates, const int& value) : coordinates(coordinates), value(value), validCombinations({}), validNeighbors({}) {}

void MinesweeperNode::generateValidCombinations(std::vector<std::pair<int, int>>& current, const int& index)
{
    if(current.size() == value)
    {
        validCombinations.push_back(current);
        return;
    }
    for(int i = index; i < validNeighbors.size(); i++)
    {
        current.emplace_back(validNeighbors[i]);
        generateValidCombinations(current, i + 1);
        current.pop_back();
    }
}

void MinesweeperNode::generateValidNeighbors(const std::vector<std::vector<char>>& board)
{
    for(int i = coordinates.first - 1; i <= coordinates.first + 1; i++)
        for(int j = coordinates.second - 1; j <= coordinates.second + 1; j++)
            if(i >= 0 && j >= 0 && i < board.size() && j < board[0].size() && (board[i][j] == '0' || board[i][j] == 'X'))
                validNeighbors.emplace_back(i, j);
}

const std::vector<std::vector<std::pair<int, int>>>& MinesweeperNode::getValidCombinations()
{
    return validCombinations;
}

const std::pair<int, int>& MinesweeperNode::getCoordinates() const
{
    return coordinates;
}

MinesweeperNode::iterator MinesweeperNode::begin()
{
    return validCombinations.begin();
}

MinesweeperNode::iterator MinesweeperNode::end()
{
    return validCombinations.end();
}

MinesweeperNode& MinesweeperNode::operator++()
{
    ++value;
    return *this;
}

MinesweeperNode MinesweeperNode::operator++(int)
{
    MinesweeperNode temp = *this;
    ++*this;
    return temp;
}

MinesweeperNode& MinesweeperNode::operator--()
{
    --value;
    return *this;
}

MinesweeperNode MinesweeperNode::operator--(int)
{
    MinesweeperNode temp = *this;
    --*this;
    return temp;
}

int MinesweeperNode::getValue() const
{
    return value;
}

void MinesweeperNode::increment()
{
    ++value;
}

void MinesweeperNode::decrement()
{
    --value;
}