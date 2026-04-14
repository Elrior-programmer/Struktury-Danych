#pragma once

struct Large {
    static const int SIZE = 256;
    char data[SIZE];

    Large() {
        for (int i = 0; i < SIZE; i++) {
            data[i] = 0;
        }
    }

    Large(char val) {
        for (int i = 0; i < SIZE; i++) {
            data[i] = val;
        }
    }

    bool operator==(const Large& other) const {
        for (int i = 0; i < SIZE; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }
};