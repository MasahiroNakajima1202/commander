//*****************************************************************************
//  sceneモジュール
//  サンプルシーン
//  author: 中島将浩
//  update: 2014/04/15
//*****************************************************************************

#include "renderer.h"
#include "object.h"

Object *Object::_top[DRAW_LAYER_MAX] = {};

//*****************************************************************************
//【初期化】
//*****************************************************************************
HRESULT Object::SetUp(void){
	//_next = nullptr;
	_death = false;
	_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_pre_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	_radius = 0.0f;

	return S_OK;
}

//*****************************************************************************
//【更新】
//*****************************************************************************
void Object::Update(void){
	_pre_position = _position;
	_position += _velocity;

	_pre_rotation = _rotation;
}

//*****************************************************************************
//【リストへ参加】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object::PushBackToList(int layer_no){
	Object *cur = nullptr;
	if(_top[layer_no] == nullptr){//最初のひとり
		_top[layer_no] = this;
		return;
	}

	//二人目以降
	cur = _top[layer_no];

	//curを末尾まで動かす
	while(cur->_next != nullptr){
		cur = cur->_next;
	}

	//curに要素追加
	cur->_next = this;
}

//*****************************************************************************
//【リストから削除】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object::RemoveFromList(int layer_no){
	Object *cur = nullptr;
	Object *pre = nullptr;
	
	cur = _top[layer_no];
	//ぼくが見つかるまで進める 念のためnullptr checkも ありえないけど
	while(cur != this && cur != nullptr){
		pre = cur;
		cur = cur->_next;
	}

	if(cur == nullptr){//ぼくがいなかった
		return;	//ｱｰﾘｴｰﾝ
	}

	if(cur == _top[layer_no]){
		_top[layer_no] = cur->_next;
	}
	else{
		pre->_next = cur->_next;
	}
}


//*****************************************************************************
//【全更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object::UpdateAll(void){
	Object *cur = nullptr;
	int i = 0;					//loop index

	for(i=0; i<DRAW_LAYER_MAX; i++){
		cur = _top[i];
		while(cur != nullptr){
			cur->Update();
			cur = cur->_next;
		}
	}
}

//*****************************************************************************
//【描画】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object::DrawAll(void){
	Object *cur = nullptr;
	int i = 0;					//loop index

	for(i=0; i<DRAW_LAYER_MAX; i++){
		cur = _top[i];
		while(cur != nullptr){
			if(cur->_visible){
				cur->Draw();
			}
			cur = cur->_next;
		}
	}
}

void Object::DrawLayer(DRAW_LAYER layer){
	Object *cur = nullptr;

	cur = _top[layer];
	while (cur != nullptr){
		if (cur->_visible){
			cur->Draw();
		}
		cur = cur->_next;
	}
}


//*****************************************************************************
//【しね！ハイエナどもめ！】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object::DestroyAll(void){
	int i = 0;					//loop index
	for(i=0; i<DRAW_LAYER_MAX; i++){
		while(_top[i] != nullptr){
			_top[i]->Release();
			delete _top[i];
		}
	}
}

//*****************************************************************************
//【全更新】
//  返り値: なし
//  引数: なし
//*****************************************************************************
void Object::Flush(void){
	Object *cur = nullptr;
	Object *next = nullptr;
	int i = 0;					//loop index

	for(i=0; i<DRAW_LAYER_MAX; i++){
		cur = _top[i];
		while(cur != nullptr){
			next = cur->_next;
			if(cur->_death){
				cur->Release();
				delete cur;
			}
			cur = next;
		}
	}
}



//*****************************************************************************
//【こいつ、います？】
//  対象のオブジェクトが存在するかどうか
//  返り値: なし
//  引数: なし
//*****************************************************************************
bool Object::Extist(Object *object){
	int i = 0;					//loop index
	Object *cur = nullptr;

	for(i=0; i<DRAW_LAYER_MAX; i++){
		cur = _top[i];
		while(cur != nullptr){
			if(cur == object){
				return true;
			}
			cur = cur->_next;
		}
	}

	//いなかったよ……
	return false;
}

//*****************************************************************************
//【当たり判定(球と球)】
//  二つのオブジェクトの当たり判定を調べます as ball and ball
//  返り値: なし
//  引数: なし
//*****************************************************************************
bool Object::HitCheckBallBall(Object* ball_a, Object* ball_b){
	float sum = ball_a->_radius + ball_b->_radius;
	D3DXVECTOR3 v = ball_a->_position - ball_b->_position;
	float sq_length = v.x*v.x + v.y*v.y + v.z*v.z;

	if(sum*sum < sq_length){
		return false;
	}
	
	return true;
}

