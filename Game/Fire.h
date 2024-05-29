#pragma once
#include "GameObject.h"

#define FIRE_GRAVITY 0.001f
#define FIRE_SPEED	0.002f

#define FIRE_BBOX_WIDTH 7
#define FIRE_BBOX_HEIGHT 7


#define FIRE_STATE_TOP 234
#define FIRE_STATE_MID 235
#define FIRE_STATE_BOT 236

#define ID_ANI_FIRE 2345

class CFire : public CGameObject
{
protected:
	float ax;
	float ay;
	ULONGLONG fall_start;
	bool isCollidable = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return !isCollidable; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFire(float x, float y);
	virtual void SetState(int state);
};