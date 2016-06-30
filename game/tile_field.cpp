//*****************************************************************************
//  タイルによる地形
//  author: 中島将浩
//  update: 2016/02/24
//*****************************************************************************
#include "tile_field.h"
#include "tile_field_image.h"

const float TileField::TILE_SIZE(20.0f);
const float TileField::TILE_HEIGHT(5.0f);
const int TileField::TILE_STACK_LIMIT(32);


TileField::TileField(Renderer *renderer, int width, int depth):
ModelField(renderer, ""),
_width(max(0, width)),
_depth(max(0, depth)),
_height_map(nullptr),
_image(nullptr){
	int size(_width * _depth);
	if(size > 0){
		_height_map = new int[size];
		for(int i = 0; i<size; i++){
			_height_map[i] = 0;
		}
	}

	//描画オブジェクトの生成
	_image = new TileFieldImage(_renderer);
	_image->SetUp(this);
}

TileField::~TileField(){
	if(_height_map != nullptr){
		delete[] _height_map;
		_height_map = nullptr;
	}

	if(_image != nullptr){
		_image->Destroy();
		_image = nullptr;
	}
}

void TileField::Update(void){
	if(_height_map == nullptr){return;}
}

float TileField::GetHeight(float x, float z){
	if(_height_map == nullptr){return 0.0f;}

	float x_bottom(static_cast<float>(_width) * -0.5f * TILE_SIZE);
	float z_bottom(static_cast<float>(_depth) * -0.5f * TILE_SIZE);
	int x_index(static_cast<int>((x - x_bottom) / TILE_SIZE));
	int z_index(static_cast<int>((z - z_bottom) / TILE_SIZE));

	if(x_index < 0 || _width <= x_index
	|| z_index < 0 || _depth <= z_index){
		return 0.0f;
	}

	float height(TILE_HEIGHT * static_cast<float>(_height_map[z_index * _width + x_index]));
	return height;
}

int TileField::GetIndexHeight(int x_index, int z_index){
	if(_height_map == nullptr){return 0;}

	int index(z_index * _width + x_index);
	int ret(0);
	if(0 <= index && index < _width * _depth){
		ret = _height_map[index];
	}

	return ret;
}


bool TileField::FixLay(D3DXVECTOR3 &dst, D3DXVECTOR3 src, D3DXVECTOR3 begin){
	if(_height_map == nullptr){return false;}
	if(D3DXVec3Dot(&src, &src) <= 0.001f){return false;}

	D3DXVECTOR3 work_begin(begin);
	D3DXVECTOR3 work_end(begin + src);
	D3DXVECTOR3 normal_lay(src);
	D3DXVec3Normalize(&normal_lay, &normal_lay);

	int x_sign(1), z_sign(1);
	if(normal_lay.x < 0.0f){
		x_sign = -x_sign;
	}
	if(normal_lay.z < 0.0f){
		z_sign = -z_sign;
	}

	//次の格子点までの距離(変動値なので負も存在)
	D3DXVECTOR3 cur_position(work_begin);
	bool enter(false);
	int x_index(0), z_index(0);
	PositionToIndex(cur_position.x, cur_position.z, x_index, z_index);
	bool hit(false);
	D3DXVECTOR3 hit_position(0.0f, 0.0f, 0.0f);

	float x_distance(GetXDistance(work_begin.x));
	float z_distance(GetZDistance(work_begin.z));
	if(x_sign < 0){
		x_distance = x_distance - TILE_SIZE;
		if(x_distance >= 0.0f){
			x_distance -= TILE_SIZE;
		}
	}
	if(z_sign < 0){
		z_distance = z_distance - TILE_SIZE;
		if(z_distance >= 0.0f){
			z_distance -= TILE_SIZE;
		}
	}


	while(!enter
		|| (0 <= x_index && x_index < _width
		&& 0 <= z_index && z_index < _depth)){
		//格子点までの距離の再計算
		x_distance = (GetXDistance(cur_position.x));
		z_distance = (GetZDistance(cur_position.z));
		if(x_sign < 0){
			x_distance = x_distance - TILE_SIZE;
			if(x_distance >= 0.0f){
				x_distance -= TILE_SIZE;
			}
		}
		if(z_sign < 0){
			z_distance = z_distance - TILE_SIZE;
			if(z_distance >= 0.0f){
				z_distance -= TILE_SIZE;
			}
		}
		//next indexの算出
		int next_x_index(x_index);
		int next_z_index(z_index);
		D3DXVECTOR3 next_position(work_begin);

		//本当はz_distance / x_distance < normal_lay.z / normal_lay.xをチェックしたいが、ゼロ除算を気にして同値な式で判定
		float sign(static_cast<float>(x_sign * z_sign));
		if(sign * (normal_lay.x * z_distance - x_distance * normal_lay.z) < 0.0f){
			//normal_layのほうが傾きが大きい z方向に先に着地
			next_z_index += z_sign;
			float length(z_distance / normal_lay.z);
			next_position = cur_position + length * normal_lay;
		}
		else{
			//normal_layのほうが傾きが小さい x方向に着地
			next_x_index += x_sign;
			float length(x_distance / normal_lay.x);
			next_position = cur_position + length * normal_lay;
		}

		//内部にいたときのみチェック
		if((0 <= x_index && x_index < _width
		&& 0 <= z_index && z_index < _depth)){
			float cur_height(TILE_HEIGHT * static_cast<float>(_height_map[z_index * _width + x_index]));
			
			//cur_positionの高さがindexの示す高さを下回っているかどうかチェック
			if(cur_position.y < cur_height){
				//ここでhit
				hit = true;
				hit_position = cur_position;
				break;
			}
			//下回っていなかったら、nextについて同じチェック
			else if(next_position.y < cur_height){
				//このマスの地表でhit
				hit = true;
				float length((cur_position.y - cur_height) / -normal_lay.y);
				hit_position = cur_position + normal_lay * length;
				break;
			}
			

			//両方ハズレだったら次周へ持ち越し
			enter = true;
		}

		//index更新
		x_index = next_x_index;
		z_index = next_z_index;
		cur_position = next_position;

		//長さチェック
		D3DXVECTOR3 lay(cur_position - begin);
		float sq_max(D3DXVec3Dot(&src, &src));
		float sq_length(D3DXVec3Dot(&lay, &lay));
		if(sq_length > sq_max){
			break;
		}
	}

	if(hit){
		dst = hit_position - begin;
	}

	return hit;
}

