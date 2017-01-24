varying vec4 diffuseColor;
varying vec3 lightVector;
varying vec3 fragNormal;

void main()
{
	float lightingFactor = max(dot(lightVector, fragNormal), 0.0);
	gl_FragColor = diffuseColor * lightingFactor;
}
