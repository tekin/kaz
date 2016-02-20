#ifndef GLYPTH_H
#define GLYPTH_H

class Glyph {
  public:
    Glyph();
    Glyph(unsigned long bitmap);
    Glyph(unsigned long bitmap, unsigned int width);
    unsigned int nextColumn();
    bool endOfGlyph();
    // the readBitmap and readWidth methods are marked as const, which means
    // they promise to not modify the instance.
    unsigned long readBitmap() const;
    unsigned int readWidth() const;
    void reset();

  private:
    unsigned long _bitmap;
    unsigned int _index;
    unsigned int _width;
};

// Comparison operator, mostly for use in the tests
inline bool operator==(const Glyph glyph1, const Glyph glyph2) {
  return(glyph1.readBitmap() == glyph2.readBitmap() && glyph1.readWidth() == glyph2.readWidth());
}

inline bool operator!=(const Glyph glyph1, const Glyph glyph2) {
  return(glyph1.readBitmap() != glyph2.readBitmap() || glyph1.readWidth() != glyph2.readWidth());
}

#endif
