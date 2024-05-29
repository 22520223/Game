#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Mushroom.h"
#include "LuckyBrick.h"
#include "LuckyBrickCoin.h"
#include "Block.h"
#include "Koopas.h"
#include "PlayScene.h"
#include "GoombaFly.h"
#include "Leaf.h"

#include "Collision.h"
//#include "SampleKeyEventHandler.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (abs(vx) > abs(maxVx)) vx = maxVx;
	CKoopas* koopas = nullptr;

	for (size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT obj = coObjects->at(i);
		if (dynamic_cast<CKoopas*>(obj))
		{
			koopas = dynamic_cast<CKoopas*>(obj);
			break;
		}
	}
	D3DXVECTOR2 marioPosition = this->GetPosition();

	if (koopas->GetState() == KOOPAS_STATE_HOLD)
	{
		if (nx > 0)
			koopas->SetPosition(marioPosition.x + 13, marioPosition.y - 2);
		else
			koopas->SetPosition(marioPosition.x - 13, marioPosition.y - 2);
		if (!isJKeyDown && nx <= 0)
			koopas->SetState(KOOPAS_STATE_KICK_RIGHT);
		else if (!isJKeyDown && nx > 0)
			koopas->SetState(KOOPAS_STATE_KICK_LEFT);
	}
	
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLuckyBrick*>(e->obj))
		OnCollisionWithLuckyBrick(e);
	else if (dynamic_cast<CLuckyBrickCoin*>(e->obj))
		OnCollisionWithLuckyBrickCoin(e);
	//else if (dynamic_cast<CBlock*>(e->obj))
	//	OnCollisionWithBlock(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	if (dynamic_cast<CGoombafly*>(e->obj))
		OnCollisionWithGoombaFly(e);
	if (dynamic_cast<CLeaf*>(e->obj))
		OnCollisionWithLeaf(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0 && goomba->GetState() != GOOMBA_STATE_DEFLECT)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_SUPER)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);

	if (e->ny != 0 || e->nx != 0)
	{
			if (level < MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_BIG;
				if (isOnPlatform)
					vy = -0.2f;
			}
			e->obj->Delete();
	}
}

void CMario::OnCollisionWithLuckyBrick(LPCOLLISIONEVENT e)
{
	CLuckyBrick* luckybrick = dynamic_cast<CLuckyBrick*>(e->obj);

	if (e->ny > 0 and luckybrick->GetState() != LUCKYBRICK_STATE5)
	{
		luckybrick->SetState(LUCKYBRICK_STATE5);
		D3DXVECTOR2 luckyBrickPosition = luckybrick->GetPosition();
		if (level == MARIO_LEVEL_SMALL)
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

void CMario::OnCollisionWithLuckyBrickCoin(LPCOLLISIONEVENT e)
{
	CLuckyBrickCoin* luckybrickcoin = dynamic_cast<CLuckyBrickCoin*>(e->obj);

	if (e->ny > 0 and luckybrickcoin->GetState() != LUCKYBRICK_STATE5)
	{
		coin++;
		luckybrickcoin->SetState(LUCKYBRICK_STATE5);
		D3DXVECTOR2 luckyBrickCoinPosition = luckybrickcoin->GetPosition();
		float coinX = luckyBrickCoinPosition.x;
		float coinY = luckyBrickCoinPosition.y - 20;

		CCoin* coin = new CCoin(coinX, coinY);
		coin->SetPosition(coinX, coinY);
		coin->SetState(COIN_DEFLECT);
		
		CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
		if (playScene)
		{
			playScene->AddObject(coin);
		}
	}
}

void CMario::OnCollisionWithGoombaFly(LPCOLLISIONEVENT e)
{
	CGoombafly* goombafly = dynamic_cast<CGoombafly*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goombafly->GetState() == GOOMBAFLY_STATE_WALKING_LEFT ||
			goombafly->GetState() == GOOMBAFLY_STATE_WALKING_RIGHT ||
			goombafly->GetState() == GOOMBAFLY_STATE_FLY)
		{
			if (goombafly->GetVx() < 0)
				goombafly->SetState(GOOMBAFLY_STATE_WALK_LEFT);
			else 
				goombafly->SetState(GOOMBAFLY_STATE_WALK_RIGHT);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goombafly->GetState() == GOOMBAFLY_STATE_WALK_LEFT || goombafly->GetState() == GOOMBAFLY_STATE_WALK_RIGHT)
		{
			goombafly->SetState(GOOMBAFLY_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0 && goombafly->GetState() != GOOMBA_STATE_DEFLECT)
		{
			if (goombafly->GetState() != GOOMBA_STATE_DIE)
			{
				if (level == MARIO_LEVEL_SUPER)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

//void CMario::OnCollisionWithBlock(LPCOLLISIONEVENT e)
//{
//	CBlock* block = dynamic_cast<CBlock*>(e->obj);
//
//	if (e->ny < 0)
//	{
//		
//		vy = 0;
//		isOnPlatform = true;
//	}
//}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	D3DXVECTOR2 marioPosition = this->GetPosition();
	float marioX = marioPosition.x;
	D3DXVECTOR2 koopasPosition = koopas->GetPosition();
	float koopasX = koopasPosition.x;
	if (e->ny < 0)
	{
		float distance = marioX - koopasX;
		if (koopas->GetState() == KOOPAS_STATE_WALKING_LEFT || koopas->GetState() == KOOPAS_STATE_WALKING_RIGHT)
		{
			koopas->SetState(KOOPAS_STATE_IDLE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_IDLE)
		{
			if (distance > 0)
			{
				koopas->SetPosition(koopasPosition.x, koopasPosition.y - 5);
				koopas->SetState(KOOPAS_STATE_KICK_RIGHT);
			}
			else
			{
				koopas->SetPosition(koopasPosition.x, koopasPosition.y - 5);
				koopas->SetState(KOOPAS_STATE_KICK_LEFT);
			}

			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_KICK_LEFT || koopas->GetState() == KOOPAS_STATE_KICK_RIGHT)
		{
			koopas->SetPosition(koopasPosition.x, koopasPosition.y - 5);
			koopas->SetState(KOOPAS_STATE_IDLE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() == KOOPAS_STATE_IDLE)
			{
				if (isJKeyDown)
				{
					koopas->SetState(KOOPAS_STATE_HOLD);
				}
				else if (e->nx < 0 && !isJKeyDown)
					koopas->SetState(KOOPAS_STATE_KICK_LEFT);
				else if (e->nx > 0 && !isJKeyDown)
					koopas->SetState(KOOPAS_STATE_KICK_RIGHT);
			}
			else
			{
				if (level == MARIO_LEVEL_SUPER)
				{
					level = MARIO_LEVEL_BIG;
					StartUntouchable();
				}
				else if (level == MARIO_LEVEL_BIG)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);

	if (e->ny != 0 || e->nx != 0)
	{
		if (level < MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_BIG;
			if (isOnPlatform)
				vy = -0.2f;
		}
		else if (level == MARIO_LEVEL_BIG)
		{
			level = MARIO_LEVEL_SUPER;
		}
		e->obj->Delete();
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdSuper()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SUPER_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SUPER_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SUPER_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SUPER_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SUPER_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SUPER_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SUPER_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SUPER_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SUPER_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SUPER_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SUPER_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SUPER_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SUPER_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SUPER_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SUPER_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_SUPER)
		aniId = GetAniIdSuper();

	animations->Get(aniId)->Render(x, y);

	//RenderBoundingBox();

	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_SUPER)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
