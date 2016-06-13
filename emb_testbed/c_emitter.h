#pragma once

#include <c_common.h>
#include "c_entity.h"
#include "c_particle.h"

enum EEmitType {
	EMIT_BURST,
	EMIT_STREAM,
	EMIT_LIGHTNING
};

struct SEmitInfo {
	EEmitType type = EMIT_BURST;
	t_real direction = 0;
	t_real spread = 0;
	t_real count = 0;
	t_real interval = 0;
	t_real minSpeed = 0;
	t_real maxSpeed = 0;
	t_real lifespan = 0;
	Vector2 target = { 0, 0 };
};

class CEmitter : public CEntity {

	public:
	CEmitter( const Vector2& pos, const SEmitInfo& einfo, const SPartInfo& pinfo );
	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );
	void SetDirection( t_real direction );
	void Enable( void );
	void Disable( void );

	private:

	void _Emit( void );
	void _Emit( Vector2 from );

	bool _enabled;
	t_real _life;
	SEmitInfo _einfo;
	SPartInfo _pinfo;
	t_real _intervalCount;


};
