/*
Compile and run this test with:

  $ g++ -I include -I ./ -pthread test/Glyph_test.cpp Glyph.cpp lib/libgtest.a -o bin/test_executable
  $ ./bin/test_executable

*/
#include "Glyph.h"
#include "gtest/gtest.h"

TEST(GlyphTest, nextColumn) {
  Glyph glyph(0b0110100110110000UL);
  // returns successive nibbles of the glyth
  EXPECT_EQ(0b0000000000000110, glyph.nextColumn());
  EXPECT_EQ(0b0000000000001001, glyph.nextColumn());
  EXPECT_EQ(0b0000000000001011, glyph.nextColumn());
  EXPECT_EQ(0b0000000000000000, glyph.nextColumn());
}

TEST(GlyphTest, widthOverrideTest) {
  Glyph glyph(0b01101001UL, 2);
  // Glyph width can be overridden for narrower glyphs
  EXPECT_EQ(0b0000000000000110, glyph.nextColumn());
  EXPECT_EQ(false, glyph.endOfGlyph());
  EXPECT_EQ(0b0000000000001001, glyph.nextColumn());
  EXPECT_EQ(true, glyph.endOfGlyph());
}

TEST(GlyphTest, wideWidthOverrideTest) {
  Glyph glyph(0b11110100001001001111UL, 5); // Glyph for 'M'
  // Glyph width can be overridden for narrower glyphs
  EXPECT_EQ(0b000001111, glyph.nextColumn());
  EXPECT_EQ(false, glyph.endOfGlyph());
  EXPECT_EQ(0b000000100, glyph.nextColumn());
  EXPECT_EQ(false, glyph.endOfGlyph());
  EXPECT_EQ(0b000000010, glyph.nextColumn());
  EXPECT_EQ(false, glyph.endOfGlyph());
  EXPECT_EQ(0b000000100, glyph.nextColumn());
  EXPECT_EQ(false, glyph.endOfGlyph());
  EXPECT_EQ(0b000001111, glyph.nextColumn());
  EXPECT_EQ(true, glyph.endOfGlyph());
}

TEST(GlyphTest, equalityTest) {
  Glyph a_glyph(0b1111101010101111UL);
  Glyph another_a_glyph(0b1111101010101111UL);

  ASSERT_EQ(a_glyph, another_a_glyph);
}

TEST(GlyphTest, inequalityTest) {
  Glyph a_glyph(0b1111101010101111UL);
  Glyph b_glyph(0b1111110101110000UL);
  ASSERT_NE(a_glyph, b_glyph);
}

TEST(GlyphTest, endOfGlyph) {
  Glyph glyph(0b0110100110110000L);
  // returns false until the end of the Glyph is reached
  EXPECT_EQ(false, glyph.endOfGlyph());
  glyph.nextColumn();
  EXPECT_EQ(false, glyph.endOfGlyph());
  glyph.nextColumn();
  EXPECT_EQ(false, glyph.endOfGlyph());
  glyph.nextColumn();
  EXPECT_EQ(false, glyph.endOfGlyph());
  glyph.nextColumn();
  EXPECT_EQ(true, glyph.endOfGlyph());
}

TEST(GlyphTest, reset) {
  Glyph glyph(0b0110100110110000UL);
  // resets the Glyph to its initial state
  EXPECT_EQ(0b0000000000000110, glyph.nextColumn());
  EXPECT_EQ(0b0000000000001001, glyph.nextColumn());
  glyph.reset();
  EXPECT_EQ(0b0000000000000110, glyph.nextColumn());
  EXPECT_EQ(0b0000000000001001, glyph.nextColumn());
}
