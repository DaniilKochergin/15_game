//
// Created by Danil on 02.05.2019.
//

#include <iostream>
#include "Solver.h"

Solver::Solver(Board const &a) {
    if (!a.is_solvable()) {
        throw std::runtime_error("Make class Solver from unsolvable board");
    }
    start = a;
    solve();
}

Solver::Solver(Solver const &a) {
    data = a.data;
}

void Solver::swap(Solver &a) {
    std::swap(data, a.data);
}

Solver &Solver::operator=(Solver &&a) noexcept {
    swap(a);
    return *this;
}

Solver::Solver(Solver &&a) noexcept {
    swap(a);
}


bool operator<(const std::pair<size_t, Board> &a, const std::pair<size_t, Board> &b) {
    return a.first > b.first;
}

void Solver::solve() {
    std::priority_queue<std::pair<size_t, Board>> q;
    q.push({0, start});
    while (true) {
        size_t sum = q.top().first;
        Board v = q.top().second;
        q.pop();
        if (is_goal(v)) {
            answer_recovery(v);
            return;
        }
        vector<Board> next_steps = get_next_steps(v);
        for (size_t i = 0; i < next_steps.size(); ++i) {
            auto it = vertex.find(next_steps[i]);
            size_t d = next_steps[i].manhattan() + next_steps[i].hamming();
            if ((it != vertex.end() && (it->second > sum + d)) || it == vertex.end()) {
                q.push(make_pair(sum + d, next_steps[i]));
                vertex[v] = sum;
                parent[next_steps[i]] = v;
            }
        }
    }

}

bool Solver::is_goal(Board const &a) const {
    for (size_t i = 0; i < a.size() * a.size() - 1; ++i) {
        if (a[i / a.size()][i % a.size()] != i + 1) return false;
    }
    return a[a.size() - 1][a.size() - 1] == 0;
}

vector<Board> Solver::get_next_steps(Board const &a) const {
    std::pair<int, int> zero = a.get_zero();
    vector<Board> next_steps;
    for (size_t i = 0; i < transitions.size(); ++i) {
        int x = zero.first + transitions[i].first;
        int y = zero.second + transitions[i].second;
        if (a.is_cords_in_field(x, y)) {
            Board b = a;
            std::swap(b[zero.first][zero.second], b[x][y]);
            b.set_zero(x, y);
            next_steps.push_back(b);
        }
    }
    return next_steps;
}

void Solver::answer_recovery(Board const &v) {
    data.push_back(v);
    if (start == v) {
        return;
    }

    answer_recovery(parent[v]);
}

size_t Solver::VertexSetHashFunction::operator()(Board const &a) const {
    size_t res = 0;
    size_t power_of_p = 1;
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a.size(); ++j) {
            power_of_p *= p;
            res += power_of_p * a[i][j];
        }
    }
    return res;
}

bool Solver::SetEqual::operator()(Board const &a, Board const &b) const {
    if (a.size() == b.size()) {
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a.size(); ++j) {
                if (a[i][j] != b[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

