#include "FileReader.h"

FileReader::FileReader() {}

void FileReader::getInputFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);
    if(!file.is_open())
        return;
    std::string s;
    while(std::getline(file, s))
    {
        // Will first convert all names to lower case so they can be used more easily to compute priority.
        s[0] = std::tolower(static_cast<unsigned char>(s[0]));
        words.push_back(s);
    }
}

const std::vector<std::string>& FileReader::getWords() const
{
    return words;
}