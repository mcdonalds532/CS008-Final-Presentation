#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H
#include <unordered_set>
#include <string>
#include <cctype>

enum class State
{
    START, VALID, INVALID
};

class FiniteStateMachine
{
public:
    FiniteStateMachine();
    bool isValidIdentifier(const std::string& input) const;

private:
    static bool isValidFirstCharacter(const char& c);
    static bool isValidNonFirstCharacter(const char& c);
    bool isValidKeyword(const std::string& input) const;
    const std::unordered_set<std::string> validKeywords =
    {
        "Autocorrect", "Minesweeper", "Sliding Puzzle"
    };
};

#endif //FINITESTATEMACHINE_H