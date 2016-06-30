float4x4 _wvp;
float4x4 _vp;
float4x4 _world;

float4 _light_diffuse;
float3 _light_direction;
float4 _light_ambient;
float4 _mat_diffuse;
float4 _mat_ambient;

sampler _tex_sampler1;

float3 _camera_position;

float4x4 _world_array[52];

void VSSkinMesh( in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					in float3 in_blend_weight : BLENDWEIGHT0,
					in float4 in_blend_index : BLENDINDICES,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD,
					out float3 out_normal : TEXCOORD1){
	float brightness;
	float3 normal;

	int index0, index1, index2, index3;
	float weight0, weight1, weight2, weight3;
	float4x4 world0, world1, world2, world3;

	
	index0 = in_blend_index.x;
	index1 = in_blend_index.y;
	index2 = in_blend_index.z;
	index3 = in_blend_index.w;

	weight0 = in_blend_weight.x;
	weight1 = in_blend_weight.y;
	weight2 = in_blend_weight.z;
	weight3 = 1.0f - weight0 - weight1 - weight2;

	world0 = _world_array[index0];
	world1 = _world_array[index1];
	world2 = _world_array[index2];
	world3 = _world_array[index3];

	//worldÇ∆vpÇÇ©ÇØÇ†ÇÌÇπÇÎÅI
	float4x4 world =  world0 * weight0
					+ world1 * weight1
					+ world2 * weight2
					+ world3 * weight3;
	float4 temp_pos = mul(float4(in_pos, 1.0f), world);
	temp_pos = mul(temp_pos, _vp);

	float4 temp_normal = mul(float4(in_normal, 0.0f), world);
	temp_normal = normalize(temp_normal);

	normal = (float3)mul(float4(in_normal, 0.0f), world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;

	out_pos = temp_pos;
	out_diffuse = _mat_diffuse * _light_diffuse * brightness;
	out_diffuse.a = _mat_diffuse.a;
	out_texcoord = in_texcoord;
	out_normal = temp_normal.xyz;
}

void PSLightTexture(	in float2 in_texcoord : TEXCOORD0,
						in float4 in_diffuse : COLOR,
						out float4 out_diffuse : COLOR){

	out_diffuse = tex2D(_tex_sampler1, in_texcoord) * in_diffuse;
}
