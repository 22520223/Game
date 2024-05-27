#include "Koopas.h"
#include "CheckFall.h"
#include "PlayScene.h"
CKoopas::CKoopas(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	isKicked = false;
	die_start = 0;
	SetState(KOOPAS_STATE_WALKING_LEFT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_IDLE or state == KOOPAS_STATE_KICK_LEFT or state == KOOPAS_STATE_KICK_RIGHT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT_IDLE / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT_IDLE;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	/*if (dynamic_cast<CKoopas*>(e->obj)) return;*/
	if (!haveCheck)
	{
		D3DXVECTOR2 koopasPosition = this->GetPosition();
		CCheckFall* checkfall = new CCheckFall(koopasPosition.x, koopasPosition.y);

		if (e->ny != 0 && GetState() == KOOPAS_STATE_WALKING_LEFT)
		{
			checkfall->SetPosition(koopasPosition.x - 10, koopasPosition.y);
			checkfall->SetState(CHECKFALL_STATE_LEFT);
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (playScene)
			{
				playScene->AddObject(checkfall);
			}
		}
		else if (e->ny != 0 && GetState() == KOOPAS_STATE_WALKING_RIGHT)
		{
			checkfall->SetPosition(koopasPosition.x + 10, koopasPosition.y);
			checkfall->SetState(CHECKFALL_STATE_RIGHT);
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (playScene)
			{
				playScene->AddObject(checkfall);
			}
		}
		
		haveCheck = true;
	}
	
	if (e->ny != 0)
	{
		vy = 0;
		isOnPlatform = true;
	}
	else if (GetState() != KOOPAS_STATE_KICK_LEFT && GetState() != KOOPAS_STATE_KICK_RIGHT && GetState() != KOOPAS_STATE_IDLE)
	{
		if (vx < 0)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		else
			SetState(KOOPAS_STATE_WALKING_LEFT);
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if ((state == KOOPAS_STATE_IDLE) && (GetTickCount64() - die_start > KOOPAS_DIE_TIMEOUT))
	{
		SetState(KOOPAS_STATE_WALKING_LEFT);
		D3DXVECTOR2 koopasPosition = this->GetPosition();
		SetPosition(koopasPosition.x, koopasPosition.y - 5);
		isKicked = false;
	}

	

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	if (state == KOOPAS_STATE_WALKING_LEFT)
	{
		aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	}
	else if (state == KOOPAS_STATE_IDLE)
	{
		aniId = ID_ANI_KOOPAS_IDLE;
	}
	else if (state == KOOPAS_STATE_KICK_LEFT)
	{
		aniId = ID_ANI_KOOPAS_IDLE_RIGHT;
	}
	else if (state == KOOPAS_STATE_KICK_RIGHT)
	{
		aniId = ID_ANI_KOOPAS_IDLE_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_IDLE:
		vx = 0;
		isKicked = true;
		die_start = GetTickCount64();
		haveCheck = false;
		break;
	case KOOPAS_STATE_KICK_LEFT:
		vx = KOOPAS_IDLE_SPEED;
		break;
	case KOOPAS_STATE_KICK_RIGHT:
		vx = -KOOPAS_IDLE_SPEED;
		break;
	}
}
