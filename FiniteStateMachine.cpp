#include "FiniteStateMachine.h"

FiniteStateMachine::FiniteStateMachine() = default;

bool FiniteStateMachine::isValidIdentifier(const std::string &input) const
{
    if(isValidKeyword(input))
        return true;
    return false;
}

bool FiniteStateMachine::isValidFirstCharacter(const char& c)
{
    return c == '_' || std::isalpha(c);
}

bool FiniteStateMachine::isValidNonFirstCharacter(const char& c)
{
    return c == '_' || std::isalnum(c);
}

bool FiniteStateMachine::isValidKeyword(const std::string &input) const
{
    if(validKeywords.find(input) != validKeywords.end())
        return true;
    return false;
}