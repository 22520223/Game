#include"PlantBullet.h"
#include"Mario.h"
#include"Fire.h"
#include "PlayScene.h"

CPlantBullet::CPlantBullet(float x, float y) :CGameObject(x, y)
{
	this->ay = 0;
	shoot_time = -1;
	SetState(PLANTBULLET_STATE_TOP_LEFT);
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
	y += vy * dt;
};

//void CPlantBullet::OnCollisionWith(LPCOLLISIONEVENT e)
//{
//	if (!e->obj->IsBlocking()) return;
//	if (dynamic_cast<CPlantBullet*>(e->obj)) return;
//
//	if (e->ny != 0)
//	{
//		vy = 0;
//		isCollidable = true;
//	}
//}

void CPlantBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;

	CMario* mario = nullptr;
	
	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CMario*>(obj))
		{
			mario = dynamic_cast<CMario*>(obj);
			break;
		}
	}
	D3DXVECTOR2 plantPosition = this->GetPosition();
	D3DXVECTOR2 marioPosition = mario->GetPosition();
	
	float disPy = marioPosition.y - plantPosition.y;
	if (disPy > 20)
	{
		SetState(PLANTBULLET_STATE_BOT_LEFT);
	}
	else if (disPy < -20)
	{
		SetState(PLANTBULLET_STATE_TOP_LEFT);
	}
	else
	{
		SetState(PLANTBULLET_STATE_MID_LEFT);
	}
	if (shoot_time == -1)
		StartShoot();
	else if (GetTickCount64() - shoot_time > 5000)
	{
		LPGAMEOBJECT fire = new CFire(plantPosition.x, plantPosition.y);
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene != nullptr)
		{
			playScene->AddObject(fire);
		}
		shoot_time = -1;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CPlantBullet::Render()
{
	int aniId = ID_ANI_PLANTBULLET_TOP_LEFT;

	if (state == PLANTBULLET_STATE_BOT_LEFT)
	{
		aniId = ID_ANI_PLANTBULLET_BOT_LEFT;
	}

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