#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Goomba.h"

#define GOOMBAFLY_GRAVITY 0.002f
#define GOOMBAFLY_WALKING_SPEED 0.05f
#define GOOMBAFLY_DEFLECT_SPEED 0.4f


#define GOOMBAFLY_BBOX_WIDTH 16
#define GOOMBAFLY_BBOX_HEIGHT 14
#define GOOMBAFLY_BBOX_HEIGHT_DIE 7

#define GOOMBAFLY_DIE_TIMEOUT 500

#define GOOMBAFLY_STATE_WALKING 700
#define GOOMBAFLY_STATE_DIE 800
#define GOOMBAFLY_STATE_DEFLECT 801

#define ID_ANI_GOOMBAFLY_WALKING 5100
#define ID_ANI_GOOMBAFLY_FLY 5101

class CGoombafly : public CGameObject
{
protected:
	float ax;
	float ay;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return GetState() != GOOMBAFLY_STATE_DEFLECT; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
public:
	CGoombafly(float x, float y);
	virtual void SetState(int state);
};