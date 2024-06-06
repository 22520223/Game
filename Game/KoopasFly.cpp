#include "KoopasFly.h"
#include "CheckFall.h"
#include "PlayScene.h"
#include "LuckyBrick.h"
#include "Koopas.h"

CKoopasFly::CKoopasFly(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	isKicked = false;
	die_start = 0;
	SetState(KOOPASFLY_STATE_WALKING_LEFT);
}

void CKoopasFly::GetBoundingBox(float& left, float& top, float& right, float& bottom)
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

void CKoopasFly::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CKoopasFly::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	/*if (dynamic_cast<CKoopasFly*>(e->obj)) return;*/
	if (!haveCheck)
	{
		D3DXVECTOR2 koopasPosition = this->GetPosition();
		CCheckFall* checkfall = new CCheckFall(koopasPosition.x, koopasPosition.y);

		if (e->ny != 0 && ((GetState() == KOOPAS_STATE_WALKING_LEFT) || (GetState() == KOOPASFLY_STATE_WALKING_LEFT)))
		{
			checkfall->SetPosition(koopasPosition.x - 10, koopasPosition.y);
			checkfall->SetState(CHECKFALL_STATE_LEFT);
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (playScene)
			{
				playScene->AddObject(checkfall);
			}
		}
		else if (e->ny != 0 && ((GetState() == KOOPAS_STATE_WALKING_RIGHT) || (GetState() == KOOPASFLY_STATE_WALKING_RIGHT)))
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
		if (vx < 0 && state != KOOPASFLY_STATE_WALKING_LEFT)
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		else if (vx > 0 && state != KOOPASFLY_STATE_WALKING_RIGHT)
			SetState(KOOPAS_STATE_WALKING_LEFT);
		else if (vx < 0)
			SetState(KOOPASFLY_STATE_WALKING_RIGHT);
		else
			SetState(KOOPASFLY_STATE_WALKING_LEFT);
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	if (dynamic_cast<CLuckyBrick*>(e->obj))
		OnCollisionWithLuckyBrick(e);
}

void CKoopasFly::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
	else if ((state == KOOPAS_STATE_HOLD) && (GetTickCount64() - die_start > 8000))
	{
		SetState(KOOPAS_STATE_WALKING_LEFT);
		D3DXVECTOR2 koopasPosition = this->GetPosition();
		SetPosition(koopasPosition.x, koopasPosition.y - 5);
		isKicked = false;
	}


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CKoopasFly::Render()
{
	int aniId = ID_ANI_KOOPASFLY_WALKING_RIGHT;
	if (state == KOOPASFLY_STATE_WALKING_LEFT)
	{
		aniId = ID_ANI_KOOPASFLY_WALKING_LEFT;
	}
	else if (state == KOOPAS_STATE_IDLE || state == KOOPAS_STATE_HOLD)
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

void CKoopasFly::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPASFLY_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPASFLY_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_IDLE:
		vx = 0;
		ay = KOOPAS_GRAVITY;
		isKicked = true;
		die_start = GetTickCount64();
		haveCheck = false;
		break;
	case KOOPAS_STATE_KICK_LEFT:
		vx = KOOPAS_IDLE_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_KICK_RIGHT:
		vx = -KOOPAS_IDLE_SPEED;
		ay = KOOPAS_GRAVITY;
		break;
	case KOOPAS_STATE_HOLD:
		ay = 0;
		break;
	}
}

void CKoopasFly::OnCollisionWithLuckyBrick(LPCOLLISIONEVENT e)
{
	CLuckyBrick* luckybrick = dynamic_cast<CLuckyBrick*>(e->obj);
	if (GetState() == KOOPAS_STATE_KICK_LEFT || GetState() == KOOPAS_STATE_KICK_RIGHT)
	{
		if (e->nx != 0 and luckybrick->GetState() != LUCKYBRICK_STATE5)
		{
			luckybrick->SetState(LUCKYBRICK_STATE5);
			D3DXVECTOR2 luckyBrickPosition = luckybrick->GetPosition();
			if (checkLevel)
			{
				float mushroomX = luckyBrickPosition.x;
				float mushroomY = luckyBrickPosition.y - 20;

				CMushroom* mushroom = new CMushroom(mushroomX, mushroomY);
				mushroom->SetPosition(mushroomX, mushroomY);

				CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
				if (playScene)
				{
					playScene->AddObject(mushroom);
				}
			}
			else
			{
				float leafX = luckyBrickPosition.x;
				float leafY = luckyBrickPosition.y - 20;

				CLeaf* leaf = new CLeaf(leafX, leafY);
				leaf->SetPosition(leafX, leafY);

				CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
				if (playScene)
				{
					playScene->AddObject(leaf);
				}
			}
		}
	}
}