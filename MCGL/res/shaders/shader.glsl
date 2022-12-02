//#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
//layout (location = 1) in uint aTextureID;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
//out uint TextureID;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);
    TexCoord = aTexCoord;
}


//#shader fragment
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;
//in uint aTextureID;
//in vec3 TexCoord;
uniform sampler2D texture1;
uniform float transparency;

void main()
{
    // FragColor = mix(texture(texture1, vec2(TexCoord.x / 2, TexCoord.y)), texture(texture2, TexCoord), transparency);
    //float texWidth = 384.0f;
    //float texHeight = 320.0f;
    //
    //vec2 xy = vec2(TexCoord.x / texWidth, TexCoord.y / texHeight);
    //FragColor = texture(texture1, xy);

    FragColor = texelFetch(texture1, ivec2(TexCoord.x, TexCoord.y), 0);
    
    //FragColor = texture2D((fract(TexCoord.x + TexCoord.z) + TexCoord.w) / 16.0, TexCoord.y);
    //FragColor = vec4(TexCoord.xyz, 1);
}


