#include "Glyph.h"

#define GLYPH_ROW_COUNT 4
#define GLYPH_COLUMN_MASK 0b1111UL
#define GLYPH_DEFAULT_WIDTH 4

//constructors
Glyph::Glyph() :_bitmap(0), _index(1), _width(GLYPH_DEFAULT_WIDTH) {}
Glyph::Glyph(unsigned long bitmap) :_bitmap(bitmap), _index(1), _width(GLYPH_DEFAULT_WIDTH) {}
Glyph::Glyph(unsigned long bitmap, unsigned int width)  :_bitmap(bitmap), _index(1), _width(width) {}

// Pops the next column off the bitmap
unsigned int Glyph::nextColumn() {
  unsigned int next_column = (_bitmap >> (GLYPH_ROW_COUNT*(_width-_index))) & GLYPH_COLUMN_MASK;
  _index++;
  return(next_column);
}

// Returns true if the end of the Glyph has been reached
bool Glyph::endOfGlyph() {
  if(_index > _width)
    return(true);
  else
    return(false);
}

// Resets the Glyph back to its original state
void Glyph::reset() {
  _index = 1;
}

unsigned long Glyph::readBitmap()
const {
  return(_bitmap);
}
unsigned int Glyph::readWidth()
const {
  return(_width);
}
