//*****************************************************************************
//  sceneモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************
#include "object_effect.h"
#include "renderer.h"
//#include <Effekseer.h>

const wchar_t* ObjectEffect::FILENAME_TABLE[EFFECT_TYPE::MAX] = {
	L"data/EFFECT/actor_select.efk",
};
const int ObjectEffect::FRAME_TABLE[EFFECT_TYPE::MAX] = {
	120,	   //TEST,
};


//*****************************************************************************
//【コンストラクタ】
//  頂点バッファNULL詰めなど
//  引数: なし
//*****************************************************************************
ObjectEffect::ObjectEffect(Renderer *master_renderer, int layer_no):
Object(master_renderer, layer_no),
_image(nullptr),
_handle(-1),
_loop(false),
_time(0),
_type(MAX){
}

//*****************************************************************************
//【初期化】
//  返り値: 初期化に成功したかどうか
//  引数: なし
//*****************************************************************************
HRESULT ObjectEffect::SetUp(EFFECT_TYPE type){
	//_type = type;
	//Effekseer::Manager* manager(_renderer->GetEffekseerManager());
	//_image = Effekseer::Effect::Create(manager, (EFK_CHAR*)(FILENAME_TABLE[type]));

	return S_OK;
}

//*****************************************************************************
//【終了】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectEffect::Release(void){
	//Effekseer::Manager* manager(_renderer->GetEffekseerManager());
	//if(_image != nullptr){
	//	if(_handle != -1){
	//		manager->StopEffect(_handle);
	//		_handle = -1;
	//	}
	//	_image->Release();
	//	_image = nullptr;
	//}
}

//*****************************************************************************
//【更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectEffect::Update(void){
	//Effekseer::Manager* manager(_renderer->GetEffekseerManager());
	//if(_time == FRAME_TABLE[_type]){
	//	if(_loop){
	//		Play(_loop);
	//	}
	//	else{
	//		_handle = -1;
	//	}
	//}

	//_time++;
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void ObjectEffect::Draw(void){
	//Effekseer::Manager* manager(_renderer->GetEffekseerManager());
	//EffekseerRenderer::Renderer* effekseer_renderer(_renderer->GetEffekseerRenderer());

	//_renderer->SetCurrentShader();

	////transform更新
	//if (_handle != -1){
	//	D3DXMATRIX view(_renderer->GetView());
	//	D3DXMATRIX translation, scaling, rotation;
	//	D3DXMatrixTranslation(&translation, _position.x, _position.y, _position.z);
	//	D3DXMatrixRotationYawPitchRoll(&rotation, _rotation.y, _rotation.x, _rotation.z);
	//	D3DXMatrixScaling(&scaling, _size.x, _size.y, _size.z);
	//	D3DXMATRIX world_view = scaling * rotation * translation * view;

	//	Effekseer::Matrix44 matrix;
	//	for(int i=0; i<4; i++){
	//		for(int j=0; j<4; j++){
	//			matrix.Values[i][j] = world_view.m[i][j];
	//		}
	//	}
	//	effekseer_renderer->SetCameraMatrix(matrix);

	//	manager->DrawHandle(_handle);
	//}

}

void ObjectEffect::Play(bool loop){
	//_loop = loop;
	//Effekseer::Manager* manager(_renderer->GetEffekseerManager());
	//_handle = manager->Play(_image, 0.0f, 0.0f, 0.0f);
	//_time = 0;
}