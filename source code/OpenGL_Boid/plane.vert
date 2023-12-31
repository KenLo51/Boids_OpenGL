# version 460 core

layout(location = 0) in vec3 in_position;
layout(location = 3) in vec2 in_texcoord;

out VertexData{
  vec2 TexCoord;
  vec3 Position;
} outData;

void main(){
	gl_Position = vec4(in_position, 1.0);
	outData.Position = in_position;
	outData.TexCoord = vec2(in_texcoord.x, in_texcoord.y);
}