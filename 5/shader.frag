/*varying vec4 diffuseColor;
varying vec3 lightVector;
varying vec3 fragNormal;

void main()
{
	float lightingFactor = max(dot(lightVector, fragNormal), 0.0);
	gl_FragColor = diffuseColor * lightingFactor;
}*/

const int NUM_LIGHTS = 2;

//varying vec4 diffuseColor[NUM_LIGHTS];
uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];
varying vec3 fragNormal;

void main()
{
	vec4 total = vec4(0, 0, 0, 0);// = diffuseColor;
	float lightingFactor;
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);
		total += diffuseColor[i] * lightingFactor;
	}
//total = diffuseColor[0] * lightingFactor[0];
//total += diffuseColor[1] * lightingFactor[1];
	//gl_FragColor = diffuseColor * lightingFactor;
	gl_FragColor = total;//diffuseColor * lightingFactor;
}
