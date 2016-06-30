float4x4 _wvp;
float4x4 _wv;
float4x4 _world;

float4 _mat_diffuse;

sampler _tex_sampler1;
sampler _tex_sampler2;

void VS2D(	in float3 in_pos : POSITION0,
			in float4 in_diffuse : COLOR0,
			in float2 in_texcoord : TEXCOORD0,
			out float4 out_pos : POSITION,
			out float4 out_diffuse : COLOR,
			out float2 out_texcoord : TEXCOORD){
	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = in_diffuse;
	out_texcoord = in_texcoord;
}


void PSTexture(	in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD,
				out float4 out_diffuse : COLOR){

	out_diffuse = in_diffuse * tex2D(_tex_sampler1, in_texcoord);
}
