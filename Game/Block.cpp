#include "Block.h"

void CBlock::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BLOCK)->Render(x, y);
	//RenderBoundingBox();
}

void CBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BLOCK_BBOX_WIDTH / 2;
	t = y - BLOCK_BBOX_HEIGHT / 2;
	r = l + BLOCK_BBOX_WIDTH;
	b = t + BLOCK_BBOX_HEIGHT;
}

int CBlock::IsDirectionColliable(float nx, float ny)
{
	if (ny == -1)
		return 1;
	else
		return 0;
}