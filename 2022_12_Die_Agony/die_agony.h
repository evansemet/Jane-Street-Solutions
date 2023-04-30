//
// Created by Evan Semet on 12/2/22.
//

#ifndef DIE_AGONY_H
#define DIE_AGONY_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

class DieAgony {
public:
    /**
     * function to print out the path of the die
     * @param path the values of the places that the die visited
     */
    void printPath(const std::vector<int> &path) const;

    /**
     * function to print out the die
     * @param die the current layout of the die
     */
    void printDie(std::map<std::string, int> &die) const;

    /**
     * function that rotates the die "up"
     * @param die the current layout of the die
     * @return a new map that is the die passed rotated up
     */
    std::map<std::string, int> rotateUp(std::map<std::string, int> &die) const;

    /**
     * function that rotates the die "down"
     * @param die the current layout of the die
     * @return a new map that is the die passed rotated down
     */
    std::map<std::string, int> rotateDown(std::map<std::string, int> &die) const;

    /**
     * funciton that rotates the die "left"
     * @param die the current layout of the die
     * @return a new map that is the die passed rotated left
     */
    std::map<std::string, int> rotateLeft(std::map<std::string, int> &die) const;

    /**
     * function that rotates the die "right"
     * @param die the current layout of the die
     * @return a new map that is the die passed rotated right
     */
    std::map<std::string, int> rotateRight(std::map<std::string, int> &die) const;

    /**
     * determines if a position is in the bounds of the board
     * @param row the row of the position
     * @param col the column of the position
     * @return a bool representing whether the row and col positions is valid for the board
     */
    bool inRange(const int &row, const int &col) const;

    /**
     * calculates the answer to the puzzle given the path from solve
     * @param path the values of the places that the die visited
     * @param seen the places that the die visited
     * @return the answer to the puzzle
     */
    int answer(const std::vector<int> &path, const std::vector<std::vector<int>> &seen) const;

    /**
     * function to solve the problem via DFS
     * @param current_path the current path that the die has taken
     * @param potential_die the die with numbers needed to get to point it's at currently
     * @param row the current row
     * @param col the current column
     * @param move the move number
     * @param seen 2D vector keeping track of places visited
     */
    void solve(std::vector<int> current_path, std::map<std::string, int> potential_die, int row, int col,
               int move, std::vector<std::vector<int>> seen);

private:
    // board given
    const std::vector<std::vector<int>> board = {{57,  33,  132, 268, 492, 732},
                                                 {81,  123, 240, 443, 353, 508},
                                                 {186, 42,  195, 704, 452, 228},
                                                 {-7,  2,   357, 452, 317, 395},
                                                 {5,   23,  -4,  592, 445, 620},
                                                 {0,   77,  32,  403, 337, 452}};
};

#endif // DIE_AGONY_H