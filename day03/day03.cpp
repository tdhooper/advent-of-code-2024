#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main()
{
    std::ifstream input{ "input.txt" };

    if (!input)
    {
        std::cerr << "Cannot open file input.txt";
        return 1;
    }

    std::stringstream inputstream{};
    inputstream << input.rdbuf();
    std::string inputstring = inputstream.str();

    std::regex mulPattern("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    auto mulBegin = std::sregex_iterator(inputstring.begin(), inputstring.end(), mulPattern);
    auto mulEnd = std::sregex_iterator();

    int result{ 0 };

    for (std::sregex_iterator i = mulBegin; i != mulEnd; ++i)
    {
        std::smatch match = *i;
        result += std::stoi(match[1].str()) * std::stoi(match[2].str());
    }

    std::cout << result << '\n';

    result = 0;

    std::regex doPattern("do(n't)?\\(\\)");
    auto doBegin = std::sregex_iterator(inputstring.begin(), inputstring.end(), doPattern);
    auto doEnd = std::sregex_iterator();
    std::sregex_iterator doIterator = doBegin;
    
    bool enabled = true;
    for (std::sregex_iterator i = mulBegin; i != mulEnd; ++i)
    {
        std::smatch mulMatch = *i;
        int mulIndex = mulMatch.position();

        while (doIterator != doEnd) {
            std::smatch doMatch = *doIterator;
            int doIndex = doMatch.position();
            if (doIndex > mulIndex) {
                break;
            }
            enabled = doMatch[1].str().empty();
            doIterator++;
        }

        if (enabled) {
            result += std::stoi(mulMatch[1].str()) * std::stoi(mulMatch[2].str());
        }
    }

    std::cout << result << '\n';
}
