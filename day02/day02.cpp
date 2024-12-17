#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

bool reportIsSafe(std::string line)
{
    std::stringstream linestream{};
    int lastvalue{ 0 };
    int value{ 0 };
    int index;
    bool increasing;

    linestream << line;
    index = 0;
    while (linestream >> value)
    {
        if (index > 0 && (abs(value - lastvalue) > 3 || value == lastvalue)) {
            return false;
        }
        if (index == 1) {
            increasing = value > lastvalue;
        }
        if (index > 1) {
            if (increasing != value > lastvalue) {
                return false;
            }
        }
        index++;
        lastvalue = value;
    }

    return true;
}

int main()
{
    std::ifstream input{ "input.txt" };

    if (!input)
    {
        std::cerr << "Cannot open file input.txt";
        return 1;
    }

    int safeReports{ 0 };
    std::string line{};

    while (std::getline(input, line))
    {
        if (reportIsSafe(line)) {
            safeReports++;
        }
    }

    std::cout << safeReports << '\n';
}
