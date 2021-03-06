#version 330 core
out vec4 color;
uniform vec3 lightPos;
uniform float lightPow;
uniform float Time;
uniform vec3 viewPos;
in vec3 Normal;
in vec3 FragPos;

void main(){
    mat3 rot = mat3(cos(radians(Time*30)),0.0f,sin(radians(Time*30)),0.0f,1.0f,0.0f,-sin(radians(Time*30)),0.0f,cos(radians(Time*30)));
    vec3 LightPos = rot*lightPos;
    float specularStrength = 0.5f;
    vec3 light_color = vec3(1.0f,1.0f,1.0f);
    vec3 color_obj = vec3(0.7f, 0.7f, 0.7f);
    float ambient_strenght = 0.2f;
    vec3 ambient = ambient_strenght*light_color;
    vec3 LightDir = LightPos - FragPos;
    vec3 Lightsize = LightPos - FragPos;
    LightDir = normalize(LightDir);
    float LightDis = sqrt(dot(Lightsize,Lightsize));
    float diff = max(dot(LightDir,Normal),0.0f);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-LightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    vec3 specular = specularStrength * spec * light_color;
    vec3 result = (ambient + diff*light_color + specular)*color_obj;
    color = vec4(result,1.0f);
}