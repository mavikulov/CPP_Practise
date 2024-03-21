#pragma once

#include <stdexcept>
#include <cmath>
#include <algorithm>

struct Point {
    int x, y;
};

struct Triangle {
    Point a, b, c;
};

int64_t Sid(const Point& p1, const Point& p2, const Point& p) {
    int64_t p1x = static_cast<int64_t>(p1.x);
    int64_t p2x = static_cast<int64_t>(p2.x);
    int64_t px = static_cast<int64_t>(p.x);
    int64_t p1y = static_cast<int64_t>(p1.y);
    int64_t p2y = static_cast<int64_t>(p2.y);
    int64_t py = static_cast<int64_t>(p.y);
    int64_t result = (((px - p1x) * (p2y - p1y)) - ((py - p1y) * (p2x - p1x)));
    return result;
}

bool LineCheck(const Point& p1, const Point& p2, const Point& p) {
    int64_t p1x = static_cast<int64_t>(p1.x);
    int64_t p2x = static_cast<int64_t>(p2.x);
    int64_t px = static_cast<int64_t>(p.x);
    int64_t p1y = static_cast<int64_t>(p1.y);
    int64_t p2y = static_cast<int64_t>(p2.y);
    int64_t py = static_cast<int64_t>(p.y);
    if (std::min(p1y, p2y) <= py && (std::max(p1y, p2y) >= py) && std::min(p1x, p2x) <= px &&
        std::max(p1x, p2x) >= px) {
        return true;
    }
    return false;
}

bool ZeroCheck(const Point& p1, const Point& p2, const Point& p3) {
    if (p1.x == p2.x && p2.x == p3.x && p1.y == p2.y && p2.y == p3.y) {
        return true;
    }
    return false;
}

bool IsPointInTriangle(const Triangle& t, const Point& pt) {
    if (ZeroCheck(t.a, t.b, t.c)) {
        return false;
    }
    int64_t line_check = Sid(t.a, t.b, t.c);
    if (line_check == 0) {
        bool lc1 = LineCheck(t.a, t.b, pt);
        bool lc2 = LineCheck(t.b, t.c, pt);
        bool lc3 = LineCheck(t.c, t.a, pt);
        return lc1 || lc2 || lc3;
    }
    int64_t first_check = Sid(t.a, t.b, pt);
    int64_t second_check = Sid(t.b, t.c, pt);
    int64_t third_check = Sid(t.c, t.a, pt);
    if (first_check >= 0 && second_check >= 0 && third_check >= 0) {
        return true;
    } else if (first_check <= 0 && second_check <= 0 && third_check <= 0) {
        return true;
    }
    return false;
}

