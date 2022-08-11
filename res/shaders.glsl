//vertex shader
const char* vertexSource = 
R"(
    #version 330 core

    in vec2 position;
    in vec3 color;
    out vec3 _color;

    void main()
    {
        _color = color;
        gl_Position = vec4(position, 0.0, 1.0);
    }
)";

//fragment shader
const char* fragmentSource =
R"(
    #version 330 core

    in vec3 _color;
    out vec4 outColor;

    void main()
    {
        outColor = vec4(_color, 1.0);
    }
)";