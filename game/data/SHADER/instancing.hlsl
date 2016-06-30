float4x4 _wvp;
float4x4 _vp;
float4x4 _wv;
float4x4 _world;

float4 _light_direction;
float4 _light_diffuse;
float4 _light_ambient;
float4 _mat_diffuse;
float4 _mat_ambient;

sampler _tex_sampler1;
sampler _tex_sampler2;

void VSInstancing( in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					in float4 in_world0 : TEXCOORD1,
					in float4 in_world1 : TEXCOORD2,
					in float4 in_world2 : TEXCOORD3,
					in float4 in_world3 : TEXCOORD4,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD){
	float brightness;
	float4 normal;
	float4x4 world;
	world[0] = in_world0;
	world[1] = in_world1;
	world[2] = in_world2;
	world[3] = in_world3;
	float4x4 wvp = mul(world, _vp);

	normal = mul(float4(in_normal, 0.0f), world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;


	out_pos = mul(float4(in_pos, 1.0f), wvp);
	out_diffuse = _mat_diffuse * _light_diffuse * brightness;
	out_diffuse.a = _mat_diffuse.a;
	out_texcoord = in_texcoord;
}


void PSLightTexture(in float4 in_diffuse : COLOR,
					in float2 in_texcoord : TEXCOORD,
					out float4 out_diffuse : COLOR){

	out_diffuse = in_diffuse * tex2D(_tex_sampler1, in_texcoord);
	//out_diffuse = in_diffuse;
}
