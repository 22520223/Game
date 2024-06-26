#include "TileMap.h"
#include "AssetIDs.h"
#include "Utils.h"
#include "Define.h"

CTileMap::CTileMap(int ID, LPCWSTR filePathTexture, LPCWSTR filePathData,
	int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
	this->ID = ID;
	this->filePathTexture = filePathTexture;
	this->filePathData = filePathData;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	this->filePathData = ToLPCWSTR("tileset.txt");

	numsCol = this->mapWidth / this->tileWidth;
	numsRow = this->mapHeight / this->tileHeight;
	LoadResources();
	LoadMap();
	CreateZoneToDraw();
}

void CTileMap::LoadResources()
{
	CTextures* texture = CTextures::GetInstance();
	texture->Add(ID, filePathTexture);
	LPTEXTURE texTileMap = texture->Get(ID);
	int textureWidth = 320;
	int textureHeight = 96;
	int level = 0;
	if (ID == SCENE_INTRO) {}
	else if (ID == SCENE_1) {
		textureWidth = 320;
		textureHeight = 96;
	}
	else if (ID == SCENE_2)
	{

	}
	int numsColToRead = textureWidth / tileWidth;
	int numsRowToRead = textureHeight / tileHeight;

	int idSprite = 1;
	for (int i = 0; i < numsRowToRead; i++)
	{
		for (int j = 0; j < numsColToRead; j++)
		{
			int idTile = ID_TILE + idSprite;
			sprites->Add(idTile, tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1), texTileMap);
			idSprite += 1;
		}
	}
}

void CTileMap::LoadMap()
{
	fstream fs;
	fs.open(filePathData, ios::in);

	if (fs.fail())
	{
		DebugOut(L"[ERROR] TileMap::Load_MapData failed: ID=%d", ID);
		fs.close();
		return;
	}
	string line;
	while (!fs.eof())
	{
		getline(fs, line);
		vector<LPSPRITE> spriteline;
		stringstream ss(line);
		int n;

		while (ss >> n)
		{
			int idTile = ID_TILE + n;
			spriteline.push_back(sprites->Get(idTile));
		}
		tilemap.push_back(spriteline);
	}
	fs.close();
}

void CTileMap::CreateZoneToDraw()
{
	//Dont has any ideal at here
	switch (ID)
	{
	case SCENE_MENU:
		break;
	case SCENE_1:
		limitColToDraw.push_back({ 0,160 });
		break;
	case SCENE_2:
		break;
	}
}

void CTileMap::Draw(D3DXVECTOR3 camPosition, bool isCrossEffect)
{
	int startColDraw = (int)camPosition.x / tileWidth;
	int endColDraw = startColDraw + SCREEN_WIDTH / tileWidth;

	for (int i = 0; i < numsRow; i++)
	{
		for (int j = startColDraw; j <= endColDraw; j++)
		{
			float x = float(tileWidth * (j - startColDraw) + camPosition.x - (int)camPosition.x);
			float y = float(tileHeight * i);
			tilemap[i][j]->Draw(x, y);
		}
	}
}