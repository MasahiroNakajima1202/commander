//*****************************************************************************
//  2D用頂点シェーダ
//  author: 中島将浩
//  update: 2015/06/08
//*****************************************************************************
#ifndef _VS_2D_H_
#define _VS_2D_H_

#include "vertex_shader.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class VS2D : public VertexShader{
private:
	VS2D(){}
public:

	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	VS2D(Renderer *master_renderer);

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~VS2D();

	void Set(void);

	//accessor
	virtual void SetWorld(D3DXMATRIX* value){ _world = *value; }
	virtual void SetView(D3DXMATRIX* value){}
	virtual void SetProjection(D3DXMATRIX* value){}
	virtual void SetLightDirection(D3DXVECTOR3 value){}
	virtual void SetLightDiffuse(D3DXVECTOR4 value){}
	virtual void SetMaterialDiffuse(D3DXVECTOR4 value){}

protected:
};

//accessor

#endif//_VERTEX_SHADER_H_