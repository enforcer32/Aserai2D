#pragma once

namespace Aserai2D
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
		virtual void OnImGuiRender() = 0;
	};
}
