#pragma once

#include "libs.h"

class Symbol {
    float xGap;
    float yGap;
    Image *img;
public:
    Symbol(float xGap, float yGap, float symbol);
    static void draw(float xGap, float yGap, float symbol);
    ~Symbol();
};