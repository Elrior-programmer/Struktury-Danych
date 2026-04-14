#pragma once

struct Medium {
    long long a;
    long long b;
    long long c;

    Medium() : a(0), b(0), c(0) {}

    Medium(long long x) : a(x), b(x), c(x) {}

    Medium(long long a_, long long b_, long long c_)
        : a(a_), b(b_), c(c_) {}

    bool operator==(const Medium& other) const {
        return a == other.a && b == other.b && c == other.c;
    }
};