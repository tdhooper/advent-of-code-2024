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

    std::regex pattern("mul\\(([0-9]{1,3}),([0-9]{1,3})\\)");
    auto begin = std::sregex_iterator(inputstring.begin(), inputstring.end(), pattern);
    auto end = std::sregex_iterator();

    int result{ 0 };

    for (std::sregex_iterator i = begin; i != end; ++i)
    {
        std::smatch match = *i;
        result += std::stoi(match[1].str()) * std::stoi(match[2].str());
    }

    std::cout << result << '\n';
}
