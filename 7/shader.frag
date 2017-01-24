/*Fragment shader*/

uniform sampler2D texture1, texture2;

const int NUM_LIGHTS = 1;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];
varying vec3 fragNormal;

void main()
{
	vec4 total = vec4(0, 0, 0, 0);
	float lightingFactor;
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		/*vec3 c;
		float a;*/
		vec3 ct, cf;
		vec4 texel;
		float at, af;
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);
		//cf = lightingFactor * (gl_FrontMaterial.diffuse).rgb + gl_FrontMaterial.ambient.rgb;
		cf = lightingFactor * vec3(diffuseColor[i]) + gl_FrontMaterial.ambient.rgb;
		af = gl_FrontMaterial.diffuse.a;
		texel = texture2D(texture1, gl_TexCoord[0].st) + texture2D(texture2, gl_TexCoord[0].st);
		ct = texel.rgb;
		at = texel.a;
		total += vec4(ct * cf, at * af);

		/*texel = texture2D(texture1, gl_TexCoord[0].st);

		ct = texel.rgb;
		at = texel.a;

		c = cf * ct;
		a = af * at;
		 
		float coef = smoothstep(1.0, 0.2, intensity);
		c += coef * vec3(texture2D(texture2, gl_TexCoord[0].st));

		total += vec4(c, a);*/
	}

	gl_FragColor = total;
}
