float4x4 _wvp;
float4x4 _wv;
float4x4 _world;

float4 _light_direction;
float4 _light_diffuse;
float4 _light_ambient;
float4 _mat_diffuse;
float4 _mat_ambient;

sampler _tex_sampler1;
sampler _tex_sampler2;

void VSLambert( in float3 in_pos : POSITION0,
				in float3 in_normal: NORMAL0,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_pos : POSITION,
				out float4 out_diffuse : COLOR,
				out float2 out_texcoord : TEXCOORD){

	float brightness;
	float4 normal;

	normal = mul(float4(in_normal, 0.0f), _world);
	brightness = -dot(normal, _light_direction);

	brightness = max(brightness, 0.0f);

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = _mat_diffuse * _light_diffuse * brightness;
	out_diffuse.a = 1.0f;
	out_texcoord = in_texcoord;
}


void PSLightTexture(in float4 in_diffuse : COLOR,
					in float2 in_texcoord : TEXCOORD,
					out float4 out_diffuse : COLOR){

	out_diffuse = in_diffuse * tex2D(_tex_sampler1, in_texcoord);
	//out_diffuse = in_diffuse;
}
