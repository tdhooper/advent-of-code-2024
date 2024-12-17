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

bool reportIsSafeWithSafeguards(std::string line)
{
    std::stringstream linestream{};
    int lastValue{ 0 };
    int value{ 0 };
    int index{ 0 };
    int loopindex{ 0 };
    bool increasing{ false };
    bool lastIncreasing{ false };
    int skipIndex{ -1 };

    while(true)
    {
        linestream.str("");
        linestream.clear();
        linestream << line;

        loopindex = -1;
        index = 0;

        while (linestream >> value)
        {
            loopindex++;
            if (loopindex == skipIndex)
            {
                continue;
            }
            if (index > 0)
            {
                if (abs(value - lastValue) > 3 || value == lastValue)
                {
                    goto nextPermutation;
                }
                increasing = value > lastValue;
            }
            if (index > 1 && increasing != lastIncreasing)
            {
                goto nextPermutation;
            }
            index++;
            lastValue = value;
            lastIncreasing = increasing;
        }

        return true;

        nextPermutation:;
        if (skipIndex > -1)
        {
            if (skipIndex == 0)
            {
                return false;
            }
            skipIndex--;
        }
        else
        {
            skipIndex = index;
        }
    }
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
        if (reportIsSafe(line))
        {
            safeReports++;
        }
    }

    std::cout << "Safe reports: " << safeReports << '\n';

    input.clear();
    input.seekg(0);

    safeReports = 0;

    while (std::getline(input, line))
    {
        if (reportIsSafeWithSafeguards(line))
        {
            safeReports++;
        }
    }

    std::cout << "Safe reports with safeguards: " << safeReports << '\n';
}
