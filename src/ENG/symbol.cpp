#include "symbol.h"
#include "settings.h"

void Symbol::draw(float xGap, float yGap, float symbol) {
    Rect r = {symbol / 10.0f,
              0.0f,
             (symbol + 1) / 10.0f,
              1.0f};

    Image::draw_once(xGap, yGap, 0.04f, 0.65f, &r, 1.0f);
}