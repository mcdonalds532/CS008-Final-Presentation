#ifndef AUTOCORRECTAPP_H
#define AUTOCORRECTAPP_H
#include <Malena/common.hpp>
#include "WordSort.h"

class AutocorrectApp : public ml::Application
{
public:
    AutocorrectApp();
    void initialization() override;
    void registerEvents() override;
private:
    std::vector<ml::Rectangle> suggestionsBoxes;
    std::vector<ml::Text> suggestionsText;
    std::vector<std::string> topSuggestions;
    ml::Rectangle textBox;
    ml::Text textInput;
    ml::Cursor cursor;
    ml::Typer typer;
    sf::Clock clock;
    WordSort wordSort;
    int suggestions;
    float boxHeight;
    float boxWidth;
};

#endif //AUTOCORRECTAPP_H