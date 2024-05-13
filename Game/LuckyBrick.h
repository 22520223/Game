#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Coin.h"
#include "Mushroom.h"

#define ID_ANI_LUCKYBRICK 3500
#define LUCKYBRICK_WIDTH 16
#define LUCKYBRICK_BBOX_WIDTH 16
#define LUCKYBRICK_BBOX_HEIGHT 16

class CLuckyBrick : public CGameObject {
public:
	CLuckyBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};