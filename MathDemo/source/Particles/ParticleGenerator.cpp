#include "Particles/ParticleGenerator.h"
#include "Entities/Bullet.h"
#include <Texture.h>
#include <random>

ParticleGenerator::ParticleGenerator() {
}

ParticleGenerator::ParticleGenerator(aie::Texture * pType) : m_particleType(pType) {
}

ParticleGenerator::~ParticleGenerator() {
}

void ParticleGenerator::update(float dt) {
	Node::update(dt);
	for (size_t i = 0; i < m_particles.size(); ++i)
		m_particles[i]->update(dt);

	m_lifetime -= dt;
	if (m_lifetime <= 0)
		m_isDrawn = false;
}

void ParticleGenerator::render(aie::Renderer2D * renderer) {
	for (size_t i = 0; i < m_particles.size(); ++i)
		m_particles[i]->render(renderer);
	Node::render(renderer);
}

void ParticleGenerator::createExplosion(int minParticles, int maxParticles, float minScale, float maxScale) {
	unsigned int numParticles = rand() % (maxParticles - minParticles) + minParticles;
	for (size_t i = 0; i < numParticles; ++i) {
		std::unique_ptr<Bullet> particle = std::unique_ptr<Bullet>(new Bullet(m_particleType));
		particle->setParent(this);
		particle->setRotate((float)(rand() % 360));
		particle->setMoveSpeed(120);
		particle->setLifetime(m_lifetime);
		float scale = rand() % int(maxScale - minScale) + minScale;
		particle->setSize(Vector2<float>(scale, scale));
		m_particles.push_back(std::move(particle));
	}
}

void ParticleGenerator::setLifetime(float val) {
	m_lifetime = val;
}
