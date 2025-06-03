#include "MinesweeperApp.h"

MinesweeperApp::MinesweeperApp() : Application(sf::VideoMode({480, 480}, 32), "Minesweeper App", *this) {}

void MinesweeperApp::initialization()
{
    texture.loadFromFile("Applications/Minesweeper/minesweep_cut.png");
    ml::ImageRects rects = ml::TextureSlicer::getImageRects(texture, 11, 11);
    sf::IntRect intRect;

    std::vector<std::vector<char>> board = model.getBoard();
    int width = model.getWidth();
    int height = model.getHeight();

    for(int i = 0; i < height; i++)
    {
        std::vector<ml::RectangleButton> row;
        for(int j = 0; j < width; j++)
        {
            if(board[i][j] == '0' || board[i][j] == 'X')
                intRect = rects.getIntRect(0, 0);
            else
                intRect = rects.getIntRect(1, board[i][j] - '1');
            ml::RectangleButton gridBox;
            float boxWidth = 480.f / static_cast<float>(width);
            float boxHeight = 480.f / static_cast<float>(height);
            gridBox.setSize({boxWidth, boxHeight});
            gridBox.setTextureRect(intRect);
            gridBox.setTexture(&texture);
            gridBox.setPosition({static_cast<float>(j) * boxWidth, static_cast<float>(i) * boxHeight});
            row.push_back(gridBox);
        }
        grid.push_back(row);
    }

    for(auto& row: grid)
        for(auto& element : row)
            addComponent(element);

    Backtracking backtracking(model);
    backtracking.solve(0);
    solutionSteps = model.getSolutionSteps();
    hoveredSteps = model.getHoveredBoxSteps();
    removalSteps = model.getRemovalSteps();

    onUpdate([this]()
    {
        if(currentStep >= solutionSteps.size())
            return;
        if(clock.getElapsedTime().asSeconds() >= delay)
        {
            texture.loadFromFile("Applications/Minesweeper/minesweep_cut.png");
            ml::ImageRects rects = ml::TextureSlicer::getImageRects(texture, 11, 11);
            sf::IntRect intRect;

            std::pair<int, int> hovered = hoveredSteps[currentStep];
            grid[previouslyHovered.first][previouslyHovered.second].setFillColor(sf::Color::White);
            grid[hovered.first][hovered.second].setFillColor({100, 170, 220});
            previouslyHovered = hovered;

            if(solutionSteps[currentStep].first == -2)
            {
                std::pair<int, int> coordinates = removalSteps.front();
                intRect =  rects.getIntRect(0, 0);
                removalSteps.pop();
                grid[coordinates.first][coordinates.second].setTextureRect(intRect);
                grid[coordinates.first][coordinates.second].setTexture(&texture);
            }
            else if(solutionSteps[currentStep].first != -1 && solutionSteps[currentStep].first != -3)
            {
                std::pair<int, int> coordinates = solutionSteps[currentStep];
                intRect =  rects.getIntRect(0, 2);
                grid[coordinates.first][coordinates.second].setTextureRect(intRect);
                grid[coordinates.first][coordinates.second].setTexture(&texture);
            }

            currentStep++;
            clock.restart();
        }
    });
}

void MinesweeperApp::registerEvents() {}