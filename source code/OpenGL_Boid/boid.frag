#version 460 core

in VertexData{
  vec3 Position;
} inData;

out vec4 FragColor;


void main()
{
    float g = (inData.Position.z + 1.0f) / 2.0f;
    g = clamp(g, 0.0f, 1.0f);
    FragColor = vec4(g, g, g, 1.0f);
    //FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
} 
