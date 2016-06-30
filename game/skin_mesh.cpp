//*****************************************************************************
//  �X�L�����b�V���N���X
//  �������_
//  UPDATE:2014/03/27
//*****************************************************************************

#include "skin_mesh.h"
#include "input.h"
#include <stdio.h>
#ifdef _CONVERTER_
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;
#endif
//#include "debug.h"

//*****************************************************************************
//�y�R���X�g���N�^�z
//  ����: �Ȃ�
//*****************************************************************************
SkinMesh::SkinMesh(Renderer *master_renderer, int layer_no) : Object(master_renderer, layer_no){
	_mesh_count = 0;
	_mesh = NULL;
	_mesh_cursor = 0;

	_bone_count = 0;
	_bone = NULL;
	_root = NULL;
	_cur_time = 0.0f;					//���m�p
	_bone_cursor = 0;				//�{�[���ǂݍ��ݐ���w������

	_reverse = false;

	_animation_count = 0;
	_animation = NULL;

	_current_animation = -1;				//���݂̃A�j���[�V����
	_previous_animation = -1;
	_animation_blending = false;
	_animation_blend_weight = 0.0f;
	_play_flag = false;
	_pause = false;
	_transparent = false;
}

//*****************************************************************************
//�y�f�X�g���N�^�z
//  ���_���̉�����s���B
//*****************************************************************************
SkinMesh::~SkinMesh(){
	Release();
}

//*****************************************************************************
//�y����z
//  ���_�f�[�^��{�[���s������ׂĔj��
//  �Ԃ�l  : �Ȃ�
//  ����    : �Ȃ�
//*****************************************************************************
void SkinMesh::Release(void){
	int i = 0;

	if(_mesh != NULL){
		for(i=0; i<_mesh_count; i++){
			if(_mesh[i].vertex != NULL){
				_mesh[i].vertex->Release();
				_mesh[i].vertex = NULL;
			}
			if(_mesh[i].index != NULL){
				_mesh[i].index->Release();
				_mesh[i].index = NULL;
			}
		}

		delete [] _mesh;
		_mesh = NULL;
	}


	//bone��j��
	if(_bone != NULL){
		for(i=0; i<_bone_count; i++){
			if(_bone[i].key != NULL){
				delete [] _bone[i].key;
				_bone[i].key = NULL;
			}
		}
		delete [] _bone;
		_bone = NULL;
	}


	if(_animation != NULL){
		delete [] _animation;
		_animation = NULL;
	}

	if(_decl != NULL){
		_decl->Release();
		_decl = NULL;
	}

}

//*****************************************************************************
//�y�X�V�z
//  �A�j���[�V�����ƁA�e�{�[���s��̍X�V
//  �Ԃ�l  : �Ȃ�
//  ��1���� : �Ȃ�
//*****************************************************************************
void SkinMesh::Update(void){
	D3DXMATRIX element, rot_mtx;
	float anim_length = 0.0f;

	D3DXMatrixIdentity(&element);
	element._11 = _size.x;
	element._22 = _size.y;
	element._33 = _size.z;
	D3DXMatrixRotationYawPitchRoll(&rot_mtx, _rotation.y + D3DX_PI, _rotation.x, _rotation.z);
	D3DXMatrixMultiply(&element, &element, &rot_mtx);
	element._41 = _position.x;
	element._42 = _position.y;
	element._43 = _position.z;

	//position.x -= 0.1f;


	//animation�X�V
	if(_play_flag && !_pause){
		if(0 <= _current_animation && _current_animation < _animation_count){
			ANIMATION *_cur_anim(&_animation[_current_animation]);
			_cur_anim->time += _cur_anim->speed;
			
			float length(_cur_anim->end - _cur_anim->begin);
			if(length > 0){
				if(_cur_anim->time > length){
					if(_cur_anim->loop){
						_cur_anim->time -= length;
					}
					else{
						_cur_anim->time = length;
					}
				}
			}
			else{
				_cur_anim->time = _cur_anim->begin;
			}
		}
	}

	//�K�w�\���̍X�V
	UpdateBoneMatrix(&_bone[0], &element);

	//�A�j���[�V�����ڍs���Ԃ̍X�V
	if(_animation_blending){
		_animation_switching++;
		if(_animation_switching >= ANIMATION_SWITCHING_TIME){
			_animation_switching = 0;
			_animation_blending = false;
		}
	}

}


