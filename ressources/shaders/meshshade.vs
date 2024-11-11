#version 420

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texcoord;

//uniform mat4 modelMatrix;
//uniform mat4 viewMatrix;
//uniform mat4 projectionMatrix;
//uniform mat4 mvMatrix;    
uniform mat4 mvpMatrix;  

// Output variables to pass to the fragment shader
out vec3 frag_normal;
out vec2 frag_texcoor;
//out vec3 frag_pos;    // World position of the fragment

void main()
{
    gl_Position = mvpMatrix * vec4(position.xyz, 1.0);

    frag_normal =  normal;

    frag_texcoor = texcoord.xy;

    //For light, unused at present
    //frag_pos = vec3(modelMatrix * vec4(position, 1.0));
}
