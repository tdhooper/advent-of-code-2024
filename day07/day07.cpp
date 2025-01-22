#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <functional>

// TODO: Optimise

using OperatorFn = std::function<uint64_t(uint64_t&, uint64_t&)>;

static uint64_t solve(
    uint64_t &value,
    std::vector<uint64_t> &numbers,
    std::vector<OperatorFn> &operators
)
{
    // iterate all combinations of operators
    int numberCount = numbers.size();
    int ops = operators.size();
    int combinations = std::pow(ops, numberCount - 1);
    for (int c = 0; c < combinations; c++)
    {
        uint64_t candidateValue = numbers[0];

        for (int n = 1; n < numberCount; n++)
        {
            int stride = std::pow(ops, n - 1);
            int op = (c / stride) % ops;
            candidateValue = operators[op](candidateValue, numbers[n]);
        }

        if (candidateValue > value) {
            return 0;
        }

        if (candidateValue == value) {
            return value;
        }
    }
    return 0;
}

int main()
{
    std::ifstream input{ "input.txt" };

    std::string line{};

    uint64_t resultA{ 0 };
    uint64_t resultB{ 0 };

    OperatorFn addFn = [](uint64_t& a, uint64_t& b) -> uint64_t
        { return a + b; };
    OperatorFn mulFn = [](uint64_t& a, uint64_t& b) -> uint64_t
        { return a * b; };
    OperatorFn catFn = [](uint64_t& a, uint64_t& b) -> uint64_t
        { return std::stoull(std::to_string(a) + std::to_string(b)); };

    std::vector<OperatorFn> operatorsA = { addFn, mulFn };
    std::vector<OperatorFn> operatorsB = { addFn, mulFn, catFn };

    while (std::getline(input, line))
    {
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

        // solve
        resultA += solve(value, numbers, operatorsA);
        resultB += solve(value, numbers, operatorsB);
    }

    std::cout << resultA << '\n';
    std::cout << resultB << '\n';
}
