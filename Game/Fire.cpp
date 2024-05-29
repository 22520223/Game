#include"Fire.h"

CFire::CFire(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = FIRE_GRAVITY;
	fall_start = -1;
	SetState(FIRE_STATE_TOP);
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

	if (e->ny != 0)
	{
		vy = 0;
		isCollidable = true;
	}
}

void CFire::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;
	vx += ax * dt;



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

	}
}