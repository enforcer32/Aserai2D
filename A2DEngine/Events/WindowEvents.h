#pragma once

#include "A2DEngine/Events/Event.h"

namespace Aserai2D
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
	};


	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {}

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t m_Width, m_Height;
	};
}
