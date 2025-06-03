#include "AutocorrectApp.h"

AutocorrectApp::AutocorrectApp() : Application(sf::VideoMode({720, 420}, 32), "Text Input App", *this), suggestions(5), boxWidth(360.f), boxHeight(40.f) {}

void AutocorrectApp::initialization()
{
    // Default settings of the text box.
    textBox.setSize({boxWidth, boxHeight});
    textBox.setFillColor(sf::Color::White);
    textBox.setPosition({180, 190});
    textBox.setOutlineThickness(5);
    addComponent(textBox);

    cursor.setCharacterSize(30);
    cursor.setPosition({185, 188});
    cursor.setFillColor(sf::Color::Black);
    addComponent(cursor);

    textInput.setCharacterSize(30);
    textInput.setFillColor(sf::Color::Black);
    textInput.setPosition({185, 190});
    textInput.setString("");
    addComponent(textInput);

    for(int i = 0; i < suggestions; i++)
    {
        ml::Rectangle suggestionBox;
        suggestionBox.setSize({boxWidth, boxHeight / 1.3f});
        suggestionBox.setFillColor(sf::Color::White);
        suggestionBox.setOutlineThickness(5);
        suggestionBox.setOutlineColor({192, 192, 192, 128});
        suggestionBox.setPosition({textBox.getPosition().x,
            textBox.getPosition().y + boxHeight + textBox.getOutlineThickness() + static_cast<float>(i) * suggestionBox.getOutlineThickness() + static_cast<float>(i) * (boxHeight / 1.3f)});
        suggestionBox.toggleState(ml::Stateful::HIDDEN);
        suggestionsBoxes.push_back(suggestionBox);

        ml::Text suggestionText;
        suggestionText.setCharacterSize(23);
        suggestionText.setFillColor(sf::Color::Black);
        suggestionText.setString("Hey");
        suggestionText.setPosition({suggestionBox.getPosition().x, suggestionBox.getPosition().y});
        suggestionText.toggleState(ml::Stateful::HIDDEN);
        suggestionsText.push_back(suggestionText);
    }

    for(auto& suggestion : suggestionsBoxes)
        addComponent(suggestion);
    for(auto& suggestionText : suggestionsText)
        addComponent(suggestionText);

    // First add empty strings to the vector so that there are no issues when attempting to access it.
    for(int i = 0; i < suggestions; i++)
        topSuggestions.emplace_back("");

    // Populate the dictionary of words from the file.
    wordSort.addWordsFromFile("Applications/Autocorrect/5000-baby-girl-names.txt");
}

void AutocorrectApp::registerEvents()
{
    // States change based on user interaction.
    textBox.onClick([this]()
    {
        textBox.enableState(ml::Stateful::FOCUSED);
        textBox.setOutlineColor(sf::Color::Blue);
        cursor.enableState(ml::Stateful::BLINKING);
        typer.enableState(ml::Stateful::ENABLED);
    });
    textBox.onBlur([this]()
    {
        textBox.disableState(ml::Stateful::FOCUSED);
        textBox.setOutlineColor(sf::Color::Black);
        cursor.disableState(ml::Stateful::BLINKING);
        typer.disableState(ml::Stateful::ENABLED);
    });
    typer.onKeypress([this]()
    {
        if(textBox.checkState(ml::Stateful::FOCUSED))
        {
            std::string s = typer.getString();
            textInput.setString(s);
            topSuggestions = wordSort.getTopSuggestions(suggestions, s);
            {
                for(int i = 0; i < suggestions; i++)
                {
                    if(!topSuggestions.empty())
                    {
                        suggestionsText[i].setString(topSuggestions[i]);
                        suggestionsText[i].disableState(ml::Stateful::HIDDEN);
                        suggestionsBoxes[i].disableState(ml::Stateful::HIDDEN);
                    }
                    else
                    {
                        suggestionsText[i].enableState(ml::Stateful::HIDDEN);
                        suggestionsBoxes[i].enableState(ml::Stateful::HIDDEN);
                    }
                }
            }
        }
    });
    textInput.onUpdate([this]()
    {
        std::string s = typer.getString();
        topSuggestions = wordSort.getTopSuggestions(suggestions, s);
        textInput.setString(s);
        if(textBox.checkState(ml::Stateful::FOCUSED))
        {
            for(int i = 0; i < suggestions; i++)
            {
                if(!topSuggestions.empty())
                {
                    suggestionsText[i].setString(topSuggestions[i]);
                    suggestionsText[i].disableState(ml::Stateful::HIDDEN);
                    suggestionsBoxes[i].disableState(ml::Stateful::HIDDEN);
                }
                else
                {
                    suggestionsText[i].enableState(ml::Stateful::HIDDEN);
                    suggestionsBoxes[i].enableState(ml::Stateful::HIDDEN);
                }
            }
        }
    });
    cursor.onUpdate([this]()
    {
        if(textBox.checkState(ml::Stateful::FOCUSED))
        {
            std::string s = typer.getString();
            float newCursorPosition = 185.f + textInput.getGlobalBounds().size.length();
            cursor.setPosition({newCursorPosition, cursor.getPosition().y});
            if(clock.getElapsedTime().asMilliseconds() > 500)
            {
                cursor.toggleState(ml::Stateful::HIDDEN);
                clock.restart();
            }
        }
    });

    for(int i = 0; i < suggestions; i++)
    {
        suggestionsText[i].onUpdate([this, i]()
        {
            std::string s = typer.getString();
            suggestionsText[i].setString(topSuggestions[i]);
        });
        suggestionsBoxes[i].onClick([this, i]()
        {
            const std::string s = suggestionsText[i].getString();
            typer.setString(s);
            for(int j = 0; j < suggestions; j++)
            {
                // Suggestions are hidden once one is selected.
                suggestionsText[j].enableState(ml::Stateful::HIDDEN);
                suggestionsBoxes[j].enableState(ml::Stateful::HIDDEN);
            }
        });
    }
}