//*****************************************************************************
//�y�`��z
//  �����̈ʒu�𒆐S�Ƃ��āA��`��`��
//  �Ԃ�l  : �Ȃ�
//  ��1���� : �`�撆�S�ʒu��x���W
//  ��2���� : �`�撆�S�ʒu��y���W
//*****************************************************************************
void SkinMesh::Draw(void){
	//null check
	if(_mesh == NULL){
		return;
	}
	
	D3DXMATRIX scl_mtx, rot_mtx, translate_mtx;
	LPDIRECT3DDEVICE9 device = NULL;		//�f�o�C�X�擾�p
	int i = 0;//loop index

	device = _renderer->GetDevice();

	//���_�`��
	device->SetVertexDeclaration(_decl);

	DWORD def_cull = 0;
	device->GetRenderState(D3DRS_CULLMODE, &def_cull);

	if(_reverse){
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				//D3DCULL_CW
	}
	else{
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);			//D3DCULL_CCW
	}

	//�s��̎w��
	D3DXMATRIX matrix_table[Renderer::BONE_TABLE_MAX] = {};

	for(i=0; i<_bone_count; i++){
		matrix_table[i] = _bone[i].world_mtx;
	}
	_renderer->SetWorldArray(matrix_table, 52);

	for(i=0; i<_mesh_count; i++){
		//null check
		if(_mesh[i].index == NULL || _mesh[i].vertex == NULL){
			continue;
		}

		_renderer->SetTextureToShader(_mesh[i].texture);

		//_renderer->SetMaterialAmbient(debug_mat.Diffuse);
		D3DXVECTOR4 diffuse(_mesh[i].material.Diffuse.r,
							_mesh[i].material.Diffuse.g,
							_mesh[i].material.Diffuse.b,
							_mesh[i].material.Diffuse.a);
		if(_transparent){
			diffuse.w *= 0.5f;
		}
		_renderer->SetMaterialDiffuse(diffuse);

		_renderer->SetCurrentShader();

		device->SetStreamSource(0, _mesh[i].vertex, 0, sizeof(VERTEX_BLEND_3D));
		device->SetIndices(_mesh[i].index);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, _mesh[i].vertex_count, 0, _mesh[i].index_count / 3);					//�`��

	}

	//�J�����O����
	device->SetRenderState(D3DRS_CULLMODE, def_cull);
}

//*****************************************************************************
//�y�A�j���[�V�����̒ǉ��z
//  �V�����A�j���[�V������ǉ�����
//  �Ԃ�l  : �Ȃ�
//  ��1���� : �J�n�t���[��
//  ��2���� : �I���t���[��
//  ��3���� : �Đ����x
//*****************************************************************************
void SkinMesh::MakeNewAnimation(float begin, float end, float speed){
	MakeNewAnimation(begin, end, false, "DefaultAnimation", speed);
}
void SkinMesh::MakeNewAnimation(float begin, float end, bool loop, char *name, float speed){
	ANIMATION *new_anim = NULL;
	int i = 0;							//loop index

	//�J�E���^����
	_animation_count++;

	//���T�C�Y
	new_anim = new ANIMATION[_animation_count];

	//�R�s�[
	for(i=0; i<_animation_count-1; i++){
		new_anim[i] = _animation[i];
	}

	//�V�K�ɐ������ꂽanimation�̏�����
	new_anim[_animation_count - 1].begin = begin;
	new_anim[_animation_count - 1].end = end;
	new_anim[_animation_count - 1].speed = speed;
	new_anim[_animation_count - 1].loop = loop;
	strcpy(new_anim[_animation_count - 1].name, name);

	//���z���ׂ�
	delete [] _animation;

	//�A�h���X�R�s�[
	_animation = new_anim;
}

void SkinMesh::GetAnimationName(int index, char *str){
	//out of range
	if(index < 0 || _animation_count <= index){return;}
	if(_animation == NULL){return;}

	strcpy(str, _animation[index].name);
}
void SkinMesh::SetAnimationName(int index, char *str){
	//out of range
	if(index < 0 || _animation_count <= index){return;}
	if(_animation == NULL){return;}

	strcpy(_animation[index].name, str);
}

