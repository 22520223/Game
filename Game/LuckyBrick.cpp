#include"LuckyBrick.h"

void CLuckyBrick::Render()
{
	int aniId = ID_ANI_LUCKYBRICK;
	if (state == LUCKYBRICK_STATE5)
	{
		aniId = ID_ANI_LUCKYBRICK_STATE5;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CLuckyBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LUCKYBRICK_BBOX_WIDTH / 2;
	t = y - LUCKYBRICK_BBOX_HEIGHT / 2;
	r = l + LUCKYBRICK_BBOX_WIDTH;
	b = t + LUCKYBRICK_BBOX_HEIGHT;
}

bool CLuckyBrick::IsBreak()
{
	if (state == LUCKYBRICK_STATE5)
		return 1;
	return 0;
}