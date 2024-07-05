#pragma once
#include <string>
#include <iostream>
#include <list>

#include "debug.h"
#include "Effects.h"
#include "PlayScene.h"

class CObjectPool
{
private:
	list<CEffects*> effects;
	bool isInit;
	static CObjectPool* instance;
	CObjectPool() {
		isInit = false;
	}
	~CObjectPool()
	{
		for (auto it = effects.begin(); it != effects.end(); ++it) {
			delete* it;
		}
		Unload();
	}
public:
	static CObjectPool* getInstance()
	{
		if (instance == NULL)
		{
			DebugOut(L"[INFO]Creating ObjectPool.\n");
			instance = new CObjectPool;
		}
		return instance;
	}

	static void Release()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	CEffects* getEffect()
	{
		CEffects* effect = effects.front();
		effects.pop_front();
		effects.push_back(effect);
		return effect;
	}

	void getEffectBreakBrick(float objX, float objY)
	{
		for (int i = 0; i < 4; i++)
		{
			CEffects* effect = effects.front();
			effects.pop_front();
			effects.push_back(effect);
			effect->SetValue(objX, objY, EFFECT_TYPE_BREAK_BRICK, 0);
		}
	}

	void returnEffect(CEffects* effect)
	{
		effect->reset();
		effects.push_back(effect);
	}

	void startInit()
	{
		if (isInit == true) return;
		for (int i = 0; i < 12; i++)
		{
			CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			CEffects* effect = new CEffects;
			effects.push_back(effect);
			playScene->AddObject(effect);
		}
		isInit = true;
	}

	void Unload()
	{
		isInit = false;
		effects.clear();
	}
};
typedef CObjectPool* LPOBJECTPOOL;