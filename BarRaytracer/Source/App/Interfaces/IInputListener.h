#pragma once
#include"../Common.h"

namespace framework
{
	class IInputListener
	{
	public:
		virtual void OnMouseMove(uint x, uint y, int relX, int relY, uint btn, uint key) {}
		virtual void OnMouseDown(uint x, uint y, uint btn, uint key) {}
		virtual void OnMouseUp(uint x, uint y, uint btn, uint key) {}
		virtual void OnMouseWheel(uint x, uint y, short wheel) {}

		virtual void OnKeyDown(uint key) {}
		virtual void OnKeyUp(uint key) {}
		virtual void OnChar(char Char) {}
	};
};