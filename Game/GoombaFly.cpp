#include "GoombaFly.h"
#include "Koopas.h"

CGoombafly::CGoombafly(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBAFLY_GRAVITY;
	die_start = -1;
	SetState(GOOMBAFLY_STATE_WALKING_LEFT);
}

void CGoombafly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBAFLY_STATE_DIE)
	{
		left = x - GOOMBAFLY_BBOX_WIDTH / 2;
		top = y - GOOMBAFLY_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBAFLY_BBOX_WIDTH;
		bottom = top + GOOMBAFLY_BBOX_HEIGHT_DIE;
	}
	else if (state == GOOMBAFLY_STATE_WALKING_LEFT || state == GOOMBAFLY_STATE_WALK || state == GOOMBAFLY_STATE_WALKING_RIGHT)
	{
		left = x - GOOMBAFLY_BBOX_WIDTH / 2;
		top = y - GOOMBAFLY_BBOX_HEIGHT / 2;
		right = left + GOOMBAFLY_BBOX_WIDTH;
		bottom = top + GOOMBAFLY_BBOX_HEIGHT;
	}
	else
	{
		left = x - GOOMBAFLY_BBOX_WIDTH / 2;
		top = y - GOOMBAFLY_BBOX_FLY_HEIGHT / 2;
		right = left + GOOMBAFLY_BBOX_WIDTH;
		bottom = top + GOOMBAFLY_BBOX_FLY_HEIGHT;
	}
}

void CGoombafly::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoombafly::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoombafly*>(e->obj)) return;
	if (state == GOOMBAFLY_STATE_FLY && e->ny < 0)
	{
		isOnPlatform = true;
	}
	else if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
}

void CGoombafly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBAFLY_STATE_DIE) && (GetTickCount64() - die_start > GOOMBAFLY_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	else if ((state == GOOMBAFLY_STATE_WALKING_LEFT || state == GOOMBAFLY_STATE_WALKING_RIGHT) && (GetTickCount64() - die_start > 1000))
	{
		SetState(GOOMBAFLY_STATE_FLY);
	}
	else if ((state == GOOMBAFLY_STATE_FLY) && isOnPlatform)
	{
		if (vx > 0)
			SetState(GOOMBAFLY_STATE_WALKING_RIGHT);
		else
			SetState(GOOMBAFLY_STATE_WALKING_LEFT);
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoombafly::Render()
{
	int aniId = ID_ANI_GOOMBAFLY_WALKING;
	if (state == GOOMBAFLY_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
	}
	else if (state == GOOMBAFLY_STATE_FLY)
		aniId = ID_ANI_GOOMBAFLY_FLY;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CGoombafly::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBAFLY_STATE_DIE:
		die_start = GetTickCount64();
		y += (GOOMBAFLY_BBOX_HEIGHT - GOOMBAFLY_BBOX_HEIGHT_DIE) / 2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case GOOMBAFLY_STATE_WALKING_LEFT:
		die_start = GetTickCount64();
		vx = -GOOMBAFLY_WALKING_SPEED;
		break;
	case GOOMBAFLY_STATE_WALKING_RIGHT:
		die_start = GetTickCount64();
		vx = GOOMBAFLY_WALKING_SPEED;
		break;
	case GOOMBAFLY_STATE_WALK:
		vx = -GOOMBAFLY_WALKING_SPEED;
		break;
	case GOOMBAFLY_STATE_DEFLECT:
		vy = -GOOMBAFLY_DEFLECT_SPEED;
		break;
	case GOOMBAFLY_STATE_FLY:
		vy = -GOOMBAFLY_DEFLECT_SPEED;
		isOnPlatform = false;
		break;
	}
}

void CGoombafly::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (koopas->GetState() == KOOPAS_STATE_KICK_LEFT || koopas->GetState() == KOOPAS_STATE_KICK_RIGHT)
	{
		SetState(GOOMBAFLY_STATE_DEFLECT);
	}
}