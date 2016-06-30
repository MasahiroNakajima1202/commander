//*****************************************************************************
//  �X�L�����b�V���N���X
//  �������_
//  UPDATE:2014/03/27
//*****************************************************************************
#ifndef _MY_SKIN_MESH_H_
#define _MY_SKIN_MESH_H_

#include "main.h"
#include "renderer.h"
#include "object.h"


//#define _CONVERTER_

//*****************************************************************************
// class def
//*****************************************************************************
class SkinMesh : public Object{
public:

	//*****************************************************************************
	//�y�R���X�g���N�^�z
	//  ���_�m�ۂ����Ȃ�
	//  ����: �Ȃ�
	//*****************************************************************************
	SkinMesh(Renderer *master_renderer, int layer_no = DRAW_LAYER_SKIN_MESH);

	//*****************************************************************************
	//�y�f�X�g���N�^�z
	//  ���_���̉�����s���B
	//*****************************************************************************
	virtual ~SkinMesh();

	//*****************************************************************************
	//�y�ǂݍ��݁z
	//  �Ԃ�l  : �ǂݍ��݂̐���
	//  ��1���� : �e�N�X�`���̃t�@�C���p�X
	//*****************************************************************************
#ifdef _CONVERTER_
	bool Load(char *filename);
#endif

	//*****************************************************************************
	//�y����z
	//  ���_�f�[�^��{�[���s������ׂĔj��
	//  �Ԃ�l  : �Ȃ�
	//  ����    : �Ȃ�
	//*****************************************************************************
	virtual void Release(void);

	//*****************************************************************************
	//�y�X�V�z
	//  �A�j���[�V�����ƁA�e�{�[���s��̍X�V
	//  �Ԃ�l  : �Ȃ�
	//  ��1���� : �Ȃ�
	//*****************************************************************************
	virtual void Update(void);

	//*****************************************************************************
	//�y�`��z
	//  �����̈ʒu�𒆐S�Ƃ��āA��`��`��
	//  �Ԃ�l  : �Ȃ�
	//  ��1���� : �`�撆�S�ʒu��x���W
	//  ��2���� : �`�撆�S�ʒu��y���W
	//  ��3���� : �`�撆�S�ʒu��z���W
	//*****************************************************************************
	//virtual void Draw(float x, float y, float z);
	virtual void Draw(void);

	//*****************************************************************************
	//�y�A�j���[�V�����̒ǉ��z
	//  �V�����A�j���[�V������ǉ�����
	//  �Ԃ�l  : �Ȃ�
	//  ��1���� : �J�n�t���[��
	//  ��2���� : �I���t���[��
	//  ��3���� : �Đ����x
	//*****************************************************************************
	void MakeNewAnimation(float begin, float end, float speed = 1.0f);
	void MakeNewAnimation(float begin, float end, bool loop, char *name, float speed = 1.0f);

	void ExportModelFile(char *filename = "model.ndk");
	void LoadModelFile(char *filename);

	//*****************************************************************************
	//�y�A�j���[�V��������z
	//  �R�����g�ȗ�
	//*****************************************************************************
	void SetCurrentAnimation(int anim_id, bool blend = true){
		if(0 <= anim_id && anim_id < _animation_count){
			_previous_animation = _current_animation;
			_current_animation = anim_id;
			_animation_switching = 0;
			_animation_blending = true;
		}
	}
	void PlayCurrentAnimation(void){_play_flag = true;}
	void StopAnimation(void){_play_flag = false;}
	void PlayAnimation(int anim_id, bool blend = true){
		SetCurrentAnimation(anim_id, blend);
		ResetCurrentAnimation();
		PlayCurrentAnimation();
	}
	void ResetAnimation(int anim_id){
		if(0 <= anim_id && anim_id < _animation_count){
			_animation[anim_id].time = 0.0f;
		}
	}
	void ResetCurrentAnimation(void){
		ResetAnimation(_current_animation);
	}
	void ResetAllAnimation(void){
		for(int i = 0; i<_animation_count; i++){
			ResetAnimation(i);
		}
	}
	void GetAnimationName(int index, char *str);
	void SetAnimationName(int index, char *str);
	void PauseAnimation(void){_pause = true;}
	void RestartAnimation(void){_pause = false;}

