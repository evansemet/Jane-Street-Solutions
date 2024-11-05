#include <array>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <optional>
#include <thread>

const int SIZE = 6;
const int TARGET_SCORE = 2024;

const std::array<std::array<u_int8_t, SIZE>, SIZE> grid = {
    {
        {0, 1, 1, 2, 2, 2},
        {0, 1, 1, 2, 2, 2},
        {0, 0, 1, 1, 2, 2},
        {0, 0, 1, 1, 2, 2},
        {0, 0, 0, 1, 1, 2},
        {0, 0, 0, 1, 1, 2}
    }
};

struct ABC {
    int a;
    int b;
    int c;

    friend std::ostream& operator<<(std::ostream& os, const ABC& abc) {
        os << abc.a << "," << abc.b << "," << abc.c;
        return os;
    }
};

struct Point {
    int i;
    int j;

    bool inRange() const {
        return (i >= 0 && i < SIZE) && (j >= 0 && j < SIZE);
    }

    bool operator==(const Point& other) const {
        return (i == other.i) && (j == other.j);
    }

    Point operator+(const Point& other) const {
        return Point{i + other.i, j + other.j};
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "," << "abcdef"[point.j] << 6 - point.i;
        return os;
    }
};

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& point) const {
            return point.i * 6 + point.j;
        }
    };
}

struct Score {
    int score;
    Point point;
    std::vector<Point> path;
};

std::array<Point, 8> knight_moves = {
    {Point{-2, -1}, Point{-2, 1}, Point{-1, -2}, Point{-1, 2}, Point{1, -2}, Point{1, 2}, Point{2, -1}, Point{2, 1}}
};

std::vector<Point> valid_moves(const Point& point) {
    std::vector<Point> moves;
    moves.reserve(8);
    for (Point move : knight_moves) {
        Point new_point = point + move;
        if (new_point.inRange()) moves.emplace_back(new_point);
    }
    return moves;
}

int value(const ABC& abc, const Point& point) {
    switch (grid[point.i][point.j]) {
        case 0: return abc.a;
        case 1: return abc.b;
        default: return abc.c;
    }
}

Score change_score(const ABC& abc, Score score, const Point& point) {
    int val = value(abc, point);
    score.score = (val == value(abc, score.point)) ? (score.score + val) : (score.score * val);
    score.point = point;
    return score;
}

std::optional<std::vector<Point>> valid_path_found(const ABC& abc, Point current, const Point& end, Score score, std::unordered_set<Point> visited, std::vector<Point> path) {
    if (current == end && score.score == TARGET_SCORE) return path;
    else if (score.score >= TARGET_SCORE) return std::nullopt;

    for (Point move : valid_moves(current)) {
        if (visited.find(move) == visited.end()) {
            visited.insert(move);
            Score new_score = change_score(abc, score, move);
            path.push_back(move);
            auto result = valid_path_found(abc, move, end, new_score, visited, path);
            if (result.has_value()) return result;
            visited.erase(move);
            path.pop_back();
        }
    }
    return std::nullopt;
}

void knight_moves_6() {
    Point bottom_left = Point{SIZE-1, 0};
    Point top_right = Point{0, SIZE-1};
    Point top_left = Point{0, 0};
    Point bottom_right = Point{SIZE-1, SIZE-1};
    ABC abc = ABC{3, 2, 1};

    std::unordered_set<Point> visited;
    visited.reserve(36);
    visited.insert(bottom_left);
    std::vector<Point> path;
    path.reserve(36);
    path.push_back(bottom_left);
    auto bottom_left_result = valid_path_found(abc, bottom_left, top_right, Score{abc.a, bottom_left, {bottom_left}}, visited, path);
    if (bottom_left_result.has_value()) {
        visited.clear();
        visited.insert(top_left);
        path.clear();
        path.push_back(top_left);
        auto top_left_result = valid_path_found(abc, top_left, bottom_right, Score{abc.a, top_left, {top_left}}, visited, path);
        if (top_left_result.has_value()) {
            std::cout << "Found a valid path!" << std::endl;
            std::cout << abc;
            for (const Point& point : *bottom_left_result) std::cout << point;
            for (const Point& point : *top_left_result) std::cout << point;
            std::cout << std::endl;
            return;
        }
    }
    std::cout << "No valid paths found." << std::endl;
}

int main() {
    std::cout << "Starting search..." << std::endl;
    knight_moves_6();
    return 0;
}
