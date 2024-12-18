#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

static void getWindow(std::ifstream& input, std::string& window, int location, int windowSize, int lineLength, int characterCount)
{
    char value{ 0 };
    int readOffset{ 0 };
    int writeOffset{ 0 };

    window.assign(window.length(), '\0');

    for (int y{ 0 }; y < windowSize; y++) {
        for (int x{ 0 }; x < windowSize; x++) {
            readOffset = location + (lineLength + 1) * y + x;
            if (readOffset >= characterCount)
            {
                return;
            }
            input.seekg(readOffset, std::ios::beg);
            input.get(value);
            if (value != '\n')
            {
                writeOffset = y * windowSize + x;
                window[writeOffset] = value;
            }
            else
            {
                break;
            }
        }
    }
}

static int matchWordinWindow(std::string_view word, std::string_view window, int offset, int stride, bool forwards)
{
    int iWord{ 0 };
    int iWindow{ 0 };
    int wordSize = word.size();

    for (int i{ 0 }; i < wordSize; ++i)
    {
        iWord = forwards ? i : wordSize - i - 1;
        iWindow = offset + i * stride;
        if (word[iWord] != window[iWindow]) {
            return 0;
        }
    }
    return 1;
}

static int countWordsInWindow(std::string_view word, std::string_view window, int windowSize)
{
    int result{ 0 };
    result += matchWordinWindow(word, window, 0, 1, true);
    result += matchWordinWindow(word, window, 0, 1, false);
    result += matchWordinWindow(word, window, 0, windowSize, true);
    result += matchWordinWindow(word, window, 0, windowSize, false);
    result += matchWordinWindow(word, window, 0, windowSize + 1, true);
    result += matchWordinWindow(word, window, 0, windowSize + 1, false);
    result += matchWordinWindow(word, window, windowSize - 1, windowSize - 1, true);
    result += matchWordinWindow(word, window, windowSize - 1, windowSize - 1, false);
    return result;
}

static int countWordsInWindow2(std::string_view word, std::string_view window, int windowSize)
{
    int result{ 0 };
    result += matchWordinWindow(word, window, 0, windowSize + 1, true);
    result += matchWordinWindow(word, window, 0, windowSize + 1, false);
    result += matchWordinWindow(word, window, windowSize - 1, windowSize - 1, true);
    result += matchWordinWindow(word, window, windowSize - 1, windowSize - 1, false);
    return result / 2;
}

int main()
{
    std::ifstream input{ "input.txt" };

    if (!input)
    {
        std::cerr << "Cannot open file input.txt";
        return 1;
    }

    std::string word{ "XMAS" };
    int windowSize{ 0 };
    windowSize = word.length();

    std::string line{};
    std::getline(input, line);
    int lineLength = line.length();

    input.seekg(0, std::ios::end);
    int characterCount = input.tellg();

    std::string window(windowSize * windowSize, '\0');

    int count{ 0 };
    int wordsInWindow{ 0 };

    for (int i{ 0 }; i < characterCount; ++i)
    {
        getWindow(input, window, i, windowSize, lineLength, characterCount);
        wordsInWindow = countWordsInWindow(word, window, windowSize);
        count += wordsInWindow;
    }

    std::cout << count << '\n';

    word = "MAS";
    windowSize = word.length();
    window.resize(windowSize * windowSize);
    count = 0;

    for (int i{ 0 }; i < characterCount; ++i)
    {
        getWindow(input, window, i, windowSize, lineLength, characterCount);
        wordsInWindow = countWordsInWindow2(word, window, windowSize);
        count += wordsInWindow;
    }

    std::cout << count << '\n';
}