	void SetReverse(bool value){_reverse = value;}
	void SetTransparent(bool value){_transparent = value;}

	D3DXMATRIX* GetBoneWorldByName(char *name);
	D3DXMATRIX* GetBoneOffsetByName(char *name);

protected:

private:
	struct MESH{
		LPDIRECT3DVERTEXBUFFER9 vertex;
		LPDIRECT3DINDEXBUFFER9 index;
		int vertex_count;
		int index_count;
		D3DMATERIAL9 material;
		char texture_filename[128];			//�e�N�X�`����
		int texture;						//�e�N�X�`��

		char uvset_name[128];
	};

	struct KEY_FRAME{
		float time;
		D3DXVECTOR3 translation;
		D3DXQUATERNION rotation;
		D3DXVECTOR3 scaling;
	};

	struct BONE{
		int id;
		D3DXMATRIX bone_mtx;				//�{�[���s��(�����̓��[�J��)
		D3DXMATRIX offset_mtx;				//�{�[���I�t�Z�b�g�s��(�����̓O���[�o��)
		D3DXMATRIX transform_mtx;			//�p��(�{�[���I�t�Z�b�g�Ɠ��i�A�O���[�o��)
		D3DXMATRIX world_mtx;				//���[���h(�ŏI�I�Ȃ�Ȃ�ŁA�O���[�o��)

		BONE *child;						//�q
		BONE *sibling;						//�Z��

		char name[128];						//�{�[���̖��O

		int key_count;
		KEY_FRAME *key;

		BONE(){
			child=NULL;
			sibling=NULL;
			memset(name, 0, 128);
			id=-1;
		}
	};

	struct ANIMATION{
		float begin;				//�J�n����
		float end;					//�I������
		float speed;				//�Đ����x 1.0f���f�t�H���g
		float time;					//���݂̈ʒu
		bool loop;					//loop falg
		char name[64];				//animation name

		ANIMATION(){
			begin = 0.0f;
			end = 0.0f;
			speed = 1.0f;
			time = 0.0f;
			loop = false;
			memset(name, 0, sizeof(char) * 64);
		}
	};

	int _mesh_count;
	MESH *_mesh;
	int _mesh_cursor;

	int _bone_count;
	BONE *_bone;
	BONE *_root;
	float _cur_time;					//���m�p
	int _bone_cursor;				//�{�[���ǂݍ��ݐ���w������

	//animation
	int _animation_count;				//animation�z��̐�
	ANIMATION *_animation;				//animation�z��擪

	int _current_animation;				//���݂̃A�j���[�V����
	int _previous_animation;
	bool _animation_blending;
	float _animation_blend_weight;
	int _animation_switching;			//�A�j���[�V�����ڍs����
	static const int ANIMATION_SWITCHING_TIME = 8;
	bool _play_flag;
	bool _pause;
	bool _transparent;

	bool _reverse;

	BONE* SearchBoneByName(char *name);

	//��]�L�[�t���[��
	//�����X�V
	void UpdateBoneMatrix(BONE *subject, D3DXMATRIX *parent);

	//�s�񂩂�rotation�𔲂��o��
	void ExtractTranslationFromMatrix(D3DXMATRIX *dst, D3DXMATRIX *src);
	void ExtractRotationFromMatrix(D3DXMATRIX *dst, D3DXMATRIX *src);
	void ExtractScalingFromMatrix(D3DXMATRIX *dst, D3DXMATRIX *src);

	//�L�[�t���[���Ԃ̕��
	D3DXVECTOR3 InterpolateTranslation(BONE *subject, float time);
	D3DXQUATERNION InterpolateRotation(BONE *subject, float time);
	D3DXVECTOR3 InterpolateScaling(BONE *subject, float time);

	D3DXVECTOR3 InterpolateBlendTranslation(BONE *subject, float prev_time, float next_time, float t);
	D3DXQUATERNION InterpolateBlendRotation(BONE *subject, float prev_time, float next_time, float t);
	D3DXVECTOR3 InterpolateBlendScaling(BONE *subject, float prev_time, float next_time, float t);

	LPDIRECT3DVERTEXDECLARATION9 _decl;

};


#endif//_MY_SKIN_MESH_H_