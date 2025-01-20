#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>


struct Rule
{
    int first{};
    int second{};
};

static bool passesRule(std::vector<int>& pages, Rule& rule)
{
    std::string segment{ };
    int page{ };
    int firstIndex{ 0 };
    int secondIndex{ INT_MAX };
    int index{ 0 };
    for (int& page : pages)
    {
        if (page == rule.first)
        {
            firstIndex = index;
        }
        if (page == rule.second)
        {
            secondIndex = index;
        }
        index++;
    }
    return firstIndex <= secondIndex;
}

static bool passesRules(std::vector<int>& pages, std::vector<Rule>& rules)
{
    for (Rule& rule : rules)
    {
        if (!passesRule(pages, rule))
        {
            return false;
        }
    }
    return true;
}

static bool compareRules(std::vector<Rule>& rules, const int& pageA, const int& pageB)
{
    for (Rule& rule : rules)
    {
        if (rule.first == pageA && rule.second == pageB)
        {
            return true;
        }
        if (rule.first == pageB && rule.second == pageA)
        {
            return false;
        }
    }
    return true;
}

static void sortByRules(std::vector<int>& pages, std::vector<Rule>& rules) {
    using namespace std::placeholders;
    auto cmpRules = std::bind(compareRules, rules, _1, _2);
    std::sort(std::begin(pages), std::end(pages), cmpRules);
}

int main()
{
    std::ifstream input{ "input.txt" };

    if (!input)
    {
        std::cerr << "Cannot open file input.txt";
        return 1;
    }

    std::vector<Rule> rules{ };

    std::string line{};
    std::stringstream lineStream{};
    std::string segment{};

    int count{ 0 };

    while (std::getline(input, line))
    {
        if (line.empty())
        {
            break;
        }

        lineStream.clear();
        lineStream.str(line);

        Rule rule{};

        std::getline(lineStream, segment, '|');
        rule.first = std::stoi(segment);

        std::getline(lineStream, segment, '|');
        rule.second = std::stoi(segment);

        rules.push_back(rule);        
    }

    int page{ };
    int resultA{ 0 };
    int resultB{ 0 };

    while (std::getline(input, line))
    {
        lineStream.clear();
        lineStream.str(line);

        std::vector<int> pages{ };

        while (std::getline(lineStream, segment, ','))
        {
            page = std::stoi(segment);
            pages.push_back(page);
        }

        if (passesRules(pages, rules))
        {
            resultA += pages[pages.size() / 2];
        }
        else
        {
            sortByRules(pages, rules);
            resultB += pages[pages.size() / 2];
        }
    }

    std::cout << resultA << '\n';
    std::cout << resultB << '\n';
}
