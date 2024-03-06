#include "A2DEnginePCH.h"
#include "A2DEngine/Core/UUID.h"

#include <random>

namespace Aserai2D
{
	UUID::UUID()
		: m_UUID(GenerateRandom())
	{
	}

	UUID::UUID(uint64_t uuid)
		: m_UUID(uuid)
	{
	}

	uint64_t UUID::GenerateRandom()
	{
		static std::random_device randomDevice;
		static std::mt19937_64 engine(randomDevice());
		static std::uniform_int_distribution<uint64_t> uniformDistrib;
		return uniformDistrib(engine);
	}
}