//*****************************************************************************
//�y���f���f�[�^�̏o�́z
//*****************************************************************************
void SkinMesh::ExportModelFile(char *filename){
	int i = 0, j = 0;					//loop index
	FILE *fp = NULL;
	VERTEX_BLEND_3D *work_vtx = NULL;
	WORD *work_index = NULL;

	fp = fopen(filename, "wb");

	if(fp == NULL){return;}

	//���b�V����
	fwrite(&_mesh_count, sizeof(int), 1, fp);

	//���b�V���z��
	for(i=0; i<_mesh_count; i++){
		//���_��
		fwrite(&_mesh[i].vertex_count, sizeof(int), 1, fp);

		//���_
		_mesh[i].vertex->Lock(0, 0, (void**)&work_vtx, 0);
		fwrite(work_vtx, sizeof(VERTEX_BLEND_3D), _mesh[i].vertex_count, fp);		
		_mesh[i].vertex->Unlock();

		//index��
		fwrite(&_mesh[i].index_count, sizeof(int), 1, fp);

		//index
		_mesh[i].index->Lock(0, 0, (void**)&work_index, 0);
		fwrite(work_index, sizeof(WORD), _mesh[i].index_count, fp);		
		_mesh[i].index->Unlock();

		//�}�e���A��
		fwrite(&_mesh[i].material, sizeof(D3DMATERIAL9), 1, fp);

		//�t�@�C����
		fwrite(_mesh[i].texture_filename, sizeof(char), 128, fp);
	}

	//�{�[����
	fwrite(&_bone_count, sizeof(int), 1, fp);

	//�{�[���z��
	for(i=0; i<_bone_count; i++){
		//�{�[���\���̂𐶂� ���X�g�|�C���^��pool�̒��̃L�[�t���[���z��~3��NULL��
		BONE bone_buff = _bone[i];
		bone_buff.child = NULL; bone_buff.sibling = NULL;
		bone_buff.key = NULL;
		fwrite(&bone_buff, sizeof(BONE), 1, fp);

		int test = sizeof(BONE);

		//�q��id(NULL�Ȃ��-1)
		int child_id = -1;
		if(_bone[i].child != NULL){child_id = _bone[i].child->id;}
		fwrite(&child_id, sizeof(int), 1, fp);

		//�Z���id
		int sibling_id = -1;
		if(_bone[i].sibling != NULL){sibling_id = _bone[i].sibling->id;}
		fwrite(&sibling_id, sizeof(int), 1, fp);

		//key�z��
		fwrite(_bone[i].key, sizeof(KEY_FRAME), _bone[i].key_count, fp);
	}

	//animation�̌�
	fwrite(&_animation_count, sizeof(int), 1, fp);

	//animation�z�� current_time��0�Ő���Ă���
	for(i=0; i<_animation_count; i++){
		_animation[i].time = 0.0f;
	}
	if(_animation != NULL){
		fwrite(_animation, sizeof(ANIMATION), _animation_count, fp);
	}

	fclose(fp);
}
void SkinMesh::LoadModelFile(char *filename){
	int i = 0, j = 0;					//loop index
	FILE *fp = NULL;
	VERTEX_BLEND_3D *work_vtx = NULL;
	WORD *work_index = NULL;
	int file_size;
	unsigned char *loading_buff;
	int cursor = 0;
	LPDIRECT3DDEVICE9 device = NULL;		//�f�o�C�X�擾�p

	device = _renderer->GetDevice();

	fp = fopen(filename, "rb");

	if(fp == NULL){return;}

	//��������S���ǂݍ��ށI
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	//�v�[���̓��I�m��
	loading_buff = new unsigned char[file_size];
	fread(loading_buff, 1, file_size, fp);

	fclose(fp);

	//���b�V����
	memcpy(&_mesh_count, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
	//fwrite(&mesh_count, sizeof(int), 1, fp);

	//���b�V���z��̓��I�m��
	_mesh = new MESH[_mesh_count];
	memset(_mesh, 0, sizeof(MESH)*_mesh_count);

	

	//���_�v�f�̒�`
	//D3DXVECTOR3 vtx;		// ���_���W
	//float weight[3];		// �d��
	//DWORD mtx_index;		// ���_�C���f�b�N�X(���ʃo�C�g�����)
	//D3DXVECTOR3 nor;		// �@���x�N�g��
	//D3DCOLOR diffuse;		// ���ˌ�
	//D3DXVECTOR2 tex;		// �e�N�X�`�����W

	D3DVERTEXELEMENT9 v_ele[] = {
		{0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDWEIGHT, 0},
		{0, 24, D3DDECLTYPE_UBYTE4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BLENDINDICES, 0},
		{0, 28, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 40, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR, 0},
		{0, 44, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	//declaration������
	if(FAILED(device->CreateVertexDeclaration(v_ele, &_decl))){
		return;
	}

	//���b�V���z��
	for(i=0; i<_mesh_count; i++){
		//���_��
		memcpy(&_mesh[i].vertex_count, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
		//fwrite(&mesh[i].vertex_count, sizeof(int), 1, fp);

		//���_
		if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_BLEND_3D) * _mesh[i].vertex_count,
											 D3DUSAGE_WRITEONLY,
											 0,
											 D3DPOOL_MANAGED,
											 &_mesh[i].vertex,
											 NULL))){
			//���_�m�ۂɎ��s
			_mesh[i].vertex = NULL;
		}
		_mesh[i].vertex->Lock(0, 0, (void**)&work_vtx, 0);
		memcpy(work_vtx, loading_buff + cursor, sizeof(VERTEX_BLEND_3D) * _mesh[i].vertex_count);
		cursor += sizeof(VERTEX_BLEND_3D) * _mesh[i].vertex_count;
		//fwrite(work_vtx, sizeof(VERTEX_BLEND_3D), mesh[i].vertex_count, fp);		
		_mesh[i].vertex->Unlock();

		//index��
		memcpy(&_mesh[i].index_count, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
		//fwrite(&mesh[i].index_count, sizeof(int), 1, fp);

		//index
		if(FAILED(device->CreateIndexBuffer(sizeof(WORD) * _mesh[i].index_count,
											D3DUSAGE_WRITEONLY,
											D3DFMT_INDEX16,
											D3DPOOL_MANAGED,
											&_mesh[i].index,
											NULL))){
			_mesh[i].index = NULL;
		}
		_mesh[i].index->Lock(0, 0, (void**)&work_index, 0);
		memcpy(work_index, loading_buff + cursor, sizeof(WORD) * _mesh[i].index_count);
		cursor += sizeof(WORD) * _mesh[i].index_count;
		//fwrite(work_index, sizeof(WORD), mesh[i].index_count, fp);		
		_mesh[i].index->Unlock();

		//�}�e���A��
		memcpy(&_mesh[i].material, loading_buff + cursor, sizeof(D3DMATERIAL9)); cursor += sizeof(D3DMATERIAL9);
		//fwrite(&mesh[i].material, sizeof(D3DMATERIAL9), 1, fp);

		//�t�@�C����
		memcpy(_mesh[i].texture_filename, loading_buff + cursor, sizeof(char) * 128); cursor += sizeof(char) * 128;
		//fwrite(mesh[i].texture_filename, sizeof(char), 128, fp);

		//�e�N�X�`�����[�h
		char filename[256] = "";
		sprintf(filename, "data/TEXTURE/%s", _mesh[i].texture_filename);
		_mesh[i].texture = _renderer->LoadTexture(filename);
	}

	//�{�[����
	memcpy(&_bone_count, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
	//fwrite(&bone_count, sizeof(int), 1, fp);

	//�{�[���z��
	_bone = new BONE[_bone_count];

	for(i=0; i<_bone_count; i++){
		//�{�[���\���̂𐶂� ���X�g�|�C���^��pool�̒��̃L�[�t���[���z��~3��NULL��
		memcpy(&_bone[i], loading_buff + cursor, sizeof(BONE)); cursor += sizeof(BONE);
		//fwrite(&bone_buff, sizeof(BONE), 1, fp);

		//�q��id(NULL�Ȃ��-1)
		int child_id = -1;
		memcpy(&child_id, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
		if(child_id == -1){_bone[i].child = NULL;}
		else{_bone[i].child = &_bone[child_id];}
		//fwrite(&child_id, sizeof(int), 1, fp);

		//�Z���id
		int sibling_id = -1;
		memcpy(&sibling_id, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
		if(sibling_id == -1){_bone[i].sibling = NULL;}
		else{_bone[i].sibling = &_bone[sibling_id];}
		//fwrite(&sibling_id, sizeof(int), 1, fp);

		//�A�j���[�V�����v�[��
		int key_num = 0;
		//key�z��
		key_num = _bone[i].key_count;
		_bone[i].key = new KEY_FRAME[key_num];
		memcpy(_bone[i].key, loading_buff + cursor, sizeof(KEY_FRAME) * key_num);
		cursor += sizeof(KEY_FRAME) * key_num;
		//fwrite(bone_table[i]->pool.scl_key, sizeof(SCALING_KEY), bone_table[i]->pool.scl_key_max, fp);
		
	}

	//animation�̌�
	memcpy(&_animation_count, loading_buff + cursor, sizeof(int)); cursor += sizeof(int);
	//fwrite(&animation_max, sizeof(int), 1, fp);

	//animation�z�� current_time��0�Ő���Ă���
	if(_animation_count > 0){
		_animation = new ANIMATION[_animation_count];
		memcpy(_animation, loading_buff + cursor, sizeof(ANIMATION) * _animation_count);
		cursor += sizeof(ANIMATION) * _animation_count;
	}
	//if(animation != NULL){
	//	fwrite(animation, sizeof(ANIMATION), 1, fp);
	//}

	delete [] loading_buff;

	//root�o�^
	_root = &_bone[0];

#ifdef _CONVERTER_
	hidden = new bool[mesh_count];
	selected = new bool[mesh_count];
	for(i=0; i<mesh_count; i++){
		hidden[i] = false;
		selected[i] = false;
	}
#endif
}

//private func
//�m�[�h����̃A�j���[�V�����̓ǂݍ���

//�����X�V
void SkinMesh::UpdateBoneMatrix(BONE *subject, D3DXMATRIX *parent){
	KEY_FRAME *prev(NULL), *next(NULL);
	int i = 0;								//loop index
	float t(0.0f);							//��ԃp�����[�^
	float length(0.0f);						//�t���[���Ԃ̒���
	D3DXMATRIX trs_mtx, scl_mtx, rot_mtx;	//��Ɨp
	float time(_cur_time);

	int key_count(subject->key_count);

	//�A�j���[�V�������łȂ��ꍇ�͏����p���œ���
	if(!_play_flag){
		//translation
		D3DXVECTOR3 translation(InterpolateTranslation(subject, 0.0f));

		//rotation
		D3DXQUATERNION rotation(InterpolateRotation(subject, 0.0f));

		//scaling
		D3DXVECTOR3 scaling(InterpolateScaling(subject, 0.0f));

		//transform����
		D3DXMatrixTranslation(&trs_mtx, translation.x, translation.y, translation.z);
		D3DXMatrixRotationQuaternion(&rot_mtx, &rotation);
		D3DXMatrixScaling(&scl_mtx, scaling.x, scaling.y, scaling.z);

	}
	//�؂�ւ���
	else if(_animation_blending){
		//���Ԃ̌v�Z
		float cur_t(_animation[_current_animation].begin + _animation[_current_animation].time);
		float pre_t(_animation[_previous_animation].begin + _animation[_previous_animation].time);

		float blend_weight((float)_animation_switching / (float)ANIMATION_SWITCHING_TIME);

		//translation
		D3DXVECTOR3 translation(InterpolateBlendTranslation(subject, pre_t, cur_t, blend_weight));

		//rotation
		D3DXQUATERNION rotation(InterpolateBlendRotation(subject, pre_t, cur_t, blend_weight));

		//scaling
		D3DXVECTOR3 scaling(InterpolateBlendScaling(subject, pre_t, cur_t, blend_weight));

		//transform����
		D3DXMatrixTranslation(&trs_mtx, translation.x, translation.y, translation.z);
		D3DXMatrixRotationQuaternion(&rot_mtx, &rotation);
		D3DXMatrixScaling(&scl_mtx, scaling.x, scaling.y, scaling.z);
	}
	//�P��A�j���[�V����
	else{
		//���Ԃ̌v�Z
		float t(_animation[_current_animation].begin + _animation[_current_animation].time);

		//translation
		D3DXVECTOR3 translation(InterpolateTranslation(subject, t));

		//rotation
		D3DXQUATERNION rotation(InterpolateRotation(subject, t));

		//scaling
		D3DXVECTOR3 scaling(InterpolateScaling(subject, t));

		//transform����
		D3DXMatrixTranslation(&trs_mtx, translation.x, translation.y, translation.z);
		D3DXMatrixRotationQuaternion(&rot_mtx, &rotation);
		D3DXMatrixScaling(&scl_mtx, scaling.x, scaling.y, scaling.z);
	}

	D3DXMatrixIdentity(&subject->bone_mtx);
	D3DXMatrixMultiply(&subject->bone_mtx, &subject->bone_mtx, &scl_mtx);
	D3DXMatrixMultiply(&subject->bone_mtx, &subject->bone_mtx, &rot_mtx);
	D3DXMatrixMultiply(&subject->bone_mtx, &subject->bone_mtx, &trs_mtx);

	//���ɓn���s��̌v�Z
	D3DXMatrixMultiply(&subject->transform_mtx, &subject->bone_mtx, parent);

	//���[���h���X�V world = offset * �����̍s�� * �e�̍s��;
	D3DXMatrixMultiply(&subject->world_mtx, &subject->offset_mtx, &subject->transform_mtx);

	//D3DXVECTOR3 point(0.0f, 0.0f, 0.0f);
	//D3DXVec3TransformCoord(&point, &point, &subject->transform_mtx);//�����bone�̈ʒu���킩��I��I
	

	if(subject->child != NULL){//�q���̍X�V
		UpdateBoneMatrix(subject->child, &subject->transform_mtx);
	}

	if(subject->sibling != NULL){//�Z��̍X�V
		UpdateBoneMatrix(subject->sibling, parent);
	}
}


SkinMesh::BONE* SkinMesh::SearchBoneByName(char *name){
	if(_bone == NULL){return NULL;}
	if(name == NULL){return NULL;}

	int i(0);
	for(i=0; i<_bone_count; i++){
		if(strcmp(_bone[i].name, name) == 0){
			return _bone + i;
		}
	}

	return NULL;
}

D3DXMATRIX* SkinMesh::GetBoneWorldByName(char *name){
	BONE *work(SearchBoneByName(name));
	if(work == NULL){return NULL;}

	return &(work->world_mtx);
}
D3DXMATRIX* SkinMesh::GetBoneOffsetByName(char *name){
	BONE *work(SearchBoneByName(name));
	if(work == NULL){return NULL;}

	return &(work->offset_mtx);
}

//�L�[�t���[���Ԃ̕��
D3DXVECTOR3 SkinMesh::InterpolateTranslation(BONE *subject, float time){
	if(subject == NULL){return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}
	if(subject->key == NULL){return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}


	//���Ԃ̓��ł�
	float cur_time(time);
	cur_time = max(cur_time, 0.0f);
	cur_time = min(cur_time, subject->key[subject->key_count - 1].time);

	//����̃L�[�t���[���擾
	int next(0);
	for(next=1; next<subject->key_count; next++){
		if(cur_time <=subject->key[next].time){
			break;
		}
	}

	//���O�̃L�[�t���[���擾
	int prev(next - 1);

	//�O���translation�擾
	D3DXVECTOR3 prev_trs(subject->key[prev].translation);
	D3DXVECTOR3 next_trs(subject->key[next].translation);

	//parameter�擾
	float t(0.0f);
	float length(subject->key[next].time - subject->key[prev].time);
	if(length != 0.0f){
		t = (cur_time - subject->key[prev].time) / length;
	}

	D3DXVECTOR3 ret(prev_trs * (1.0f - t) + next_trs * t);

	return ret;
}
D3DXQUATERNION SkinMesh::InterpolateRotation(BONE *subject, float time){
	if(subject == NULL){return D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);}
	if(subject->key == NULL){return D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);}


	//���Ԃ̓��ł�
	float cur_time(time);
	cur_time = max(cur_time, 0.0f);
	cur_time = min(cur_time, subject->key[subject->key_count - 1].time);

	//����̃L�[�t���[���擾
	int next(0);
	for(next=1; next<subject->key_count; next++){
		if(cur_time <=subject->key[next].time){
			break;
		}
	}

	//���O�̃L�[�t���[���擾
	int prev(next - 1);

	//�O���translation�擾
	D3DXQUATERNION prev_rot(subject->key[prev].rotation);
	D3DXQUATERNION next_rot(subject->key[next].rotation);

	//parameter�擾
	float t(0.0f);
	float length(subject->key[next].time - subject->key[prev].time);
	if(length != 0.0f){
		t = (cur_time - subject->key[prev].time) / length;
	}

	D3DXQUATERNION ret(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXQuaternionSlerp(&ret, &prev_rot, &next_rot, t);

	return ret;
}
D3DXVECTOR3 SkinMesh::InterpolateScaling(BONE *subject, float time){
	if(subject == NULL){return D3DXVECTOR3(1.0f, 1.0f, 1.0f);}
	if(subject->key == NULL){return D3DXVECTOR3(1.0f, 1.0f, 1.0f);}


	//���Ԃ̓��ł�
	float cur_time(time);
	cur_time = max(cur_time, 0.0f);
	cur_time = min(cur_time, subject->key[subject->key_count - 1].time);

	//����̃L�[�t���[���擾
	int next(0);
	for(next=1; next<subject->key_count; next++){
		if(cur_time <=subject->key[next].time){
			break;
		}
	}

	//���O�̃L�[�t���[���擾
	int prev(next - 1);

	//�O���translation�擾
	D3DXVECTOR3 prev_scl(subject->key[prev].scaling);
	D3DXVECTOR3 next_scl(subject->key[next].scaling);

	//parameter�擾
	float t(0.0f);
	float length(subject->key[next].time - subject->key[prev].time);
	if(length != 0.0f){
		t = (cur_time - subject->key[prev].time) / length;
	}

	D3DXVECTOR3 ret(prev_scl * (1.0f - t) + next_scl * t);

	return ret;
}

D3DXVECTOR3 SkinMesh::InterpolateBlendTranslation(BONE *subject, float prev_time, float next_time, float t){
	if(subject == NULL){return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}
	if(subject->key == NULL){return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}

	//�؂�ւ��O��translation
	D3DXVECTOR3 prev_trs(InterpolateTranslation(subject, prev_time));

	//�؂�ւ����translation
	D3DXVECTOR3 next_trs(InterpolateTranslation(subject, next_time));

	//blend
	D3DXVECTOR3 blend((1.0f - t) * prev_trs + t * next_trs);

	return blend;
}
D3DXQUATERNION SkinMesh::InterpolateBlendRotation(BONE *subject, float prev_time, float next_time, float t){
	if(subject == NULL){return D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);}
	if(subject->key == NULL){return D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);}

	//�؂�ւ��O��rotation
	D3DXQUATERNION prev_rot(InterpolateRotation(subject, prev_time));

	//�؂�ւ����rotation
	D3DXQUATERNION next_rot(InterpolateRotation(subject, next_time));

	//blend
	D3DXQUATERNION blend(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXQuaternionSlerp(&blend, &prev_rot, &next_rot, t);

	return blend;
}
D3DXVECTOR3 SkinMesh::InterpolateBlendScaling(BONE *subject, float prev_time, float next_time, float t){
	if(subject == NULL){return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}
	if(subject->key == NULL){return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}

	//�؂�ւ��O��scaling
	D3DXVECTOR3 prev_scl(InterpolateScaling(subject, prev_time));

	//�؂�ւ����scaling
	D3DXVECTOR3 next_scl(InterpolateScaling(subject, next_time));

	//blend
	D3DXVECTOR3 blend((1.0f - t) * prev_scl + t * next_scl);

	return blend;
}

