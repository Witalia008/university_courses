#ifndef GAME_H
#define GAME_H

#include <vector>
#include <tuple>
#include <set>
#include <exception>
#include <iostream>
#include <stdio.h>
#include <random>
#include <time.h>

using namespace std;

class Game
{
public:
    enum class States{Untouched, Flagged, Opened};
    enum class CellType:int{BrokenMine = -2, Mine, Empty, One, Two, Three, Four, Five, Six, Seven, Eight, Nine};

protected:
    vector<vector<CellType>> field;
    vector<vector<States>> state;
    int width;
    int height;
    int mine_cnt;
    int screen_width;
    int screen_height;
    int cell_width;
    int cell_height;
    bool is_running;
    int is_finished;

    void calculateNumbers();
    bool isValidCell(int, int);
public:
    Game();
    Game(int, int, int);
    void generateMines(int, int);
    void setOnScreen(int, int);
    pair<int, int> getFieldCoord(int, int);

    bool isMine(int, int);
    int getNumberOnField(int, int) throw(exception);
    int getNumberOfMines();
    auto getAllMines() -> vector<pair<int, int>>;
    pair<int, int> getCellSize();
    bool isRunning();
    int isFinished();
    bool isEnd();
    void click(int, int, int);
    void open(int, int);
    int Width() { return width; }
    int Height() { return height; }
    States getState(int x, int y) { return state[x][y]; }
    int getMinesCnt() { return mine_cnt; }
    void autoOpen(int, int);
};

#endif // GAME_H
