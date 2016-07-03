#version 440 core

struct info_screen {
	vec2 window_size;
	vec2 view_size;
};

struct info_effect_pixelate {
	vec2 sample_size;
	float strength;
};

uniform sampler2D scene;
uniform sampler2D blur;
uniform vec4 col;
uniform float pixel_size;

uniform info_screen 		 s_screen;
uniform info_effect_pixelate s_effect_pixelate;

in vec2 in_UV;

out vec4 color;

vec3 interp_nearest( sampler2D base, float x, float y, float sample_x, float sample_y, float strength ) {
	float dx = sample_x *(1./1600.0) * strength;
	float dy = sample_y *(1./1024.0) * strength;
	vec2 coord = vec2(dx*floor(x/dx), dy*floor(y/dy));
	return texture2D(base, coord).rgb;
}

void main(void) { 

	vec3 pixelate_color = interp_nearest( scene, in_UV.x, in_UV.y, s_effect_pixelate.sample_size.x, s_effect_pixelate.sample_size.y, s_effect_pixelate.strength );
	vec3 bloom_color = interp_nearest( blur, in_UV.x, in_UV.y, s_effect_pixelate.sample_size.x, s_effect_pixelate.sample_size.y, s_effect_pixelate.strength );

	//if( pixelate_color.r > 1.0 || pixelate_color.g > 1.0 || pixelate_color.b > 1.0 ) {
	
		const float exposure = 0.3;
		const float gamma = 2;
		vec3 hdrColor = pixelate_color;
		vec3 bloomColor = bloom_color;
		hdrColor += bloomColor; // additive blending
		// tone mapping
		vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
		// also gamma correct while we're at it       
		result = pow(result, vec3(1.0 / gamma));
		color = vec4(result, 1.0f);
	
	//} else {
	//	color = vec4( pixelate_color, 1.0 );
	//}
	
}