#include "stats.h"

stats::stats(PNG& im) {
    int width = im.width();
    int height = im.height();
    sumRed.resize(width + 1, vector<long>(height + 1, 0));
    sumGreen.resize(width + 1, vector<long>(height + 1, 0));
    sumBlue.resize(width + 1, vector<long>(height + 1, 0));
    sumsqRed.resize(width + 1, vector<long>(height + 1, 0));
    sumsqGreen.resize(width + 1, vector<long>(height + 1, 0));
    sumsqBlue.resize(width + 1, vector<long>(height + 1, 0));

    // Initialize cumulative sums and cumulative sums of squares for each color channel
    for (int y = 1; y <= height; y++) {
        for (int x = 1; x <= width; x++) {
            RGBAPixel* pixel = im.getPixel(x - 1, y - 1);
            long r = pixel->r;
            long g = pixel->g;
            long b = pixel->b;
            sumRed[x][y] = sumRed[x-1][y] + sumRed[x][y-1] - sumRed[x-1][y-1] + r;
            sumGreen[x][y] = sumGreen[x-1][y] + sumGreen[x][y-1] - sumGreen[x-1][y-1] + g;
            sumBlue[x][y] = sumBlue[x-1][y] + sumBlue[x][y-1] - sumBlue[x-1][y-1] + b;
            sumsqRed[x][y] = sumsqRed[x-1][y] + sumsqRed[x][y-1] - sumsqRed[x-1][y-1] + r*r;
            sumsqGreen[x][y] = sumsqGreen[x-1][y] + sumsqGreen[x][y-1] - sumsqGreen[x-1][y-1] + g*g;
            sumsqBlue[x][y] = sumsqBlue[x-1][y] + sumsqBlue[x][y-1] - sumsqBlue[x-1][y-1] + b*b;
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, int dim) {
    if (channel == 'r')
        return generalSum(sumRed, ul, dim);
    else if (channel == 'g')
        return generalSum(sumGreen, ul, dim);
    else  // (channel == 'b')
        return generalSum(sumBlue, ul, dim);
}

long stats::generalSum(vector<vector<long>>& tab, pair<int, int> ul, int dim) {
    pair<int, int> lr;
    lr.first = ul.first + pow(2, dim) - 1;
    lr.second = ul.second + pow(2, dim) - 1;

    if (ul.first == 0 && ul.second == 0)
        return tab[lr.second][lr.first];
    else if (ul.second == 0)
        return tab[lr.second][lr.first] - tab[lr.second][ul.first - 1];
    else if (ul.first == 0)
        return tab[lr.second][lr.first] - tab[ul.second - 1][lr.first];
    else
        return tab[lr.second][lr.first] - tab[lr.second][ul.first - 1] - tab[ul.second - 1][lr.first] + tab[ul.second - 1][ul.first - 1];
}

long stats::getSumSq(char channel, pair<int, int> ul, int dim) {
 long sum = 0;
    int x = ul.first;
    int y = ul.second;
    int length = pow(2, dim);

    if (channel == 'r') {
        sum = sumsqRed[x + length][y + length] - sumsqRed[x][y + length] - sumsqRed[x + length][y] + sumsqRed[x][y];
    } else if (channel == 'g') {
        sum = sumsqGreen[x + length][y + length] - sumsqGreen[x][y + length] - sumsqGreen[x + length][y] + sumsqGreen[x][y];
    } else if (channel == 'b') {
        sum = sumsqBlue[x + length][y + length] - sumsqBlue[x][y + length] - sumsqBlue[x + length][y] + sumsqBlue[x][y];
    }
    return sum;
}

long stats::rectArea(int dim) {
    /* Your code here!! */
    long sideLength = pow(2, dim);
    return sideLength * sideLength;
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int dim) {

    double area = rectArea(dim);

    double redSumSq = (double)getSumSq('r', ul, dim);
    double greenSumSq = (double)getSumSq('g', ul, dim);
    double blueSumSq = (double)getSumSq('b', ul, dim);

    double redSum = (double)getSum('r', ul, dim);
    double greenSum = (double)getSum('g', ul, dim);
    double blueSum = (double)getSum('b', ul, dim);

    double redVar = redSumSq - (redSum * redSum)/area;
    double greenVar = greenSumSq - (greenSum * greenSum)/area;
    double blueVar = blueSumSq - (blueSum * blueSum)/area;

    return (redVar + greenVar + blueVar);
    
    //double sumSq = redSumSq + greenSumSq + blueSumSq;
    //double sum = redSum + greenSum + blueSum;
    //double sumSqLong = ((double)redSum*redSum) + ((double)greenSum*greenSum) + ((double)blueSum*blueSum);
    //double var = sumSq - sumSqLong / area;
    //return var;
}


RGBAPixel stats::getAvg(pair<int, int> ul, int dim) {
    /* Your code here!! */
    int area = rectArea(dim);
    RGBAPixel pixel;
    pixel.r = getSum('r', ul, dim)/area;
    pixel.g = getSum('g', ul, dim)/area;
    pixel.b = getSum('b', ul, dim)/area;
    return pixel;
}
