#pragma once

namespace Aserai
{
	class Panel
	{
	public:
		virtual ~Panel() = default;
		virtual void OnImGuiRender() = 0;
	};
}
