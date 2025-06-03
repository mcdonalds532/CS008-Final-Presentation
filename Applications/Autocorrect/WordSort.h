#ifndef WORDSORT_H
#define WORDSORT_H
#include "CompareWords.h"
#include "FileReader.h"
#include "Heap.h"
#include "Word.h"

class WordSort
{
public:
    WordSort();
    // Empties the words vector and populates it with words from an input file using FileReader's methods.
    void addWordsFromFile(const std::string& fileName);
    // Uses a heap to return the top k suggestions based on user's input.
    const std::vector<std::string>& getTopSuggestions(const int& k, const std::string& userInputText);
private:
    std::vector<std::string> topSuggestions;
    std::vector<Word*> words;
};

#endif //WORDSORT_H