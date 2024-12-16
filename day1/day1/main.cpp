#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int main()
{
    std::ifstream input{ "input.txt" };

    if (!input)
    {
        std::cerr << "Cannot open file input.txt";
        return 1;
    }

    int count { 0 };
    std::string line{};

    while (std::getline(input, line))
    {
        count++;
    }

    std::vector<int> listA(count);
    std::vector<int> listB(count);
   
    input.clear();
    input.seekg(0);

    std::stringstream linestream{};
    int index{ 0 };

    while (std::getline(input, line))
    {
        linestream << line;
        linestream >> listA[index] >> listB[index];

        linestream.str("");
        linestream.clear();

        index++;
    }

    std::sort(std::begin(listA), std::end(listA));
    std::sort(std::begin(listB), std::end(listB));

    int totalDiff{ 0 };

    for (int i{ 0 }; i < count; i++)
    {
        totalDiff += abs(listA[i] - listB[i]);
    }

    std::cout << totalDiff << '\n';
}
