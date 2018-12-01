#include "Font.h"
#include <assert.h>
#include "SpriteEffect.h"

Font::Font(const std::wstring& filename, Color chroma)
	:
	surface(filename),
	// calculate glyph dimensions from bitmap dimensions
	glyphWidth(surface.GetWidth() / nColumns),
	glyphHeight(surface.GetHeight() / nRows),
	chroma(chroma)
{
	// verify that bitmap had valid dimensions
	assert(glyphWidth * nColumns == surface.GetWidth());
	assert(glyphHeight * nRows == surface.GetHeight());
}

void Font::DrawText(const std::wstring & text, const Vei2 & pos, Color color, Graphics & gfx) const
{
	// create effect functor
	SpriteEffect::Substitution e{ chroma, color };

	// curPos is the pos that we are drawing to on the screen
	auto curPos = pos;
	for (auto c : text)
	{
		if (c == '\n')
		{
			curPos.x = pos.x;
			curPos.y += glyphHeight;
			continue;
		}
		// only draw characters that are on the font sheet
		// firstChar + 1 because might as well skip ' '
		else if (c >= firstChar + 1 && c <= lastChar)
		{
			gfx.DrawSprite(curPos.x, curPos.y, MapGlyphRect((char)c), surface, e);
		}
		// advance screen pos for next character
		curPos.x += glyphWidth;
	}
}

RectI Font::MapGlyphRect(char c) const
{
	assert(c >= firstChar && c <= lastChar);
	// font sheet glyphs start at ' ', calculate index into sheet
	const int glyphIndex = c - firstChar;
	// map 1d glyphIndex to 2D coordinates
	const int yGlyph = glyphIndex / nColumns;
	const int xGlyph = glyphIndex % nColumns;
	
	// convert the sheet grid coords to pixel coords in sheet
	return RectI(
		{ xGlyph * glyphWidth, yGlyph * glyphHeight }, glyphWidth, glyphHeight
	);
}
