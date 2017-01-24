/*varying vec4 diffuseColor;
varying vec3 fragNormal;
varying vec3 lightVector;
uniform vec3 eyeSpaceLightVector;

void main()
{
	vec3 eyeSpaceVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	lightVector = vec3(normalize(eyeSpaceLightVector - eyeSpaceVertex));
	fragNormal = normalize(gl_NormalMatrix * gl_Normal);
	diffuseColor = gl_Color;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}*/

const int NUM_LIGHTS = 2;

//varying vec4 diffuseColor[NUM_LIGHTS];
uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 fragNormal;
varying vec3 lightVector[NUM_LIGHTS];
uniform vec3 eyeSpaceLightVector[NUM_LIGHTS];

void main()
{
	vec3 eyeSpaceVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		lightVector[i] = vec3(normalize(eyeSpaceLightVector[i]/*vec3(10, 1, 1)*/ - eyeSpaceVertex));
		//diffuseColor[i] = gl_Color;
	}
//diffuseColor[0] = vec4(1, 0, 0, 0);
//diffuseColor[1] = vec4(0, 1, 0, 0);
	fragNormal = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
