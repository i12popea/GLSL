/*Fragment shader*/

uniform sampler2D color_texture;

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
		vec3 ct, cf;
		vec4 texel;
		float at, af;
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);
		//cf = lightingFactor * (gl_FrontMaterial.diffuse).rgb + gl_FrontMaterial.ambient.rgb;
		cf = lightingFactor * vec3(diffuseColor[i]) + gl_FrontMaterial.ambient.rgb;
		af = gl_FrontMaterial.diffuse.a;
		texel = texture2D(color_texture, gl_TexCoord[0].st);
		ct = texel.rgb;
		at = texel.a;
		total += vec4(ct * cf, at * af);

		//total += vec3(texture2D(color_texture, gl_TexCoord[0].st)) * lightingFactor + diffuseColor[i] * lightingFactor;
		//total += vec4(diffuseColor[i].xyz*vec3(texture2D(color_texture, gl_TexCoord[0].st))*lightingFactor);
		//total += texture2D(color_texture, gl_TexCoord[0].st) * lightingFactor + diffuseColor[i];
		//total += vec4(vec4(texture2D(color_texture, gl_TexCoord[0].st)).rgb * lightingFactor * diffuseColor[i].rgb * lightingFactor, 1);

	//	total += texture2D(color_texture, gl_TexCoord[0].st) + diffuseColor[i] * lightingFactor;

		//Estas líneas mezclan la textura con el color, puede ser útil para ficheros OBJ
		/*vec4 diff = lightingFactor * diffuseColor[i] * texture2D(color_texture, gl_TexCoord[0].st);
		vec4 amb = diffuseColor[i] * texture2D(color_texture, gl_TexCoord[0].st);
		total += max(diff, amb);*/
	}

	gl_FragColor = total;
}