void TileField::PositionToIndex(float x, float z, int& x_index, int& z_index){
	x /= TILE_SIZE;
	z /= TILE_SIZE;
	int work_x(static_cast<int>(x + static_cast<float>(_width) * 0.5f));
	int work_z(static_cast<int>(z + static_cast<float>(_depth) * 0.5f));
	//if(x < -static_cast<float>(_width) * 0.5f){work_x--;}
	//if(z < -static_cast<float>(_depth) * 0.5f){work_z--;}
	//if(x < 0.0f){work_x--;}
	//if(z < 0.0f){work_z--;}

	x_index = work_x;
	z_index = work_z;
}

void TileField::StackTile(int x_index, int z_index, int number){
	if(_height_map == nullptr){return;}
	if(x_index < 0 || _width <= x_index){return;}
	if(z_index < 0 || _depth <= z_index){return;}

	int index(z_index * _width + x_index);
	_height_map[index] += number;
}

void TileField::LeaveTile(int x_index, int z_index, int number){
	if (_height_map == nullptr){ return; }
	if (x_index < 0 || _width <= x_index){ return; }
	if (z_index < 0 || _depth <= z_index){ return; }

	int index(z_index * _width + x_index);
	_height_map[index] -= number;
	_height_map[index] = max(0, _height_map[index]);
}

void TileField::CommitImage(void){
	if(_image == nullptr){return;}
	_image->CommitImage();
}


float TileField::GetXDistance(float x){
	x -= static_cast<float>(_width) * 0.5f * TILE_SIZE;
	float begin(static_cast<float>(static_cast<int>(x / TILE_SIZE)) * TILE_SIZE - TILE_SIZE);
	float grid(begin);
	while(grid <= x){
		grid += TILE_SIZE;
	}
	float distance(grid - x);
	return distance;
}
float TileField::GetZDistance(float z){
	z -= static_cast<float>(_depth) * 0.5f * TILE_SIZE;
	float begin(static_cast<float>(static_cast<int>(z / TILE_SIZE)) * TILE_SIZE - TILE_SIZE);
	float grid(begin);
	while(grid <= z){
		grid += TILE_SIZE;
	}
	float distance(grid - z);
	return distance;
}

