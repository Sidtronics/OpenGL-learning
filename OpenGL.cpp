#include <string>
#define WAIT std::cin.get()

#include<iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<futils.h>

void CompileShader(unsigned int* shader, const char* shaderSource, unsigned int shaderType){ 
    *shader = glCreateShader(shaderType);
    glShaderSource(*shader, 1, &shaderSource, NULL);
    glCompileShader(*shader);

    //Error Debugging
    int status;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);
    
    if(status != GL_TRUE){
    char buffer[1024];
    glGetShaderInfoLog(*shader, 1024, NULL , buffer);
    std::cout << (shaderType == GL_VERTEX_SHADER ? "\nVertex" : "\nFragment") << " Shader Compilation Error:" << std::endl;
    std::cout << buffer << std::endl;
    }
};

int main(){

    std::cout << "GLFW: " << glfwGetVersionString() << std::endl;
    std::cout << "GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

    //Initializing GLWF
    if(!glfwInit()){
        const char* err;
        glfwGetError(&err); 
        std::cout << "Error: " << err << std::endl;
        return -1;
    }

    //Window Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    //Window Creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL-Arch",NULL,NULL);
    if(window == NULL){
        const char* err;
        glfwGetError(&err); 
        std::cout << "Error: " << err << std::endl;
        return -1; 
    }

    //Make context current 
    glfwMakeContextCurrent(window);

    //GLEW Initialisation
    glewExperimental = GL_TRUE;
    unsigned int err = glewInit();
    if(err != GLEW_OK){
        std::cout << "Error: " << glewGetErrorString(err) << std::endl;
        return -1;
    }    

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;


    //Buffers
    float positions[] = 
    {//   X      Y      R     G     B
        -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 1.0f, 1.0f, 0.5f
        
    };

    unsigned int elements[] = {
        0, 1, 3, 3, 2, 1
    };

    //Generating Vertex Array Object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    //Generating Vertex Buffer Object
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), (void*)&positions, GL_STATIC_DRAW);

    //Generating Element Buffer Object
    unsigned int ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    //Get Shader Source
    Fstrm shaders("res/shaders");
    std::string vertexSource = shaders.readBlock("VertexShader");
    std::string fragmentSource = shaders.readBlock("FragmentShader");

    //Create & Complie Shader
    unsigned int vertexShader;
    unsigned int fragmentShader;
    CompileShader(&vertexShader, vertexSource.c_str(), GL_VERTEX_SHADER);
    CompileShader(&fragmentShader, fragmentSource.c_str(), GL_FRAGMENT_SHADER);

    //Create & Link Shader Program
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    //Configure Vertex Buffer layout
    unsigned int posAttrib = glGetAttribLocation(shaderProgram, "position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
    glEnableVertexAttribArray(posAttrib);

    unsigned int colAttrib = glGetAttribLocation(shaderProgram, "color");
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
    glEnableVertexAttribArray(colAttrib);

    //unsigned int unicolor = glGetUniformLocation(shaderProgram, "triangleColor");
    //glUniform3f(unicolor, 0.0f, 1.0f, 0.0f);

    //Rendering loop
    while(!glfwWindowShouldClose(window))
    {
        //Render
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        //Handle Events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    //WAIT;  
}
