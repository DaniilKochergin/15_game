//
// Created by Danil on 02.05.2019.
//

#ifndef UNTITLED8_SOLVER_H
#define UNTITLED8_SOLVER_H

#include "Board.h"
#include <stdexcept>
#include <unordered_map>
#include <queue>

using std::vector;

struct Solver {
    Solver() = default;

    explicit Solver(Board const &a);

    Solver &operator=(Solver const &a) = default;

    Solver &operator=(Solver &&a) noexcept;

    Solver(Solver const &a);

    Solver(Solver &&a) noexcept;

    void swap(Solver &a);

    vector<Board> data;
    Board start;
    vector<std::pair<int, int>> transitions = {{0,  1},
                                               {1,  0},
                                               {-1, 0},
                                               {0,  -1}};

    void solve();

    struct VertexSetHashFunction {
        size_t operator()(Board const &board) const;

    private:
        const size_t p = 31;
    };

    struct SetEqual {
        bool operator()(Board const &a, Board const &b) const;
    };

    vector<Board> get_next_steps(Board const &a) const;

    std::unordered_map<Board, Board, VertexSetHashFunction, SetEqual> parent;

    void answer_recovery(Board const &v);

    std::unordered_map<Board, size_t, VertexSetHashFunction, SetEqual> vertex;

    bool is_goal(Board const &a) const;

};


#endif //UNTITLED8_SOLVER_H
