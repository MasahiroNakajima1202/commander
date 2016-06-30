//*****************************************************************************
//  インスタンシング用頂点シェーダ
//  author: 中島将浩
//  update: 2016/03/09
//*****************************************************************************
#ifndef _VS_INSTANCING_H_
#define _VS_INSTANCING_H_

#include "vertex_shader.h"
#include "renderer.h"

//*****************************************************************************
//  constant
//*****************************************************************************

//*****************************************************************************
//  class
//*****************************************************************************
class Renderer;
class VSInstancing : public VertexShader{
private:
	VSInstancing(){}
public:

	//*****************************************************************************
	//【コンストラクタ】
	//  頂点バッファNULL詰めなど
	//  引数: なし
	//*****************************************************************************
	VSInstancing(Renderer *master_renderer);

	//*****************************************************************************
	//【デス様】
	//  あとかたづけ
	//  引数: なし
	//*****************************************************************************
	virtual ~VSInstancing();

	virtual void Set(void);

	//accessor

protected:
};

//accessor

#endif//_VERTEX_SHADER_H_