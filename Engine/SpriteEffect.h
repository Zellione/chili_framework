#pragma once

#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma(Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, cSrc); 
			}
		}
	private:
		Color chroma;
	};

	class Substitution
	{
	public:
		Substitution(Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
	
	class Copy
	{
	public:
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};

	class Ghost
	{
	public:
		Ghost(Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			const Color dstPixel = gfx.GetPixel(xDest, yDest);

			const Color blendedPixel = {
				unsigned char((cSrc.GetR() + dstPixel.GetR()) / 2),
				unsigned char((cSrc.GetG() + dstPixel.GetG()) / 2),
				unsigned char((cSrc.GetB() + dstPixel.GetB()) / 2),
			};

			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, blendedPixel);
			}
		}
	private:
		Color chroma;
	};
}