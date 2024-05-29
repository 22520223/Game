#include"Fire.h"
#include"PlantBullet.h"

CFire::CFire(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	fall_start = -1;
	SetState(FIRE_STATE_BOT);
}

void CFire::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BBOX_WIDTH / 2;
	top = y - FIRE_BBOX_HEIGHT / 2;
	right = left + FIRE_BBOX_WIDTH;
	bottom = top + FIRE_BBOX_HEIGHT;
}

void CFire::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFire::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFire*>(e->obj)) return;

	isCollidable = true;
	
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;
	vx = ax * dt;



	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFire::Render()
{
	int aniId = ID_ANI_FIRE;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFire::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIRE_STATE_MID:
		ay = 0;
		ax = -FIRE_SPEED;
		break;
	case FIRE_STATE_TOP:
		ay = -FIRE_GRAVITY;
		ax = -FIRE_SPEED;
		break;
	case FIRE_STATE_BOT:
		ay = FIRE_GRAVITY;
		ax = -FIRE_SPEED;
		break;
	}
}