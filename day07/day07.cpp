#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

int main()
{
    std::ifstream input{ "input.txt" };

    std::string line{};

    uint64_t result{ 0 };

    while (std::getline(input, line))
    {

        //std::cout << line << "\n";

        // read desired value
        std::istringstream linestream(line);
        std::uint64_t value{};
        linestream >> value;

        // skip the : character
        linestream.seekg(1, std::ios::cur);

        // read the rest of the numbers
        std::vector<uint64_t> numbers{};
        uint64_t number{};
        while (linestream >> number)
        {
            numbers.push_back(number);
        }

        // iterate operator combinations in the pattern:
        //  n 0 1 2
        // c
        // 0  0 0 0
        // 1  1 0 0
        // 2  0 1 0
        // 3  1 1 0
        // 4  0 0 1
        // 5  1 0 1
        // 6  0 1 1
        // 7  1 1 1

        int numberCount = numbers.size();
        int combinations = std::pow(2, numberCount - 1);
        for (int c = 0; c < combinations; c++)
        {
            //std::cout << "combination: " << c << "\n";

            uint64_t candidateValue = numbers[0];

            for (int n = 1; n < numberCount; n++)
            {

                int stride = std::pow(2, n - 1);
                int op = (c / stride) % 2;

                if (op)
                {
                    //std::cout << candidateValue << " * " << numbers[n];
                    candidateValue *= numbers[n];
                }
                else
                {
                    //std::cout << candidateValue << " + " << numbers[n];
                    candidateValue += numbers[n];
                }

                //std::cout << " = " << candidateValue << '\n';
            }


            // check combination
            if (candidateValue == value) {
                //std::cout << result << " + " << value << '\n';
                result += value;
                break;
            }
        }
    }

    std::cout << result << '\n';
}
