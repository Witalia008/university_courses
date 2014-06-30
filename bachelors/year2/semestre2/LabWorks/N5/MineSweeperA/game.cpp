
#include "game.h"

Game::Game()
{
    this->width = this->height = -1;
    mine_cnt = 0;
    is_running = false;
    is_finished = 0;
}

Game::Game(int width, int height, int minesNumber) {
    minesNumber = min(minesNumber, int(width * height / 1.1));
    this->width = width;
    this->height = height;
    this->mine_cnt = minesNumber;
    this->field.resize(width);
    for (auto &i : this->field)
        i.assign(height, CellType::Empty);
    this->state.resize(width);
    for (auto &i : this->state)
        i.assign(height, States::Untouched);
    is_running = is_finished = false;
}

void Game::setOnScreen(int screen_width, int screen_height) {
    this->screen_width = screen_width;
    this->screen_height = screen_height;
    this->cell_height = screen_height / this->height;
    this->cell_width = screen_width / this->width;
}

void Game::generateMines(int first_x, int first_y) {
    srand(time(NULL));
    set<pair<int, int>> used;
    used.insert(make_pair(first_x, first_y));
    for (int i = 0; i < this->mine_cnt; ++i) {
        int x, y;
        do {
            x = rand() % this->width;
            y = rand() % this->height;
        } while (used.find(make_pair(x, y)) != used.end());
        used.insert(make_pair(x, y));
    }
    for (auto i : used) {
        this->field[i.first][i.second] = CellType::Mine;
    }
    this->field[first_x][first_y] = CellType::Empty;
    this->calculateNumbers();
}

bool Game::isValidCell(int x, int y) {
    return x >= 0 && y >= 0 && x < width && y < height;
}

void Game::calculateNumbers() {
    for (int i = 0; i < this->width; ++i)
        for (int j = 0; j < this->height; ++j)
            if (this->field[i][j] != CellType::Mine) {
                int cur = 0;
                for (int dx = -1; dx < 2; ++dx)
                    for (int dy = -1; dy < 2; ++dy)
                        if ((dx || dy) && this->isValidCell(i + dx, j + dy)) {
                            cur += this->field[i + dx][j + dy] == CellType::Mine;
                        }
                this->field[i][j] = static_cast<CellType>(cur);
            }
}

pair<int, int> Game::getFieldCoord(int scr_x, int scr_y) {
    return make_pair(scr_x / this->cell_width, scr_y / this->cell_height);
}

bool Game::isMine(int x, int y) {
    return this->isValidCell(x, y) && this->field[x][y] == CellType::Mine;
}

int Game::getNumberOfMines() {
    return mine_cnt;
}

pair<int, int> Game::getCellSize() {
    return make_pair(cell_width, cell_height);
}

int Game::getNumberOnField(int x, int y) throw(exception){
    if (!this->isValidCell(x, y))
        throw exception();
    return static_cast<int>(this->field[x][y]);
}

vector<pair<int, int>> Game::getAllMines() {
    vector<pair<int, int>> res;
    for (int i = 0; i < this->width; ++i)
        for (int j = 0; j < this->height; ++j)
            if (this->isMine(i, j))
                res.push_back(make_pair(i, j));
    return res;
}

bool Game::isRunning() {
    return is_running;
}

int Game::isFinished() {
    return is_finished;
}

void Game::open(int x, int y) {
    if (!isValidCell(x, y) || state[x][y] != States::Untouched)
        return;
    if (getNumberOnField(x, y) < 0 || getNumberOnField(x, y) > 8)
        return;
    state[x][y] = States::Opened;
    if (field[x][y] == CellType::Empty) {
        for (int dx = -1; dx < 2; ++dx)
            for (int dy = -1; dy < 2; ++dy)
                open(x + dx, y + dy);
    }
}

bool Game::isEnd() {
    if (isFinished())
        return false;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            if (state[i][j] != States::Opened && field[i][j] != CellType::Mine)
                return false;
        }
    }
    return true;
}

void Game::click(int x, int y, int mode) {
    if (!isValidCell(x, y) || isFinished())
        return;
    if (!isRunning()) {
        if (mode == 0) return;
        is_running = true;
        generateMines(x, y);
        open(x, y);
    }
    if (state[x][y] == States::Opened) {
        autoOpen(x, y);
        return;
    }
    if (state[x][y] == States::Untouched) {
        if (mode == 0) {
            if (mine_cnt > 0) {
                state[x][y] = States::Flagged;
                --mine_cnt;
            }
        } else {
            if (isMine(x, y)) {
                is_finished = 2;
                auto X = getAllMines();
                for (auto i : X)
                    if (state[i.first][i.second] != States::Flagged)
                        state[i.first][i.second] = States::Opened;
                field[x][y] = CellType::BrokenMine;
            } else {
                open(x, y);
            }
        }
        if (isEnd())
            is_finished = 1;
        if (is_finished == 1) {
            for (int i = 0; i < width; ++i)
                for (int j = 0; j < height; ++j)
                    if (state[i][j] == States::Untouched)
                        state[i][j] = States::Flagged;
        }
    } else if (state[x][y] == States::Flagged && mode == 0) {
        state[x][y] = States::Untouched;
        ++mine_cnt;
    }
}

void Game::autoOpen(int x, int y) {
    if (!isValidCell(x, y) || isFinished())
        return;
    if (state[x][y] != States::Opened)
        return;
    int cur_cell = getNumberOnField(x, y);
    for (int dx = -1; dx < 2; ++dx)
        for (int dy = -1; dy < 2; ++dy)
            if (isValidCell(x + dx, y + dy)) {
                cur_cell -= state[x + dx][y + dy] == States::Flagged;
            }
    if (!cur_cell) {
        for (int dx = -1; dx < 2; ++dx)
            for (int dy = -1; dy < 2; ++dy)
                if (isValidCell(x + dx, y + dy) && state[x + dx][y + dy] != States::Opened)
                    click(x + dx, y + dy, 1);
    }
}

