#include "ApplicationSelector.h"

ApplicationSelector::ApplicationSelector() : Application(sf::VideoMode({720, 420}, 32), "Text Input App", *this), boxHeight(40.f), boxWidth(360.f) {}

void ApplicationSelector::initialization()
{
    textBox.setSize({boxWidth, boxHeight});
    textBox.setFillColor(sf::Color::White);
    textBox.setPosition({180, 190});
    textBox.setOutlineThickness(5);
    addComponent(textBox);

    textInput.setCharacterSize(30);
    textInput.setFillColor(sf::Color::Black);
    textInput.setPosition({185, 190});
    textInput.setString("");
    addComponent(textInput);

    cursor.setCharacterSize(30);
    cursor.setPosition({185, 188});
    cursor.setFillColor(sf::Color::Black);
    addComponent(cursor);
}

void ApplicationSelector::registerEvents()
{
    textBox.onClick([this]()
    {
        textBox.enableState(ml::Stateful::FOCUSED);
        textBox.setOutlineColor(sf::Color::Red);
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

    textBox.onUpdate([this]()
    {
        if(textBox.checkState(ml::Stateful::FOCUSED))
        {
            const std::string s = typer.getString();
            if(fsm.isValidIdentifier(s))
                textBox.setOutlineColor(sf::Color::Green);
            else
                textBox.setOutlineColor(sf::Color::Red);
        }
    });

    typer.onKeypress([this]()
    {
        if(textBox.checkState(ml::Stateful::FOCUSED))
        {
            const std::string s = typer.getString();
            textInput.setString(s);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
            {
                if(fsm.isValidIdentifier(s))
                {
                    if(s[0] == 'S')
                    {
                        SlidingPuzzleApp app;
                        app.run();
                    }
                    else if(s[0] == 'M')
                    {
                        MinesweeperApp app;
                        app.run();
                    }
                    else if(s[0] == 'A')
                    {
                        AutocorrectApp app;
                        app.run();
                    }
                }
            }
        }
    });

    textInput.onUpdate([this]()
    {
        const std::string s = typer.getString();
        textInput.setString(s);
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
}