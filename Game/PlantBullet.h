#pragma once
#include "GameObject.h"

#define PLANTBULLET_GRAVITY 0.001f
#define PLANTBULLET_SPEED	0.05f

#define PLANTBULLET_BBOX_WIDTH 16
#define PLANTBULLET_BBOX_HEIGHT 32


#define PLANTBULLET_STATE_TOP 1234
//#define PLANTBULLET_STATE_MID 1235
#define PLANTBULLET_STATE_BOT 1236
#define PLANTBULLET_STATE_DIE 1240

#define ID_ANI_PLANTBULLET_TOP 1237		
//#define ID_ANI_PLANTBULLET_MID  1238
#define ID_ANI_PLANTBULLET_BOT 1239

class CPlantBullet : public CGameObject
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
	CPlantBullet(float x, float y);
	virtual void SetState(int state);
};