#include"PlantBullet.h"
#include"Koopas.h"

CPlantBullet::CPlantBullet(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = PLANTBULLET_GRAVITY;
	fall_start = -1;
	SetState(PLANTBULLET_STATE_TOP);
}

void CPlantBullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PLANTBULLET_BBOX_WIDTH / 2;
	top = y - PLANTBULLET_BBOX_HEIGHT / 2;
	right = left + PLANTBULLET_BBOX_WIDTH;
	bottom = top + PLANTBULLET_BBOX_HEIGHT;
}

void CPlantBullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CPlantBullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPlantBullet*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
		isCollidable = true;
	}
}

void CPlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;
	vx += ax * dt;



	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlantBullet::Render()
{
	int aniId = ID_ANI_PLANTBULLET_TOP;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPlantBullet::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLANTBULLET_STATE_DIE:
		this->Delete();
		break;
	}
}