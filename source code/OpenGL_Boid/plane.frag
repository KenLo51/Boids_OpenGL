#version 460 core

in VertexData{
  vec2 TexCoord;
  vec3 Position;
} inData;

out vec4 FragColor;

uniform sampler2D image;


void main()
{
    FragColor = texture2D(image, inData.TexCoord);
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 
