#pragma once

#include "c_rigidBody.h"
#include <c_defs.h>
#include <c_sprite.h>
#include "c_resources.h"

struct s_colInfo;

class CEntity {

	public:

	CEntity( void );
	virtual ~CEntity( void );

	virtual void Init( void );
	virtual void Tick( void );
	virtual void Draw( void );
	virtual void SetPosition( Vector2 newPosition );
	virtual void OnCollision( s_colInfo * info );
	virtual void Disable( void );
	virtual void Enable( void );
	virtual bool IsEnabled( void );
	virtual void AllocateSprites( t_uint count );

	virtual CRigidBody& GetRigidBody( void );

	protected:
	CSprite ** _sprite;
	t_uint _spriteCount;
	CRigidBody _rigidBody;
	bool _enabled;


};