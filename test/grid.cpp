#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "grid.hpp"


TEST_CASE("1d-grid") {
    double dx = 10./41;
    double x = 0.;
    for (double xp : grid<1> {42, {0, 10}}) {
        CHECK(xp == doctest::Approx(x));
        x += dx;
    }
}

TEST_CASE("2d-grid-row-major") {
    double dx = 10./3;
    double dy = 10./4;
    double x = 0.;
    double y = 0.;
    for (auto p : grid<2> {{4, {0, 10}}, {5, {0, 10}}}) {
        CHECK(p[0] == doctest::Approx(x));
        CHECK(p[1] == doctest::Approx(y));
        y += dy;
        if (y > doctest::Approx(10.)) {
            y = 0.;
            x += dx;
        }
    }
}

TEST_CASE("2d-grid-col-major") {
    double dx = 10./3;
    double dy = 10./4;
    double x = 0.;
    double y = 0.;
    for (auto p : grid<2, major_order::col> {{4, {0, 10}}, {5, {0, 10}}}) {
        CHECK(p[0] == doctest::Approx(x));
        CHECK(p[1] == doctest::Approx(y));
        x += dx;
        if (x > doctest::Approx(10.)) {
            x = 0.;
            y += dy;
        }
    }
}
