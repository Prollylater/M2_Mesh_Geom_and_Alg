#version 420
// Input variables from the vertex shader
in vec3 frag_normal;
in vec2 frag_texcoor;
//in vec3 frag_pos;  

//Uniform modifier
uniform int DisplayMode;  


// Color uniform
uniform vec3 light_dir = normalize(vec3(-0.5, -0.5, -1.0));
uniform vec3 light_col = vec3(1.0, 1.0, 1.0);
uniform vec3 object_col = vec3(0.1, 0.5, 0.3); 

// Texture uniform
uniform sampler2D mesh_color;

// Output color
out vec4 fragment_color;

void main()
{
    //vec3 ambient = 0.5 * light_col;

    float cos_res = max(dot(normalize(frag_normal), light_col), 0.0);
    vec3 diffuse = cos_res * light_col;
    vec3 lighting_col =diffuse;

    // Sample the texture color
    vec3 tex_color = texture(mesh_color, frag_texcoor).rgb;
    
    // Combine texture color with object color and lighting
    vec3 light_color = lighting_col * object_col; //
    vec3 color =  object_col; //lighting_col *

    vec3 final_color[4] = {color,color,vec3(abs(frag_normal)),tex_color*color};
    fragment_color = vec4(final_color[DisplayMode], 1.0);
    //fragment_color = vec4(vec3(0.5), 1.0);

}
