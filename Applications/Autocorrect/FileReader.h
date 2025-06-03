#ifndef FILEREADER_H
#define FILEREADER_H
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

class FileReader
{
public:
    FileReader();
    // Reads input from file and stores it in a vector of strings
    void getInputFromFile(const std::string& fileName);
    // Returns the vector of strings
    const std::vector<std::string>& getWords() const;
private:
    std::vector<std::string> words;
};

#endif //FILEREADER_H