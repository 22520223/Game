#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

class CLuckyBrickCoin : public CGameObject {
public:
	CLuckyBrickCoin(float x, float y) : CGameObject(x, y) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	D3DXVECTOR2 GetPosition()
	{
		return D3DXVECTOR2(x, y);
	}
};