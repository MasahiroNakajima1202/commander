//*****************************************************************************
//  2D用ピクセルシェーダ
//  author: 中島将浩
//  update: 2015/10/28
//*****************************************************************************
#include "ps2d.h"

//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
PS2D::PS2D(Renderer *master_renderer):
PixelShader(master_renderer, "data/SHADER/shader2d.hlsl", "PSTexture"){
}

//*****************************************************************************
//【デス様】
//  あとかたづけ
//  引数: なし
//*****************************************************************************
PS2D::~PS2D(){}

