#include "block.h"
#include <cmath>
#include <iostream>

// Returns height of the current block
int Block::height() const {
  return data.size();
}

// Returns width of the current block
int Block::width() const {
  if (data.size() == 0) {
    return 0;
  } else {
    return data[0].size();
  }
}

// Draws the current block at position (x,0) in im
void Block::render(PNG &im, int x) const {
 if (!(x>=0 && (unsigned)x<im.width()))
    return;
  
unsigned int col_bound = (x + width() > im.width())? im.width() : (x + width());  
  for (unsigned int col = x; col<col_bound; col++){
    for (unsigned int row = 0; row<im.height(); row++){
      *(im.getPixel(col, row)) = data[row][col-(unsigned)x];
    }
  }
}

// From the pNG image im, grabs the vertical rectangular strip
//      of pixels whose upper left corner is at position (x,0) 
//      and whose dimensions are width by height of the image im
void Block::build(PNG &im, int x, int width) {
  unsigned int col_bound = x + width;
  unsigned int row_bound = im.height();
  data.resize(im.height());
  for (unsigned int row=0; row<row_bound; row++){
    data[row].resize(width);
    for (unsigned int col=x; col<col_bound; col++){
      data[row][col-(unsigned)x] = *(im.getPixel(col, row));
    }
  }
}