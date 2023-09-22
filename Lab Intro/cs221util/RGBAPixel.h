#ifndef CS221UTIL_RGBAPixel_H
#define CS221UTIL_RGBAPixel_H

namespace cs221util {
    class RGBAPixel {

        public:

        RGBAPixel();
        RGBAPixel(unsigned char r, unsigned char g, unsigned char b);
        RGBAPixel(unsigned char r, unsigned char g, unsigned char b, double a);
    
        unsigned char r;
        unsigned char g;
        unsigned char b;
        double a;
    };
}
#endif