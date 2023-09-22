#include "RGBAPixel.h"

namespace cs221util {

    RGBAPixel::RGBAPixel() {
        r = 255;
        g = 255;
        b = 255;
        a= 1.0;
    }

    RGBAPixel::RGBAPixel(unsigned char red, unsigned char green, unsigned char blue) {
        r = red;
        g = green;
        b = blue;
        a = 1.0;
    }

    RGBAPixel::RGBAPixel(unsigned char red, unsigned char green, unsigned char blue, double alpha) {
        r = red;
        g = green;
        b = blue;
        a = alpha;
    }
}
