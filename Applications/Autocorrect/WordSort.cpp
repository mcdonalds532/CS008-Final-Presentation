#include "WordSort.h"

WordSort::WordSort() {}

void WordSort::addWordsFromFile(const std::string& fileName)
{
    words.clear();
    FileReader fileReader;
    fileReader.getInputFromFile(fileName);
    const std::vector<std::string> inputWords = fileReader.getWords();
    for(const auto& inputWord : inputWords)
    {
        auto newWord = new Word(inputWord);
        words.push_back(newWord);
    }
}

const std::vector<std::string>& WordSort::getTopSuggestions(const int& k, const std::string& userInputText)
{
    topSuggestions.clear();
    // Returning an empty vector if user has not inputted anything.
    if(userInputText.empty())
        return topSuggestions;
    // Otherwise, calculate the priority of all the words based on user input.
    for(auto* word : words)
        word->calculatePriority(userInputText);

    // Then fill a heap with all the words.
    Heap<Word*, CompareWords> heap;
    for(auto& word : words)
        heap.push(word);

    // Pop the top k elements and return the vector topSuggestions.
    while(!heap.empty() && topSuggestions.size() < k)
    {
        const Word* word = heap.top();
        std::string text = word->getWord();
        text[0] = std::toupper(static_cast<unsigned char>(text[0]));
        topSuggestions.push_back(text);
        heap.pop();
    }
    return topSuggestions;
}