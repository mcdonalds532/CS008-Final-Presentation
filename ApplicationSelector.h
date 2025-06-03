#ifndef APPLICATIONSELECTOR_H
#define APPLICATIONSELECTOR_H
#include "Applications/Sliding Puzzle/SlidingPuzzleApp.h"
#include "Applications/Autocorrect/AutocorrectApp.h"
#include "Applications/Minesweeper/MinesweeperApp.h"
#include <Malena/common.hpp>
#include "FiniteStateMachine.h"

class ApplicationSelector : public ml::Application
{
public:
    ApplicationSelector();
    void initialization() override;
    void registerEvents() override;
private:
    FiniteStateMachine fsm;
    ml::Rectangle textBox;
    ml::Text textInput;
    ml::Cursor cursor;
    ml::Typer typer;
    sf::Clock clock;
    float boxHeight;
    float boxWidth;
};

#endif //APPLICATIONSELECTOR_H