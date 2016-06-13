#pragma once

#include "c_entity.h"

struct SPartInfo {
	t_real minLifespan = 0;
	t_real maxLifespan = 0;
	t_real minScale = 1.0;
	t_real maxScale = 1.0;
	t_real minGrav = 0.0;
	t_real maxGrav = 0.0;
	t_real minGravDir = 0.0;
	t_real maxGravDir = 0.0;
	t_color4_r startColor = { 1.0, 1.0, 1.0, 1.0 };
	t_color4_r startVariance = { 0.0, 0.0, 0.0, 0.0 };
	t_color4_r endColor = { 0.0, 0.0, 0.0, 0.0 };
	t_color4_r endVariance = { 0.0, 0.0, 0.0, 0.0 };
	EBlendMode mode = BLEND_ADD;
};

class CParticle : public CEntity {

	public:
	CParticle( const SPartInfo& info );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );

	private:
	t_real _gravDir;
	t_real _grav;
	t_real _span;
	t_real _life;
	t_color4_r _start;
	t_color4_r _end;

};
