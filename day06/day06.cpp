#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <bitset>

enum Direction { up, right, down, left };

struct Tile {
    bool blocker{};
    std::bitset<4> visitedDirections{};
};

struct Guard {
    int x{};
    int y{};
    Direction direction{};
};

static void drawTiles(std::vector<Tile>& tiles, Guard &guard, size_t &width, size_t &height)
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
                else if (tile.visitedDirections.any())
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

struct PatrolResult {
    int visitedTiles;
    bool loops;
};

static PatrolResult patrolGuard(std::vector<Tile> &tiles, Guard &guard, size_t &width, size_t &height)
{
    int visitedTiles{ 0 };
    bool loops{ false };

    while (true)
    {
        int x = guard.x;
        int y = guard.y;

        //system("cls");
        //drawTiles(tiles, guard, width, height);

        Tile& tile = tiles[x + y * width];

        if (tile.visitedDirections.test(guard.direction))
        {
            loops = true;
            break;
        }

        if ( ! tile.visitedDirections.any())
        {
            visitedTiles++;
            tile.visitedDirections.set(guard.direction);
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

    PatrolResult result{};
    result.visitedTiles = visitedTiles;
    result.loops = loops;
    return result;
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

    std::vector<Tile> patrolledTiles = tiles;
    Guard patrolledGuard = guard;
    PatrolResult patrolledResult = patrolGuard(patrolledTiles, patrolledGuard, width, height);

    //drawTiles(patrolledTiles, patrolledGuard, width, height);

    int loopingObstructions{0};

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (patrolledTiles[x + y * width].visitedDirections.any()) {
                std::vector<Tile> obstructedTiles = tiles;
                obstructedTiles[x + y * width].blocker = true;
                Guard obstructedGuard = guard;
                PatrolResult obstructedResult = patrolGuard(obstructedTiles, obstructedGuard, width, height);
                if (obstructedResult.loops) {
                    loopingObstructions++;
                }
            }
        }
    }

    std::cout << patrolledResult.visitedTiles << "\n";
    std::cout << loopingObstructions << "\n";
}
