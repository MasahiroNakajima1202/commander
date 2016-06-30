float4x4 _wvp;
float4x4 _wv;
float4x4 _world;
float4x4 _rotation;

float4x4 _light_matrix;

float4 _light_diffuse;
float4 _light_ambient;
float4 _mat_diffuse;
float4 _mat_ambient;

sampler _tex_sampler1;
sampler _tex_sampler2;
sampler _toon_sampler;
sampler _fur_sampler;
sampler _normal_depth_map;
sampler _posterization;
sampler _shadow_sampler;
float2 _texture_resolution;
float _weight;

float3 _light_direction;
float3 _camera_position;

float3 _shadow_owner;

float _target_depth;
float _camera_far;

float _fur_offset;
float3 _camera_direction;

void VertexShader3D(in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD){
	float brightness;
	float4 normal;
	float4 ambient;
	float4 lambert;
	float4 half_lambert;
	float4 murase;

	normal = mul(float4(in_normal, 0.0f), _world);

	//ambient
	ambient = _mat_ambient * _light_ambient;

	//lambert
	brightness = -dot(normal, _light_direction);
	brightness = max(brightness, 0.0f);
	lambert = _mat_diffuse * _light_diffuse * brightness;

	//half lambert
	normal = mul(float4(in_normal, 0.0f), _world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;
	half_lambert = _mat_diffuse * _light_diffuse * brightness;

	//murase
	float3 camera_vector;
	float3 position = mul(float4(in_pos, 1.0f), _world);
	camera_vector = normalize(position - _camera_position);
	brightness = 1.0f - abs( dot(normal, camera_vector) ) * 1.6f;
	brightness = max(brightness, 0.0f);
	murase = _mat_diffuse * _light_diffuse * brightness;

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = 0.5f * ambient
	            + 0.2f * lambert
				+ 1.0f * half_lambert
				+ 0.4f * murase;
	out_diffuse.a = 1.0f;
	out_texcoord = in_texcoord;
}

void VSAmbient( in float3 in_pos : POSITION0,
				in float4 in_diffuse : COLOR0,
				in float3 in_normal: NORMAL0,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_pos : POSITION,
				out float4 out_diffuse : COLOR,
				out float2 out_texcoord : TEXCOORD){

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = _mat_ambient * _light_ambient;
	out_diffuse.a = 1.0f;
	out_texcoord = in_texcoord;
}

void VSLambert( in float3 in_pos : POSITION0,
				in float4 in_diffuse : COLOR0,
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


void VSHalfLambert( in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD){
	float brightness;
	float4 normal;

	normal = mul(float4(in_normal, 0.0f), _world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;


	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = _mat_diffuse * _light_diffuse * brightness;
	out_diffuse.a = 1.0f;
	out_texcoord = in_texcoord;
}

void VSMuraseEdge(  in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD){
	float brightness;

	float3 camera_vector;

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	float3 position = mul(float4(in_pos, 1.0f), _world);
	float3 normal = mul(float4(in_normal, 0.0f), _world);

	camera_vector = normalize(position - _camera_position);
	brightness = 1.0f - abs( dot(normal, camera_vector) ) * 1.6f;
	brightness = max(brightness, 0.0f);

	
	out_diffuse = _mat_diffuse * _light_diffuse * brightness;
	out_diffuse.a = 1.0f;
	out_texcoord = in_texcoord;
}

void VSNkj( in float3 in_pos : POSITION0,
			in float4 in_diffuse : COLOR0,
			in float3 in_normal: NORMAL0,
			in float2 in_texcoord : TEXCOORD0,
			out float4 out_pos : POSITION,
			out float4 out_diffuse : COLOR,
			out float2 out_texcoord : TEXCOORD){
	float brightness;
	float4 normal;
	float4 ambient;
	float4 lambert;
	float4 half_lambert;
	float4 murase;

	normal = mul(float4(in_normal, 0.0f), _world);

	//ambient
	ambient = _mat_ambient * _light_ambient;

	//lambert
	brightness = -dot(normal, _light_direction);
	brightness = max(brightness, 0.0f);
	lambert = _mat_diffuse * _light_diffuse * brightness;

	//half lambert
	normal = mul(float4(in_normal, 0.0f), _world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;
	half_lambert = _mat_diffuse * _light_diffuse * brightness;

	//murase
	float3 camera_vector;
	float3 position = mul(float4(in_pos, 1.0f), _world);
	camera_vector = normalize(position - _camera_position);
	brightness = 1.0f - abs( dot(normal, camera_vector) ) * 1.6f;
	brightness = max(brightness, 0.0f);
	murase = _mat_diffuse * _light_diffuse * brightness;

	float heat_param = -dot(normal, _light_direction);
	float4 heat = float4(0.2f, 0.1f, -0.2f, 0.0f);

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = 0.5f * ambient
	            + 0.2f * lambert
				+ 1.0f * half_lambert
				+ 0.4f * murase
				+ + heat * heat_param;
	out_diffuse = max(0.0f, out_diffuse);
	out_diffuse = min(1.0f, out_diffuse);
	out_diffuse.a = 1.0f;
	out_texcoord = in_texcoord;
}

void VSToon(in float3 in_pos : POSITION0,
			in float4 in_diffuse : COLOR0,
			in float3 in_normal: NORMAL0,
			in float2 in_texcoord : TEXCOORD0,
			out float4 out_pos : POSITION,
			out float4 out_diffuse : COLOR,
			out float2 out_texcoord : TEXCOORD){
	float brightness;

	float3 camera_vector;

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	float3 position = mul(float4(in_pos, 1.0f), _world);
	float3 normal = mul(float4(in_normal, 0.0f), _world);

	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;
	out_texcoord.x = brightness;

	camera_vector = normalize(position - _camera_position);
	brightness = abs( dot(normal, camera_vector) );
	out_texcoord.y = 0.1f + brightness * 0.5f;
	
	out_diffuse = _mat_diffuse;
}


void VSNormalDepth( in float3 in_pos : POSITION0,
				in float4 in_diffuse : COLOR0,
				in float3 in_normal: NORMAL0,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_pos : POSITION,
				out float4 out_diffuse : COLOR,
				out float2 out_texcoord : TEXCOORD){

	float brightness;
	float4 normal;

	normal = mul(float4(in_normal, 0.0f), _world);

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_texcoord = in_texcoord;

	out_diffuse = normal;
	out_diffuse.a = out_pos.z / out_pos.w;
}

void VSNormalLinearDepth( in float3 in_pos : POSITION0,
				in float4 in_diffuse : COLOR0,
				in float3 in_normal: NORMAL0,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_pos : POSITION,
				out float4 out_diffuse : COLOR,
				out float2 out_texcoord : TEXCOORD){

	float brightness;
	float4 normal;

	normal = mul(float4(in_normal, 0.0f), _world);

	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_texcoord = in_texcoord;

	float4 linear_pos = mul(float4(in_pos, 1.0f), _wv);

	out_diffuse = normal;
	out_diffuse = (linear_pos.z / linear_pos.w) / _camera_far;
	out_diffuse.a = 1.0f;
}

void VS2D( in float3 in_pos : POSITION0,
				in float4 in_diffuse : COLOR0,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_pos : POSITION,
				out float4 out_diffuse : COLOR,
				out float2 out_texcoord : TEXCOORD){

	out_pos = float4(in_pos, 1.0f);
	out_texcoord = in_texcoord;
	out_diffuse = in_diffuse;

}

void VSShadow( in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD0,
					out float2 out_shadow_texcoord : TEXCOORD1,
					out float4 out_proj_texcoord : TEXCOORD2){
	float brightness;
	float4 normal;

	normal = mul(float4(in_normal, 0.0f), _world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;


	out_pos = mul(float4(in_pos, 1.0f), _wvp);
	out_diffuse = _mat_diffuse * _light_diffuse * brightness;
	out_diffuse.a = 1.0f;

	float3 player_position = _shadow_owner;
	out_shadow_texcoord.x = -(in_pos.x - player_position.x) * 0.007f + 0.5f;
	out_shadow_texcoord.y = (in_pos.z - player_position.z) * 0.007f + 0.5f;

	out_shadow_texcoord = clamp(out_shadow_texcoord, 0.0f, 1.0f);

	out_texcoord = in_texcoord;

	float4 uv = mul(float4(in_pos, 1.0f), _light_matrix);

	uv /= uv.w;

	uv.x = uv.x * 0.5f + 0.5f;
	uv.y = -uv.y * 0.5f + 0.5f;

	uv = clamp(uv, 0.0f, 1.0f);


	out_proj_texcoord = uv;
}

void VSFur( in float3 in_pos : POSITION0,
					in float4 in_diffuse : COLOR0,
					in float3 in_normal: NORMAL0,
					in float2 in_texcoord : TEXCOORD0,
					out float4 out_pos : POSITION,
					out float4 out_diffuse : COLOR,
					out float2 out_texcoord : TEXCOORD){
	float brightness;
	float side_color;
	float4 normal;

	float3 pos = in_pos;
	pos += _fur_offset * in_normal;

	normal = mul(float4(in_normal, 0.0f), _world);
	brightness = -dot(normal, _light_direction) * 0.5f + 0.5f;
	side_color = 1.0f - abs(dot(normal.xyz, _camera_direction));

	out_pos = mul(float4(pos, 1.0f), _wvp);
	out_diffuse = _mat_diffuse * _light_diffuse * (brightness * 0.5f  + side_color * 0.5f);
	out_diffuse *= _fur_offset * 1.0f / 4.0f;
	out_diffuse.a = 1.0f - _fur_offset * 0.5f / 4.0f;
	out_texcoord = in_texcoord;
}

void PixelShader3D(	in float4 in_diffuse : COLOR,
					in float2 in_texcoord : TEXCOORD,
					out float4 out_diffuse : COLOR){

	out_diffuse = in_diffuse;
	//out_diffuse = in_diffuse;
}

void PixelShaderTex3D(	in float2 in_texcoord : TEXCOORD,
						out float4 out_diffuse : COLOR){

	out_diffuse =tex2D(_tex_sampler1, in_texcoord);
	//out_diffuse = in_diffuse;
}

void PSFur(	in float4 in_diffuse : COLOR,
			in float2 in_texcoord : TEXCOORD,
			out float4 out_diffuse : COLOR){

	out_diffuse = in_diffuse * tex2D(_fur_sampler, in_texcoord);
	
	//out_diffuse = in_diffuse;
}

void PSToon(in float4 in_diffuse : COLOR,
			in float2 in_texcoord : TEXCOORD0,
			out float4 out_diffuse : COLOR){

	out_diffuse = tex2D(_toon_sampler, in_texcoord) * in_diffuse;
}

void PSNormalDepth(	in float4 in_diffuse : COLOR,
					in float2 in_texcoord : TEXCOORD0,
					out float4 out_diffuse : COLOR){
	out_diffuse = in_diffuse;
}

void PSToonDepthEdge(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_diffuse : COLOR){
	float4 n1, n2, n3, n4;
	float2 pixel_offset;
	pixel_offset = 1.0f / _texture_resolution;
	n1 = tex2D(_normal_depth_map, float2(in_texcoord.x - pixel_offset.x, in_texcoord.y - pixel_offset.y));		//ç∂è„
	n2 = tex2D(_normal_depth_map, float2(in_texcoord.x + pixel_offset.x, in_texcoord.y - pixel_offset.y));		//âEè„
	n3 = tex2D(_normal_depth_map, float2(in_texcoord.x - pixel_offset.x, in_texcoord.y + pixel_offset.y));		//ç∂â∫
	n4 = tex2D(_normal_depth_map, float2(in_texcoord.x + pixel_offset.x, in_texcoord.y + pixel_offset.y));		//ç∂â∫

	float4 delta = abs(n1 - n4) + abs(n2 - n3);
	delta = saturate((delta - 0.01f) * 20.0f);

	float edge_amount = saturate(delta.w * 1.0f);
	out_diffuse = float4((float3)(1.0f - edge_amount), 1.0f);
}

void PSToonNormalEdge(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_diffuse : COLOR){
	float4 n1, n2, n3, n4;
	float2 pixel_offset;
	pixel_offset = 1.0f / _texture_resolution;
	n1 = tex2D(_normal_depth_map, float2(in_texcoord.x - pixel_offset.x, in_texcoord.y - pixel_offset.y));		//ç∂è„
	n2 = tex2D(_normal_depth_map, float2(in_texcoord.x + pixel_offset.x, in_texcoord.y - pixel_offset.y));		//âEè„
	n3 = tex2D(_normal_depth_map, float2(in_texcoord.x - pixel_offset.x, in_texcoord.y + pixel_offset.y));		//ç∂â∫
	n4 = tex2D(_normal_depth_map, float2(in_texcoord.x + pixel_offset.x, in_texcoord.y + pixel_offset.y));		//ç∂â∫

	float4 delta = abs(n1 - n4) + abs(n2 - n3);

	float normal_delta = dot(delta.rgb, 1.0f);
	normal_delta = saturate((normal_delta - 0.8f) * 10.0f);

	out_diffuse = float4((float3)(1.0f - normal_delta), 1.0f);
}

void PSPostToon(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_diffuse : COLOR){
	float4 n1, n2, n3, n4;
	float2 pixel_offset;
	pixel_offset = 1.0f / _texture_resolution;
	n1 = tex2D(_normal_depth_map, float2(in_texcoord.x - pixel_offset.x, in_texcoord.y - pixel_offset.y));		//ç∂è„
	n2 = tex2D(_normal_depth_map, float2(in_texcoord.x + pixel_offset.x, in_texcoord.y - pixel_offset.y));		//âEè„
	n3 = tex2D(_normal_depth_map, float2(in_texcoord.x - pixel_offset.x, in_texcoord.y + pixel_offset.y));		//ç∂â∫
	n4 = tex2D(_normal_depth_map, float2(in_texcoord.x + pixel_offset.x, in_texcoord.y + pixel_offset.y));		//ç∂â∫

	float4 delta = abs(n1 - n4) + abs(n2 - n3);

	float normal_delta = dot(delta.rgb, 1.0f);
	normal_delta = saturate((normal_delta - 0.4f) * 1.0f);

	float4 normal_diffuse = float4((float3)(1.0f - normal_delta), 1.0f);

	delta = saturate((delta - 0.25f) * 1.0f);

	float edge_amount = saturate(delta.w * 1.0f);
	float4 depth_diffuse = float4((float3)(1.0f - edge_amount), 1.0f);

	float4 edge_diffuse = normal_diffuse * 0.5f + depth_diffuse * 0.5f;

	float4 inside_color;

	inside_color = tex2D(_posterization, in_texcoord);

	out_diffuse = edge_diffuse * inside_color;
}

void PSRenderShadow(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_diffuse : COLOR){
	out_diffuse = float4(1.0f / 16.0f, 1.0f / 16.0f, 1.0f / 16.0f, 1.0f);
}

void PSShadow(	in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				in float2 in_shadow_texcoord : TEXCOORD1,
				in float4 in_proj_texcoord : TEXCOORD2,
				out float4 out_diffuse : COLOR){
	//float4 shadow_diffuse = tex2D(_shadow_sampler, in_shadow_texcoord);
	float4 shadow_diffuse = tex2D(_shadow_sampler, in_proj_texcoord.xy);
	out_diffuse = in_diffuse * tex2D(_tex_sampler1, in_texcoord) * shadow_diffuse;
}

void PSGaussianH(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				in float2 in_shadow_texcoord : TEXCOORD1,
				out float4 out_diffuse : COLOR){
	float2 pixel_offset;
	pixel_offset = 1.0f / _texture_resolution;

	// 1.0 / 2ÉŒÉ– * exp(-(x^2 + y^2) / 2É–^2)

	float sigma = 5.0f;
	float EXP_DEV = 2.0f * sigma * sigma;
	float sum = exp(-(3.0f * 3.0f) / EXP_DEV) * 2.0f
			  + exp(-(2.0f * 2.0f) / EXP_DEV) * 2.0f
			  + exp(-(1.0f * 1.0f) / EXP_DEV) * 2.0f
			  + exp(-(0.0f * 0.0f) / EXP_DEV);
	
	out_diffuse = 
	  tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x *  3.0f, in_texcoord.y)) * exp(-(3.0f * 3.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x *  2.0f, in_texcoord.y)) * exp(-(2.0f * 2.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x *  1.0f, in_texcoord.y)) * exp(-(1.0f * 1.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x *  0.0f, in_texcoord.y)) * exp(-(0.0f * 0.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x * -1.0f, in_texcoord.y)) * exp(-(1.0f * 1.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x * -2.0f, in_texcoord.y)) * exp(-(2.0f * 2.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x - pixel_offset.x * -3.0f, in_texcoord.y)) * exp(-(3.0f * 3.0f) / EXP_DEV) / sum;
}

void PSGaussianV(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				in float2 in_shadow_texcoord : TEXCOORD1,
				out float4 out_diffuse : COLOR){
	float2 pixel_offset;
	pixel_offset = 1.0f / _texture_resolution;

	float sigma = 5.0f;
	float EXP_DEV = 2.0f * sigma * sigma;
	float sum = exp(-(3.0f * 3.0f) / EXP_DEV) * 2.0f
			  + exp(-(2.0f * 2.0f) / EXP_DEV) * 2.0f
			  + exp(-(1.0f * 1.0f) / EXP_DEV) * 2.0f
			  + exp(-(0.0f * 0.0f) / EXP_DEV);
	
	out_diffuse = 
	  tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y *  3.0f)) *  exp(-(3.0f * 3.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y *  2.0f)) *  exp(-(2.0f * 2.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y *  1.0f)) *  exp(-(1.0f * 1.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y *  0.0f)) *  exp(-(0.0f * 0.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y * -1.0f)) *  exp(-(1.0f * 1.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y * -2.0f)) *  exp(-(2.0f * 2.0f) / EXP_DEV) / sum
	+ tex2D(_tex_sampler1, float2(in_texcoord.x, in_texcoord.y - pixel_offset.y * -3.0f)) *  exp(-(3.0f * 3.0f) / EXP_DEV) / sum;
}

void PSFrustumGaussian(in float4 in_diffuse : COLOR,
				in float2 in_texcoord : TEXCOORD0,
				out float4 out_diffuse : COLOR){
	float depth = tex2D(_normal_depth_map, in_texcoord).r;
	float blend = abs(_target_depth - depth);
	blend = saturate(blend * 4.0f);

	//blend = 0.0f;

	out_diffuse = tex2D(_tex_sampler1, in_texcoord) * blend
				+ tex2D(_tex_sampler2, in_texcoord) * (1.0f - blend);

	out_diffuse.a = 1.0f;
}