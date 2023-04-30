//
// Created by Evan Semet on 12/2/22.
//

#ifndef DIE_AGONY_CPP
#define DIE_AGONY_CPP

#include "die_agony.h"

void DieAgony::printPath(const std::vector<int> &path) const {
    std::cout << "Path:\n";
    for (uint32_t i = 0; i < path.size() - 1; ++i) std::cout << path[i] << " -> ";
    std::cout << path[path.size() - 1] << "\n\n";
}

void DieAgony::printDie(std::map<std::string, int> &die) const {
    std::cout << "Die Sides:\n";
    std::cout << die["top"] << ", " << die["bottom"] << ", " << die["left"] << ", " << die["right"] << ", " <<
              die["front"] << ", " << die["back"] << "\n\n";
}

std::map<std::string, int> DieAgony::rotateUp(std::map<std::string, int> &die) const {
    std::map<std::string, int> up;
    if (die["front"]) up["top"] = die["front"];
    if (die["bottom"]) up["front"] = die["bottom"];
    if (die["back"]) up["bottom"] = die["back"];
    if (die["top"]) up["back"] = die["top"];
    if (die["left"]) up["left"] = die["left"];
    if (die["right"]) up["right"] = die["right"];
    return up;
}

std::map<std::string, int> DieAgony::rotateDown(std::map<std::string, int> &die) const {
    std::map<std::string, int> down;
    if (die["back"]) down["top"] = die["back"];
    if (die["top"]) down["front"] = die["top"];
    if (die["front"]) down["bottom"] = die["front"];
    if (die["bottom"]) down["back"] = die["bottom"];
    if (die["left"]) down["left"] = die["left"];
    if (die["right"]) down["right"] = die["right"];
    return down;
}

std::map<std::string, int> DieAgony::rotateLeft(std::map<std::string, int> &die) const {
    std::map<std::string, int> left;
    if (die["right"]) left["top"] = die["right"];
    if (die["front"]) left["front"] = die["front"];
    if (die["left"]) left["bottom"] = die["left"];
    if (die["back"]) left["back"] = die["back"];
    if (die["top"]) left["left"] = die["top"];
    if (die["bottom"]) left["right"] = die["bottom"];
    return left;
}

std::map<std::string, int> DieAgony::rotateRight(std::map<std::string, int> &die) const {
    std::map<std::string, int> right;
    if (die["left"]) right["top"] = die["left"];
    if (die["front"]) right["front"] = die["front"];
    if (die["right"]) right["bottom"] = die["right"];
    if (die["back"]) right["back"] = die["back"];
    if (die["bottom"]) right["left"] = die["bottom"];
    if (die["top"]) right["right"] = die["top"];
    return right;
}

bool DieAgony::inRange(const int &row, const int &col) const {
    return row >= 0 && row <= 5 && col >= 0 && col <= 5;
}

int DieAgony::answer(const std::vector<int> &path, const std::vector<std::vector<int>> &seen) const {
    int total = 0;
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j)
            if (!seen[i][j]) total += board[i][j];
    }
    return total;
}

void DieAgony::solve(std::vector<int> current_path, std::map<std::string, int> potential_die, int row, int col,
                     int move, std::vector<std::vector<int>> seen) {
    // Case when we reach the final square
    if (row == 0 && col == 5) {
        int value = board[row][col];
        // Off case that this side still hasn't been labeled
        if (!potential_die["top"])
            potential_die["top"] = (value - current_path[current_path.size() - 1]) / move;
        // Make sure it was able to make the final move
        if ((value - current_path[current_path.size() - 1]) - move * potential_die["top"] == 0) {
            ++seen[row][col];
            current_path.push_back(value);
            // Print out everything
            printPath(current_path);
            printDie(potential_die);
            std::cout << "Answer is: " << answer(current_path, seen) << "\n";
        }
        // Check to see if in range
    } else if (inRange(row, col)) {
        int value = board[row][col];
        // See if this side of the die hasn't been labeled yet
        if (!potential_die["top"])
            potential_die["top"] = (value - current_path[current_path.size() - 1]) / move;
        // Make sure label on die matches what it needs to be for this move
        if ((value - current_path[current_path.size() - 1]) - move * potential_die["top"] == 0) {
            ++seen[row][col];
            current_path.push_back(value);
            ++move;
            std::map<std::string, int> up = rotateUp(potential_die);
            solve(current_path, up, row - 1, col, move, seen);
            std::map<std::string, int> down = rotateDown(potential_die);
            solve(current_path, down, row + 1, col, move, seen);
            std::map<std::string, int> left = rotateLeft(potential_die);
            solve(current_path, left, row, col - 1, move, seen);
            std::map<std::string, int> right = rotateRight(potential_die);
            solve(current_path, right, row, col + 1, move, seen);
        }
    }
}

#endif // DIE_AGONY_CPP