#ifndef WORD_H
#define WORD_H
#include <algorithm>
#include <string>
#include <cmath>

class Word
{
public:
    Word(const std::string& word);
    // Recalculates the priority of a word based on the input word.
    void calculatePriority(const std::string& inputWord);
    // Returns the word as a string.
    const std::string& getWord() const;
    // Returns the priority.
    int getPriority() const;
private:
    std::string word;
    int priority;
};

#endif //WORD_H