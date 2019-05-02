//
// Created by Danil on 01.05.2019.
//

#ifndef UNTITLED8_PYATNATSHKI_H

#include <cstdio>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

using std::vector;
using std::make_pair;

struct Board {
    Board();

    explicit Board(size_t);

    explicit Board(vector<vector<unsigned>> const &a);

    explicit Board(vector<vector<unsigned>> &&v);

    Board(Board const &a);

    Board &operator=(Board const &a);

    void swap(Board &a);

    Board &operator=(Board &&a) noexcept;

    bool is_goal() const;

    size_t size() const;

    unsigned hamming() const;

    unsigned manhattan() const;

    friend bool operator==(Board const &a, Board const &b);

    friend bool operator!=(Board const &a, Board const &b);

    friend bool operator<(Board const &a, Board const &b);

    vector<unsigned> &operator[](size_t i);

    vector<unsigned> const &operator[](size_t i) const;

    friend std::ostream &operator<<(std::ostream &out, Board const &a);

    std::string to_string() const;

    bool is_solvable() const;

    std::pair<size_t, size_t> get_zero() const;

    bool is_cords_in_field(int x, int y) const;

    void set_zero(int x, int y) {
        zero.first = x;
        zero.second = y;
    }

private:
    size_t length;
    vector<vector<unsigned>> data;
    std::pair<size_t, size_t> zero;

    std::string int_to_string(int a) const;

    std::pair<size_t, size_t> find_zero() const;


};

#define UNTITLED8_PYATNATSHKI_H

#endif //UNTITLED8_PYATNATSHKI_H
