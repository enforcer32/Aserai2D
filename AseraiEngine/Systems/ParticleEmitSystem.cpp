#include "AseraiEnginePCH.h"
#include "AseraiEngine/Systems/ParticleEmitSystem.h"
#include "AseraiEngine/Components/TransformComponent.h"
#include "AseraiEngine/Components/ParticleEmitterComponent.h"
#include "AseraiEngine/Components/ParticleSpriteComponent.h"
#include "AseraiEngine/Components/ParticleComponent.h"
#include "AseraiEngine/Components/SpriteComponent.h"
#include "AseraiEngine/Components/RigidBodyComponent.h"
#include "AseraiEngine/Components/BoxColliderComponent.h"

namespace Aserai
{
	ParticleEmitSystem::ParticleEmitSystem()
	{
		RegisterComponent<TransformComponent>();
		RegisterComponent<ParticleEmitterComponent>();
		RegisterComponent<ParticleSpriteComponent>();
	}

	void ParticleEmitSystem::OnUpdate(DeltaTime dt, const std::shared_ptr<Registry>& registry, const std::shared_ptr<InputManager>& inputManager)
	{
		for (auto& entity : GetEntities())
		{
			const auto& transform = entity.GetComponent<TransformComponent>();
			auto& particleEmitter = entity.GetComponent<ParticleEmitterComponent>();
			const ParticleSpriteComponent* particleSprite = &entity.GetComponent<ParticleSpriteComponent>();

			glm::vec3 directionVelocity = particleEmitter.Velocity;
			int32_t dirX = 0, dirY = 0;
			if (transform.Rotation2D == 90.0f)
				dirX = -1;
			else if (transform.Rotation2D == -90.0f)
				dirX = 1;
			else if (transform.Rotation2D == 0.0f)
				dirY = 1;
			else if (transform.Rotation2D == 180.0f)
				dirY = -1;
			directionVelocity.x *= dirX;
			directionVelocity.y *= dirY;

			if (particleEmitter.Automatic)
			{
				if (!particleEmitter.Frequency)
					continue;

				if (DateTime::GetTimeSeconds() - particleEmitter.LastEmitTime > particleEmitter.Frequency)
				{
					Entity particle = registry->CreateEntity();
					particle.SetGroup(particleEmitter.Name);
					particle.AddComponent<TransformComponent>(transform.Translation, glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0 * particleSprite->Width, 1.0 * particleSprite->Height, 1.0), transform.Rotation2D);
					particle.AddComponent<RigidBodyComponent>(directionVelocity);
					particle.AddComponent<SpriteComponent>(*(SpriteComponent*)particleSprite);
					particle.AddComponent<BoxColliderComponent>(particleSprite->Width, particleSprite->Height);
					particle.AddComponent<ParticleComponent>(particleEmitter.Duration, particleEmitter.Hit, particleEmitter.Friendly);

					particleEmitter.LastEmitTime = DateTime::GetTimeSeconds();
				}
			}
			else
			{
				if (inputManager->IsKeyPressed(particleEmitter.Key))
				{
					Entity particle = registry->CreateEntity();
					particle.SetGroup(particleEmitter.Name);
					particle.AddComponent<TransformComponent>(transform.Translation, glm::vec3(0.0, 0.0, 1.0), glm::vec3(1.0 * particleSprite->Width, 1.0 * particleSprite->Height, 1.0), transform.Rotation2D);
					particle.AddComponent<RigidBodyComponent>(directionVelocity);
					particle.AddComponent<SpriteComponent>(*(SpriteComponent*)particleSprite);
					particle.AddComponent<BoxColliderComponent>(particleSprite->Width, particleSprite->Height);
					particle.AddComponent<ParticleComponent>(particleEmitter.Duration, particleEmitter.Hit, particleEmitter.Friendly);

					particleEmitter.LastEmitTime = DateTime::GetTimeSeconds();
				}
			}
		}
	}
}
