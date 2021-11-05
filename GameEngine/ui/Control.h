#pragma once
#include<string>
#include<ui/Types.h>

using namespace UI;

namespace Controls
{
	class Control
	{
	protected:
		float width, height;
		float x, y;

	public:

		Control()
		{
			width = 0;
			height = 0;
			x = 0;
			y = 0;
		}

		virtual void render() = 0;
		virtual void align(Alignment vAlign, Alignment hAlign) = 0;

		unsigned int getWidth()
		{
			return width;
		}

		unsigned int getHeight()
		{
			return height;
		}

		float getXOffset()
		{
			return x;
		}

		float getYOffset()
		{
			return y;
		}
	};
}