//*****************************************************************************
//【当たり判定(点と箱)】
//  二つのオブジェクトの当たり判定を調べます as point and box
//  返り値: なし
//  引数: なし
//*****************************************************************************
bool Object::HitCheckPointBox(Object* point, Object* box){
	D3DXVECTOR3 box_position(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 box_rotation(0.0f, 0.0f, 0.0f);
	D3DXMATRIX rot_mtx, trs_mtx, inv_mtx;
	bool ret = false;

	//boxのposrotを両方に逆算
	D3DXMatrixIdentity(&inv_mtx);
	D3DXMatrixTranslation(&trs_mtx, box->_position.x, box->_position.y, box->_position.z);
	D3DXMatrixRotationYawPitchRoll(&rot_mtx, box->_rotation.y, box->_rotation.x, box->_rotation.z);
	D3DXMatrixMultiply(&inv_mtx, &inv_mtx, &rot_mtx);
	D3DXMatrixMultiply(&inv_mtx, &inv_mtx, &trs_mtx);
	D3DXMatrixInverse(&inv_mtx, nullptr, &inv_mtx);

	D3DXVECTOR3 point_pos = point->_position;
	D3DXVec3TransformCoord(&point_pos, &point_pos, &inv_mtx);

	if(-box->_size.x/2.0f < point_pos.x && point_pos.x < box->_size.x/2.0f
	&& -box->_size.y/2.0f < point_pos.y && point_pos.y < box->_size.y/2.0f
	&& -box->_size.z/2.0f < point_pos.z && point_pos.z < box->_size.z/2.0f){
		ret = true;
	}

	return ret;
}

//*****************************************************************************
//【当たり判定(点と円柱)】
//  二つのオブジェクトの当たり判定を調べます as point and pole
//  返り値: なし
//  引数: なし
//*****************************************************************************
bool Object::HitCheckPointPole(Object* point, Object* pole){
	D3DXVECTOR3 pole_position(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pole_rotation(0.0f, 0.0f, 0.0f);
	D3DXMATRIX rot_mtx, trs_mtx, inv_mtx;
	bool ret = false;

	//boxのposrotを両方に逆算
	D3DXMatrixIdentity(&inv_mtx);
	D3DXMatrixTranslation(&trs_mtx, pole->_position.x, pole->_position.y, pole->_position.z);
	D3DXMatrixRotationYawPitchRoll(&rot_mtx, pole->_rotation.y, pole->_rotation.x, pole->_rotation.z);
	D3DXMatrixMultiply(&inv_mtx, &inv_mtx, &rot_mtx);
	D3DXMatrixMultiply(&inv_mtx, &inv_mtx, &trs_mtx);
	D3DXMatrixInverse(&inv_mtx, nullptr, &inv_mtx);

	D3DXVECTOR3 point_pos = point->_position;
	D3DXVec3TransformCoord(&point_pos, &point_pos, &inv_mtx);

	//高さ判定
	if(point_pos.y > pole->_size.y / 2.0f + point->_radius
	|| point_pos.y < -pole->_size.y / 2.0f - point->_radius){
		return false;
	}

	float h_radius(point->_radius);
	if(point_pos.y > pole->_size.y / 2.0f || point_pos.y < -pole->_size.y / 2.0f){
		float height(point_pos.y - pole->_size.y / 2.0f);
		if(height < 0.0f){height = -height;}

		h_radius = sqrtf(point->_radius * point->_radius - height * height);
	}

	float length(h_radius + pole->_radius);
	if(point_pos.x * point_pos.x + point_pos.z * point_pos.z < length * length){
		//あたっちょる
		ret = true;
	}

	return ret;

}



void Object::GetWorldMatrix(D3DXMATRIX* out){
	if(out == nullptr){return;}

	D3DXMATRIX world_mtx, rot_mtx, translate_mtx;

	D3DXMatrixIdentity(&world_mtx);					//ワールド行列をとりあえずEにする

	D3DXMatrixRotationYawPitchRoll(&rot_mtx, _rotation.y, _rotation.x, _rotation.z);	//rotation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &rot_mtx);

	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, _position.z);	//translation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &translate_mtx);

	*out = world_mtx;
}

