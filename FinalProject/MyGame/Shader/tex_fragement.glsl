#version 330 core

in vec3 outTexcoord; // �ؽ�ó ��ġ���о�ð�..
in vec3 outFragPos;
in vec3 outNormal;

out vec4 FragColor;

uniform sampler2D outSampler;

uniform vec3 cameraPos;

const float ambientLight = 0.5f;
const vec3 lightColor = vec3(1.f, 0.93f, 1.f);	// �������� uniform���� �ؾ��� ��

const vec3 lightPos = vec3(20.f, 15.f, 0.f);

void main()
{

	vec3 ambient = ambientLight * lightColor;

	vec3 vNormal = normalize(outNormal);
	vec3 lightDir = normalize(lightPos - outFragPos);		// ���� ���⺤��
	float diffuseLight = max(dot(vNormal, lightDir), 0.0);	// 0 ~ 1������ ��
	vec3 diffuse = diffuseLight * lightColor;
	
	int shininess = 64;
	vec3 cameraDir = normalize(cameraPos - outFragPos);
	vec3 reflectDir = reflect(-lightDir, vNormal);
	float specularLight = max(dot(cameraDir, reflectDir), 0.0);	// 0 ~ 1������ ��
	specularLight = pow(specularLight, shininess);
	vec3 specular = specularLight * lightColor;

	// x == r == s, y == g == t,
	vec4 outColor = texture(outSampler, outTexcoord.st);

	vec3 result = (ambient + diffuse + specular) * outColor.rgb;		// vec3 * vec3 = ���ҳ����� ��
	
	FragColor = vec4(result, 1.0);
}
