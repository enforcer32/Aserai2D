#pragma once

namespace Aserai2D
{
	class DeltaTime
	{
	public:
		DeltaTime()
			: m_Time(0)
		{}

		DeltaTime(double time)
			: m_Time(time)
		{}

		operator double() const { return m_Time; }

		inline double GetSeconds() const { return m_Time; }
		inline double GetMilliSeconds() const { return m_Time * 1000.0f; }

	private:
		double m_Time;
	};
};
