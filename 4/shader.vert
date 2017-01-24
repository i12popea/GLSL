varying vec4 diffuseColor;
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
}
