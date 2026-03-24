#version 330 core
out vec4 fragColor;
in vec3 ourColor; // input variable from vs (same name and type)
in vec2 texCoord;

uniform sampler2D tex0;
uniform float time;

uniform float offset;  
void main()
{
	vec4 baseColor = texture(tex0, texCoord);
	float moveAmmount = baseColor.b*time*.2;
	vec2 shiftCoord = vec2(texCoord.x, texCoord.y+moveAmmount);
	fragColor = texture(tex0, shiftCoord);
    fragColor.a *= step(time / 5, fragColor.b);
}
