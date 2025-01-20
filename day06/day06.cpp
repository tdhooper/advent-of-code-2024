#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>

struct Tile {
    bool blocker{};
    bool visited{};
};

enum Direction { up, right, down, left };

struct Guard {
    int x{};
    int y{};
    Direction direction{};
};

void drawTiles(std::vector<Tile>& tiles, Guard &guard, size_t &width, size_t &height)
{
    std::stringstream screen{};
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (guard.x == x && guard.y == y)
            {
                screen << "^>v<"[guard.direction];
            }
            else
            {
                Tile tile = tiles[x + y * width];
                if (tile.blocker) {
                    screen << "#";
                }
                else if (tile.visited)
                {
                    screen << "X";
                }
                else
                {
                    screen << ".";
                }
            }

        }
        screen << "\n";
    }
    screen << "\n";

    std::cout << screen.str();
}

int main()
{
    std::ifstream input{ "input.txt" };
    std::stringstream inputstream{};
    inputstream << input.rdbuf();
    std::string inputstring = inputstream.str();

    size_t width = inputstring.find("\n");
    size_t height = inputstring.length() / (width + 1);

    std::vector<Tile> tiles(width * height);

    Guard guard;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            char value = inputstring[x + y * (width + 1)];
            tiles[x + y * width].blocker = value == '#';
            if (value == '^') {
                guard.x = x;
                guard.y = y;
                guard.direction = up;
            }
        }
    }

    int totalVisited{0};
 
    while (true)
    {
        int x = guard.x;
        int y = guard.y;

        //system("cls");
        //drawTiles(tiles, guard, width, height);

        Tile &tile = tiles[x + y * width];

        if ( ! tile.visited) {
            totalVisited++;
            tile.visited = true;
        }

        switch (guard.direction)
        {
            case up:
                y--;
                break;
            case down:
                y++;
                break;
            case left:
                x--;
                break;
            case right:
                x++;
                break;
        }

        if (x < 0 || y < 0 || x >= width || y >= height)
        {
            break;
        }

        if (tiles[x + y * width].blocker) {
            guard.direction = Direction((guard.direction + 1) % 4);
        }
        else
        {
            guard.x = x;
            guard.y = y;
        }
    }

    std::cout << totalVisited << "\n";
}
