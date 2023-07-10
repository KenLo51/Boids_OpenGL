# version 460 core

layout(location = 0) in vec3 in_position;

uniform vec3 pos;

out VertexData{
  vec3 Position;
} outData;

void main(){
	vec3 pos_o = pos;
	pos_o.z = clamp(pos_o.z, 0.0f, 1.0f);
	gl_Position = vec4(pos_o, 1.0);
	outData.Position = pos_o;

}