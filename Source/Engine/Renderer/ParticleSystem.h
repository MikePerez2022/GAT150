#pragma once
#include "Particle.h"
#include <vector>
#include "Renderer/Renderer.h"
#include "Framework/Singleton.h"

namespace jojo
{
	class ParticleSystem : public Singleton<ParticleSystem>
	{
	public:
		ParticleSystem() = default;
		ParticleSystem(int maxCount)
		{
			m_particles.resize(maxCount);
		}

		void Update(float dt);
		void Draw(Renderer& renderer);

		Particle* GetFreeParticle();

	private:
		std::vector<Particle> m_particles;
	};

	extern ParticleSystem g_particleSystem;
}