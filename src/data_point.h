#pragma once

#include <array>

template <int size>
struct data_point {
    std::array<float, size> data;
    int group;

    data_point() {
        for (int i = 0; i < size; i++) {
            this->data[i] = 0;
        }
        this->group = -1;
    }
    data_point(std::array<float, size> data) {
        this->data = data;
        this->group = -1;
    }
    data_point(std::array<int, size> data) {
        this->data = std::array<float, size>(data);
        this->group = -1;
    }

    data_point operator+(const data_point<size> &d) {
        std::array<float, size> ret;
        for (int i = 0; i < size; i++) {
            ret[i] = this->data[i] + d[i];
        }
        return data_point(ret);
    }
    data_point operator-(const data_point<size> &d) {
        std::array<float, size> ret;
        for (int i = 0; i < size; i++) {
            ret[i] = this->data[i] - d[i];
        }
        return data_point(ret);
    }
    data_point operator*(float f) {
        return data_point({this->data[0] * f, this->data[1] * f});
    }
    data_point operator/(float f) {
        return data_point({this->data[0] / f, this->data[1] / f});
    }

    void operator+=(const data_point<size> &d) {
        for (int i = 0; i < size; i++) {
            this->data[i] += d[i];
        }
    }
    void operator-=(const data_point<size> &d) {
        for (int i = 0; i < size; i++) {
            this->data[i] -= d[i];
        }
    }

    bool operator==(const data_point<size> &d) {
        bool ret = true;
        for (int i = 0; i < size; i++) {
            ret = ret && (this->data[i] == d.data[i]);
        }
        return ret;
    }
};