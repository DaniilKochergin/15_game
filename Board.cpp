
//
// Created by Danil on 01.05.2019.
//

#include "Board.h"

Board::Board() {
    length = 0;
}

Board::Board(size_t length) {
    data.resize(length, vector<unsigned>(length));
    this->length = length;
    vector<int> v(length * length);
    for (size_t i = 0; i < v.size(); ++i) {
        v[i] = i;
    }
    std::shuffle(v.begin(), v.end(), std::mt19937(std::random_device()()));
    for (size_t i = 0; i < length * length; ++i) {
        data[i / length][i % length] = v[i];
        if (v[i] == 0) {
            zero = make_pair(i / length, i % length);
        }
    }
}


Board::Board(Board const &a) {
    data = a.data;
    length = a.length;
    zero = a.zero;
}

std::pair<size_t, size_t> Board::find_zero() const {
    int x = 0, y = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (data[i][j] == 0) {
                x = i;
                y = j;
            }
        }
    }
    return make_pair(x, y);
}

Board::Board(vector<vector<unsigned>> &&v) {
    std::swap(data, v);
    length = data.size();
    zero = find_zero();

}

Board::Board(vector<vector<unsigned>> const &v) {
    data = v;
    length = v.size();
    zero = find_zero();
}

Board &Board::operator=(Board const &a) {
    data = a.data;
    length = a.size();
    zero = a.zero;
    return *this;
}

void Board::swap(Board &a) {
    std::swap(data, a.data);
    std::swap(length, a.length);
    std::swap(zero, a.zero);
}

Board &Board::operator=(Board &&a) noexcept {
    swap(a);
    return *this;
}


size_t Board::size() const {
    return length;
}

unsigned Board::hamming() const {
    unsigned res = 0;
    res += (data[length - 1][length - 1] != 0);
    for (int i = 0; i < length * length - 1; ++i) {
        res += (data[i / length][i % length] != i + 1);
    }
    return res;
}

bool Board::is_goal() const {
    if (zero.first == zero.second && zero.first == length - 1) {
        for (size_t i = 0; i < length * length - 1; ++i) {
            if (i + 1 != data[i / length][i % length]) return false;
        }
        return true;
    }
    return false;
}

unsigned Board::manhattan() const {
    unsigned res = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (data[i][j] != 0) {
                res += abs(i - static_cast<int>((data[i][j] - 1) / length)) +
                       abs(j - static_cast<int>((data[i][j] - 1) % length));
            } else {
                res += abs(i - static_cast<int>(length - 1)) + abs(j - static_cast<int>(length - 11));
            }
        }
    }
    return res;
}

bool operator==(Board const &a, Board const &b) {
    return a.data == b.data;
}

bool operator!=(Board const &a, Board const &b) {
    return !(a == b);
}

vector<unsigned> &Board::operator[](size_t i) {
    return data[i];
}

vector<unsigned> const &Board::operator[](size_t i) const {
    return data[i];
}

std::ostream &operator<<(std::ostream &out, Board const &a) {
    out << a.to_string();
    return out;
}

std::string Board::int_to_string(int a) const {
    std::string s;
    if (a == 0) {
        s.push_back('0');
    }
    while (a > 0) {
        s.push_back(a % 10 + '0');
        a /= 10;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

std::string Board::to_string() const {
    std::string s;
    for (size_t i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            s += this->int_to_string(data[i][j]);
            s.push_back(' ');
        }
        s.pop_back();
        s.push_back('\n');
    }
    return s;
}

bool Board::is_solvable() const {
    vector<unsigned> v;
    for (size_t i = 0; i < length; ++i) {
        for (size_t j = 0; j < length; ++j) {
            v.push_back(data[i][j]);
        }
    }
    unsigned inv = 0;
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] != 0) {
            for (int j = 0; j < i; ++j) {
                if (v[j] > v[i]) {
                    inv++;
                }
            }
        }
    }
    inv += zero.first + 1;
    return !(inv & 1u);
}

bool operator<(Board const &a, Board const &b) {
    return a.length < b.length;
}

std::pair<size_t, size_t> Board::get_zero() const {
    return zero;
}

bool Board::is_cords_in_field(int x, int y) const {
    return x < length && y < length;
}
