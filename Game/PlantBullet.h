#pragma once
#include "GameObject.h"

#define PLANTBULLET_GRAVITY 0.001f
#define PLANTBULLET_SPEED	0.05f

#define PLANTBULLET_BBOX_WIDTH 16
#define PLANTBULLET_BBOX_HEIGHT 32


#define PLANTBULLET_STATE_TOP_LEFT 1234
#define PLANTBULLET_STATE_MID_LEFT 1235
#define PLANTBULLET_STATE_BOT_LEFT 1236

#define PLANTBULLET_STATE_TOP_RIGHT 1254
#define PLANTBULLET_STATE_MID_RIGHT 1255
#define PLANTBULLET_STATE_BOT_RIGHT 1256
#define PLANTBULLET_STATE_DIE 1240

#define ID_ANI_PLANTBULLET_TOP_LEFT 1237		
#define ID_ANI_PLANTBULLET_BOT_LEFT 1239

#define ID_ANI_PLANTBULLET_TOP_RIGHT 1241		
#define ID_ANI_PLANTBULLET_BOT_RIGHT 1242

class CPlantBullet : public CGameObject
{
protected:
	float ay;
	ULONGLONG shoot_time;
	bool isCollidable = false;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return !isCollidable; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	//virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CPlantBullet(float x, float y);
	virtual void SetState(int state);
	D3DXVECTOR2 GetPosition()
	{
		return D3DXVECTOR2(x, y);
	}
	void StartShoot() { shoot_time = GetTickCount64(); }
};