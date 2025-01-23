// day08.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

struct Antenna
{
    int x{};
    int y{};
}; 

int main()
{
    std::ifstream input{ "input.txt" };

    std::string line{};

    int width{0};
    int height{0};

    std::map<char, std::vector<Antenna>> antennaGroups{};

    while (std::getline(input, line))
    {
        width = line.length();
        for (int i = 0; i < width; i++)
        {
            char value = line[i];
            if (value != '.')
            {
                Antenna antenna{};
                antenna.x = i;
                antenna.y = height;
                antennaGroups[value].push_back(antenna);
            }
        }
        height++;
    }

    std::vector<bool> antinodeMap(width * height);

    int result{ 0 };

    auto recordAntinode = [&](Antenna& a, Antenna& b) {
        int xo = b.x - a.x;
        int yo = b.y - a.y;
        int x = a.x;
        int y = a.y;
        while (x < width && x >= 0 && y < height && y >= 0)
        {
            size_t index = x + y * width;
            if (!antinodeMap[index])
            {
                antinodeMap[index] = true;
                result++;
            }
            x += xo;
            y += yo;
        }
    };

    for (auto &antennaGroup : antennaGroups)
    {
        for (auto& antennaA : antennaGroup.second)
        {
            for (auto& antennaB : antennaGroup.second)
            {
                if (&antennaA != &antennaB) {
                    recordAntinode(antennaA, antennaB);
                    recordAntinode(antennaB, antennaA);
                }
            }
        }
    }

    std::cout << result << "\n";
}
