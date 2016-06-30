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

sampler _toon_sampler;

void VSToon(in float3 in_pos : POSITION0,
			in float4 in_diffuse : COLOR0,
			in float3 in_normal: NORMAL0,
			in float2 in_texcoord : TEXCOORD0,
			out float4 out_pos : POSITION,
			out float4 out_diffuse : COLOR,
			out float2 out_texcoord : TEXCOORD,
			out float2 out_toon_texcoord : TEXCOORD1){
	float brightness;

	float3 camera_vector;

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	float3 position = mul(float4(in_pos, 1.0f), _world);
	float3 normal = mul(float4(in_normal, 0.0f), _world);

	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;
	out_toon_texcoord.x = brightness;

	camera_vector = normalize(position - _camera_position);
	brightness = abs( dot(normal, camera_vector) );
	out_toon_texcoord.y = 0.1f + brightness * 0.5f;

	out_texcoord = in_texcoord;
	
	out_diffuse = _mat_diffuse;
}



void PSToon(in float4 in_diffuse : COLOR,
			in float2 in_texcoord : TEXCOORD0,
			in float2 in_toon_texcoord : TEXCOORD1,
			out float4 out_diffuse : COLOR){

	out_diffuse = tex2D(_toon_sampler, in_toon_texcoord) * tex2D(_tex_sampler1, in_texcoord) * in_diffuse;
}