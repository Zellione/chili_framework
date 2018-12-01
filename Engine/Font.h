#pragma once

#include <string>
#include "Graphics.h"
#include "Rect.h"
#include "Surface.h"
#include "Vec2.h"
#include "Colors.h"

class Font
{
public:
	Font(const std::wstring& filename, Color chroma = Colors::White);
	void DrawText(const std::wstring& text, const Vei2& pos, Color color, Graphics& gfx) const;
private:
	RectI MapGlyphRect(char c) const;
private:
	// holds the font sheet bitmap data
	Surface surface;
	// this is given the dimensions of a glyph in the font sheet
	int glyphWidth;
	int glyphHeight;
	// number of rows / columns in the font sheet (this is fixed)
	static constexpr int nColumns = 32;
	static constexpr int nRows = 3;
	// font sheet chroma Color
	Color chroma;
	// start and end drawable character codes
	static constexpr char firstChar = ' ';
	static constexpr char lastChar = '~';
};

