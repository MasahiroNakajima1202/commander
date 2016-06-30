//*****************************************************************************
//  タイルによる地形
//  author: 中島将浩
//  update: 2016/02/24
//*****************************************************************************
#ifndef _TILE_FIELD_H_
#define _TILE_FIELD_H_

#include "main.h"
#include "model_field.h"

#include <d3dx9.h>


//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class TileFieldImage;
class TileField : public ModelField{
public:


	TileField(Renderer *renderer, int width, int depth);

	virtual ~TileField();

	virtual void Update(void);

	virtual float GetHeight(float x, float z);
	virtual int GetIndexHeight(int x_index, int z_index);

	virtual bool FixLay(D3DXVECTOR3 &dst, D3DXVECTOR3 src, D3DXVECTOR3 begin);

	


	//void StackTile(float x, float z);
	void StackTile(int x_index, int z_index, int number = 1);
	void LeaveTile(int x_index, int z_index, int number = 1);
	virtual void CommitImage(void);

	int GetWidth(void){return _width;}
	int GetDepth(void){return _depth;}

	//マイナスだろうとお構いなしのindex換算
	void PositionToIndex(float x, float z, int& x_index, int& z_index);

	//accessor
	static float GetTileSize(void){return TILE_SIZE;}
	static float GetTileHeight(void){return TILE_HEIGHT;}
	static int GetTileStackLimit(void){return TILE_STACK_LIMIT;}
private:
	static const float TILE_SIZE;
	static const float TILE_HEIGHT;
	static const int TILE_STACK_LIMIT;
	int _width;
	int _depth;
	int *_height_map;
	TileFieldImage* _image;


	float GetXDistance(float x);
	float GetZDistance(float z);
};


#endif//_NUMBER_H_