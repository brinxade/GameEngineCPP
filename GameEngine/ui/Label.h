#pragma once
#include"Control.h"
#include<ui/Text.h>

using namespace UI;

namespace Controls 
{
	class Label:public Control
	{
	private:
		Text* textNode;
		std::string fontName;
		Alignment hAlign, vAlign;
		Control* parent;

	public:
		Label(std::string text, std::string fontName = "arial")
		{
			this->parent = nullptr;
			this->textNode = new Text(this, text, fontName);
			this->x = 0;
			this->y = 0;
			this->width = this->textNode->getWidth();
			this->height = this->textNode->getHeight();
			
			align(Alignment::LEFT, Alignment::CENTER);
		}

		~Label()
		{
			delete textNode;
		}

		void setText(std::string text)
		{
			this->textNode->setText(text);
		}

		void align(Alignment vAlign, Alignment hAlign)
		{
			alignY(vAlign);
			alignX(hAlign);
		}

		void alignY(Alignment vAlign)
		{
			this->vAlign = vAlign;
			float parentHeight = parent ? parent->getHeight() : (float)WINDOW_HEIGHT;

			if (this->vAlign == Alignment::TOP)
				y = parentHeight-height;
			else if (this->vAlign == Alignment::BOTTOM)
				y = 0;
			else if (this->vAlign == Alignment::CENTER)
				y = (parentHeight / 2) - (height / 2);
		}

		void alignX(Alignment hAlign)
		{
			this->hAlign = hAlign;
			float parentWidth = parent ? parent->getWidth() : (float)WINDOW_WIDTH;

			if (this->hAlign == Alignment::LEFT)
				x = 0;
			else if (this->hAlign == Alignment::RIGHT)
				x = parentWidth - width;
			else if (this->hAlign == Alignment::CENTER)
				x = (parentWidth / 2) - (width / 2);
		}

		void render()
		{
			this->width = textNode->getWidth();
			this->height = textNode->getHeight();
			align(vAlign, hAlign);
			textNode->render();
		}
	};
}
