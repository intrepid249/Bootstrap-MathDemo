#pragma once
#include "Nodes\Node.h"
#include <vector>
#include <memory>

namespace aie {
	class Texture;
}
class Bullet;

class ParticleGenerator :
	public Node {
public:
	ParticleGenerator();
	/** Create a new particle generator with the specified particle type
	* @param pType - pointer to the texture to use as the particle type*/
	ParticleGenerator(aie::Texture *pType);
	~ParticleGenerator();

	/** Override the parent's update function
	* @see MathDemo::Node#update(float)*/
	virtual void update(float dt);
	/** Override the parent's render function
	* @see MathDemo::Node#render(aie::Renderer2D)*/
	virtual void render(aie::Renderer2D *renderer);

	/** Create a particle explosion with random amounts of particles between the set range*/
	void createExplosion(int minParticles, int maxParticles, float minScale, float maxScale);

	/** Set the duration (in seconds) the particle generator will survive for*/
	void setLifetime(float val);

protected:
	aie::Texture *m_particleType;
	std::vector<std::unique_ptr<Bullet>> m_particles;
	float m_lifetime;
};

