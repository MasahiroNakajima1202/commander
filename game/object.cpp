//*****************************************************************************
//  scene���W���[��
//  �T���v���V�[��
//  author: �������_
//  update: 2014/04/15
//*****************************************************************************

#include "renderer.h"
#include "object.h"

Object *Object::_top[DRAW_LAYER_MAX] = {};

//*****************************************************************************
//�y�������z
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
//�y�X�V�z
//*****************************************************************************
void Object::Update(void){
	_pre_position = _position;
	_position += _velocity;

	_pre_rotation = _rotation;
}

//*****************************************************************************
//�y���X�g�֎Q���z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Object::PushBackToList(int layer_no){
	Object *cur = nullptr;
	if(_top[layer_no] == nullptr){//�ŏ��̂ЂƂ�
		_top[layer_no] = this;
		return;
	}

	//��l�ڈȍ~
	cur = _top[layer_no];

	//cur�𖖔��܂œ�����
	while(cur->_next != nullptr){
		cur = cur->_next;
	}

	//cur�ɗv�f�ǉ�
	cur->_next = this;
}

//*****************************************************************************
//�y���X�g����폜�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
void Object::RemoveFromList(int layer_no){
	Object *cur = nullptr;
	Object *pre = nullptr;
	
	cur = _top[layer_no];
	//�ڂ���������܂Ői�߂� �O�̂���nullptr check�� ���肦�Ȃ�����
	while(cur != this && cur != nullptr){
		pre = cur;
		cur = cur->_next;
	}

	if(cur == nullptr){//�ڂ������Ȃ�����
		return;	//��ش��
	}

	if(cur == _top[layer_no]){
		_top[layer_no] = cur->_next;
	}
	else{
		pre->_next = cur->_next;
	}
}


//*****************************************************************************
//�y�S�X�V�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
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
//�y�`��z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
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
//�y���ˁI�n�C�G�i�ǂ��߁I�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
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
//�y�S�X�V�z
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
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
//�y�����A���܂��H�z
//  �Ώۂ̃I�u�W�F�N�g�����݂��邩�ǂ���
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
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

	//���Ȃ�������c�c
	return false;
}

//*****************************************************************************
//�y�����蔻��(���Ƌ�)�z
//  ��̃I�u�W�F�N�g�̓����蔻��𒲂ׂ܂� as ball and ball
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
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
//�y�����蔻��(�_�Ɣ�)�z
//  ��̃I�u�W�F�N�g�̓����蔻��𒲂ׂ܂� as point and box
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
bool Object::HitCheckPointBox(Object* point, Object* box){
	D3DXVECTOR3 box_position(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 box_rotation(0.0f, 0.0f, 0.0f);
	D3DXMATRIX rot_mtx, trs_mtx, inv_mtx;
	bool ret = false;

	//box��posrot�𗼕��ɋt�Z
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
//�y�����蔻��(�_�Ɖ~��)�z
//  ��̃I�u�W�F�N�g�̓����蔻��𒲂ׂ܂� as point and pole
//  �Ԃ�l: �Ȃ�
//  ����: �Ȃ�
//*****************************************************************************
bool Object::HitCheckPointPole(Object* point, Object* pole){
	D3DXVECTOR3 pole_position(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 pole_rotation(0.0f, 0.0f, 0.0f);
	D3DXMATRIX rot_mtx, trs_mtx, inv_mtx;
	bool ret = false;

	//box��posrot�𗼕��ɋt�Z
	D3DXMatrixIdentity(&inv_mtx);
	D3DXMatrixTranslation(&trs_mtx, pole->_position.x, pole->_position.y, pole->_position.z);
	D3DXMatrixRotationYawPitchRoll(&rot_mtx, pole->_rotation.y, pole->_rotation.x, pole->_rotation.z);
	D3DXMatrixMultiply(&inv_mtx, &inv_mtx, &rot_mtx);
	D3DXMatrixMultiply(&inv_mtx, &inv_mtx, &trs_mtx);
	D3DXMatrixInverse(&inv_mtx, nullptr, &inv_mtx);

	D3DXVECTOR3 point_pos = point->_position;
	D3DXVec3TransformCoord(&point_pos, &point_pos, &inv_mtx);

	//��������
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
		//�����������
		ret = true;
	}

	return ret;

}



void Object::GetWorldMatrix(D3DXMATRIX* out){
	if(out == nullptr){return;}

	D3DXMATRIX world_mtx, rot_mtx, translate_mtx;

	D3DXMatrixIdentity(&world_mtx);					//���[���h�s����Ƃ肠����E�ɂ���

	D3DXMatrixRotationYawPitchRoll(&rot_mtx, _rotation.y, _rotation.x, _rotation.z);	//rotation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &rot_mtx);

	D3DXMatrixTranslation(&translate_mtx, _position.x, _position.y, _position.z);	//translation
	D3DXMatrixMultiply(&world_mtx, &world_mtx, &translate_mtx);

	*out = world_mtx;
}

