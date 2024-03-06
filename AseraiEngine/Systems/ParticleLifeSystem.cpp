#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/ParticleLifeSystem.h"
#include "AseraiEngine/Components/ParticleComponent.h"
#include "AseraiEngine/Utils/DateTime.h"

namespace Aserai
{
	ParticleLifeSystem::ParticleLifeSystem()
	{
		RegisterComponent<ParticleComponent>();
	}

	void ParticleLifeSystem::OnUpdate(DeltaTime dt)
	{
		for (auto& entity : GetEntities())
		{
			const auto& particle = entity.GetComponent<ParticleComponent>();
			if (DateTime::GetTimeSeconds() - particle.StartTime > particle.Duration)
				entity.Destroy();
		}
	}
}
