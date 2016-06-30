//*****************************************************************************
//  ぼくの　すうがく　かんすうぐん！
//  author: 中島将浩
//  update: 2014/07/15
//*****************************************************************************

#include "my_math.h"
#include <math.h>

//*****************************************************************************
//  ただの組み合わせ
//*****************************************************************************
int Conbination(int n, int k){
	int ret = 1;
	int i = 0;			//loop index

	for(i=k+1; i<=n; i++){
		ret *= i;
	}
	for(i=1; i<=n-k; i++){
		ret /= i;
	}

	return ret;
}

//*****************************************************************************
//  バーンスタイン基底関数
//*****************************************************************************
float BernsteinBasisPolynomials(int n, int k, float t){
	float ret = 1.0f;
	int i = 0;			//loop index

	//(n, k)
	ret *= (float)Conbination(n, k);

	//t^k * (1-t)^(n-k)
	for(i=0; i<k; i++){
		ret *= t;
	}
	for(; i<n; i++){
		ret *= (1.0f - t);
	}

	return ret;
}

//*****************************************************************************
//  三次ベジェ曲線
//*****************************************************************************
void CubicBezierCurve(D3DXVECTOR3 *b, float t, D3DXVECTOR3 *out_p){
	int i = 0;			//loop index
	float ret = 0.0f;

	if(b == NULL || out_p == NULL){return;}

	out_p->x = 0.0f;
	out_p->y = 0.0f;
	out_p->z = 0.0f;

	for(i=0; i<4; i++){
		*out_p += b[i] * BernsteinBasisPolynomials(3, i, t);
	}
}

//*****************************************************************************
//  三次ベジェ曲線の長さを得る
//*****************************************************************************
float CubicBezierCurveLength(D3DXVECTOR3 *b, float t0, float t1, float threshold){
	D3DXVECTOR3 p0(0.0f, 0.0f, 0.0f), p1(0.0f, 0.0f, 0.0f);
	float l = 0.0f;
	float t = (t0 + t1) / 2.0f;

	//t0,t1に対応する点を求める
	CubicBezierCurve(b, t0, &p0);
	CubicBezierCurve(b, t1, &p1);

	//p0p1間の長さを算出
	l = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y) + (p0.z-p1.z)*(p0.z-p1.z));

	//長すぎたら細分してもう一回！
	if(l > threshold){
		l = CubicBezierCurveLength(b, t0, t, threshold)
		  + CubicBezierCurveLength(b, t, t1, threshold);
	}

	return l;
}

//*****************************************************************************
//  三次ベジェ曲線の長さを得る
//*****************************************************************************
float CubicBezierCurveLength(D3DXVECTOR3 *b, float t, float delta){
	float l = 0.0f;
	D3DXVECTOR3 p0(0.0f, 0.0f, 0.0f), p1(0.0f, 0.0f, 0.0f);
	float t0 = 0.0f, t1 = delta;
	float ret = 0.0f;

	while(t1 < t){
		//t0,t1に対応する点を求める
		CubicBezierCurve(b, t0, &p0);
		CubicBezierCurve(b, t1, &p1);
		l = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y) + (p0.z-p1.z)*(p0.z-p1.z));
		ret += l;
		t0 = t1;
		t1 += delta;
	}

	return ret;
}

//*****************************************************************************
//  CubicBezierCurveLengthの逆射
//*****************************************************************************
float CubicBezierCurveLengthInverse(D3DXVECTOR3 *b, float length, float delta){
	float t0 = 0.0f, t1 = 1.0f;
	D3DXVECTOR3 p0(0.0f, 0.0f, 0.0f), p1(0.0f, 0.0f, 0.0f), p(0.0f, 0.0f, 0.0f);
	float l = 0.0f;
	float t = 0.0f;
	float d = 0.0f;
	
	t0 = 0.0f;
	t1 = delta;

	

	while(l < length){
		//t0,t1に対応する点を求める
		CubicBezierCurve(b, t0, &p0);
		CubicBezierCurve(b, t1, &p1);
		//p0p1間の長さを算出
		d = sqrt((p0.x-p1.x)*(p0.x-p1.x) + (p0.y-p1.y)*(p0.y-p1.y) + (p0.z-p1.z)*(p0.z-p1.z));
		l += d;
		
		t0 = t1;
		t1 += delta;
	}

	//t = (t0 + t1) / 2.0f;
	t = t0;

	return t;
}

void HermiteCurve(D3DXVECTOR3 *p0, D3DXVECTOR3 *p1, D3DXVECTOR3 *v0, D3DXVECTOR3 *v1, float t, D3DXVECTOR3 *out_p){
	float h00, h01, h10, h11;
	D3DXVECTOR3 p;

	h00 = (t - 1.0f) * (t - 1.0f) * (2.0f*t + 1);
	h01 = (-2.0f*t + 3.0f) * t * t;
	h10 = (1.0f - t) * (1.0f - t) * t;
	h11 = (t - 1.0f) * t * t;

	p = h00 * (*p0) +
		h01 * (*p1) +
		h10 * (*v0) +
		h11 * (*v1);

	*out_p = p;
}

//*****************************************************************************
//  三角形内外判定 y値は無視します
//*****************************************************************************
bool TriangleInside(D3DXVECTOR3 p0, D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p){
	bool ret(false);

	D3DXVECTOR3 v0(p0 - p);
	D3DXVECTOR3 v1(p1 - p);
	D3DXVECTOR3 v2(p2 - p);

	float c0(v0.x * v1.z - v1.x * v0.z);
	float c1(v1.x * v2.z - v2.x * v1.z);
	float c2(v2.x * v0.z - v0.x * v2.z);

	ret = (c0 >= 0.0f && c1 >= 0.0f && c2 >= 0.0f)
	   || (c0 <= 0.0f && c1 <= 0.0f && c2 <= 0.0f);

	return ret;
}

//*****************************************************************************
// -π～π fix
//*****************************************************************************
void PiSectionFix(float *dst, float *src){
	float work = *src;

	while(work < -D3DX_PI){
		work += 2.0f * D3DX_PI;
	}
	while(work >= D3DX_PI){
		work -= 2.0f * D3DX_PI;
	}

	*dst = work;
}

void PiSectionFix(D3DXVECTOR3 *dst, D3DXVECTOR3 *src){
	PiSectionFix(&dst->x, &dst->x);
	PiSectionFix(&dst->y, &dst->y);
	PiSectionFix(&dst->z, &dst->z);
}


D3DXVECTOR3 CalculateTriangleNormal(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3){
	D3DXVECTOR3 v1, v2;
	D3DXVECTOR3 ext;

	v1 = p2 - p1;
	v2 = p3 - p1;

	D3DXVec3Cross(&ext, &v1, &v2);
	float length(D3DXVec3Length(&ext));
	if(length < 0.5f){
		length = 0;
	}
	D3DXVec3Normalize(&ext, &ext);

	return ext;
}