#include "Word.h"

Word::Word(const std::string& word) : word(word), priority(0) {}

int Word::getPriority() const
{
    return priority;
}

void Word::calculatePriority(const std::string& inputWord)
{
    if(inputWord.empty())
    {
        priority = 0;
        return;
    }

    int priorityValue = 0;
    int wordSize = static_cast<int>(word.size());
    int inputWordSize = static_cast<int>(inputWord.size());

    // For each matching letter in sequential order, add 2 to priority.
    int i = 0;
    int j = 0;
    while(i < word.size() && j < inputWord.size() && word[i] == inputWord[j])
    {
        priorityValue += 2;
        i++;
        j++;
    }

    // If the frequency of a letter is matching for both words and is non-zero, add 2 to priority.
    int wordLetters[26] = {};
    int inputWordLetters[26] = {};
    for(const char& c : word)
        if(std::islower(c))
            wordLetters[c - 'a']++;
    for(const char& c : inputWord)
        if(std::islower(c))
            inputWordLetters[c - 'a']++;
    for(int c = 0; c < 26; c++)
        if(wordLetters[c] == inputWordLetters[c] && wordLetters[c] != 0)
            priorityValue += 2;

    // If the words are a direct anagram of each other, add 5 to the priority.
    std::string currentWord = word;
    std::string givenWord = inputWord;
    if(!currentWord.empty() && !givenWord.empty())
    {
        std::sort(currentWord.begin(), currentWord.end());
        std::sort(givenWord.begin(), givenWord.end());
        if(givenWord == currentWord)
            priorityValue += 5;
    }

    // Subtract the difference in size of the two words from the priority.
    const int difference = wordSize - inputWordSize;
    priorityValue -= abs(difference);

    priority = priorityValue;
}

const std::string& Word::getWord() const
{
    return word;
}