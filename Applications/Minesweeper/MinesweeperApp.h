#ifndef MINESWEEPERAPP_H
#define MINESWEEPERAPP_H
#include "Malena/Utilities/TextureSlicer.h"
#include "Malena/Utilities/ImageRects.h"
#include <Malena/common.hpp>
#include "Backtracking.h"
#include "MinesweeperModel.h"
#include <vector>

class MinesweeperApp : public ml::Application
{
public:
    MinesweeperApp();
    void initialization() override;
    void registerEvents() override;
private:
    std::vector<std::vector<ml::RectangleButton>> grid;
    std::vector<std::pair<int, int>> solutionSteps;
    std::vector<std::pair<int, int>> hoveredSteps;
    std::queue<std::pair<int, int>> removalSteps;
    std::pair<int, int> previouslyHovered = {7, 7};
    sf::Texture texture;
    int currentStep = 0;
    float delay = 0.2f;
    sf::Clock clock;
    MinesweeperModel model;
};

#endif //MINESWEEPERAPP_H