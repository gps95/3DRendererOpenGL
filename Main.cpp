#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef GLFWwindow* GLFWwindowPtr;

//shaders
const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"  FragColor = vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\0";

int main()
{
  //-initialize
  if(!glfwInit())
  {
    std::cout<<"Error while initializing glfw\n";
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);//major opengl version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);//minor opengl version
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);//opengl profile
  
  //-array of 3 vertices for triangle
  GLfloat vertices[] = 
  {
    -0.5f,-0.5f*float(sqrt(3))/3,0.0f,//lower left vertex
    0.5f,-0.5f*float(sqrt(3))/3,0.0f,//lower right vertex
    0.0f,0.5f*float(sqrt(3))*2/3,0.0f//up vertex
  };


  //-create window
  int width=800,height=800;
  GLFWwindowPtr window=glfwCreateWindow(width,height,"My Window",NULL,NULL);
  if(!window)
  {
    std::cout<<"Error while creating window\n";
    return 1;
  }
  glfwMakeContextCurrent(window);

  //-use glad to load opengl configs
  gladLoadGL();

  //-set viewport for opengl
  glViewport(0,0,width,height);
  
  //-vertex shader
  //create reference shader value
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  //feed source code to created shader
  glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
  //compile shader into machine code
  glCompileShader(vertexShader);
  
  //-fragment shader
  //create reference shader value
  GLuint fragmentShader= glCreateShader(GL_FRAGMENT_SHADER);
  //feed source code to created shader
  glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);
  //compile shader into machine code
  glCompileShader(fragmentShader);

  //-attach shaders into shader program
  GLuint shaderProgram = glCreateProgram();
  //attach shaders to shaderProgram
  glAttachShader(shaderProgram,vertexShader);
  glAttachShader(shaderProgram,fragmentShader);
  //link shader program
  glLinkProgram(shaderProgram);
  //delete both shaders since they are already in the shader program
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  //-create buffer for CPU to GPU communication
  //vao is used to manage several vbos,IT MUST BE GENERATED BEFORE ANY VBO
  GLuint VAO;//vertex array object
  GLuint VBO;//vertex buffer object, can have more than one
  //generate vao
  glGenVertexArrays(1,&VAO);
  //generate vbo
  glGenBuffers(1,&VBO);
  //bind object:make a certain obj the current obj,functions will modify bound object
  //bind vao
  glBindVertexArray(VAO);
  //bind vbo
  glBindBuffer(GL_ARRAY_BUFFER,VBO);//bind vbo

  /*-store vertices into VBO
  //GL_STREAM:vertices will be modified once and used a few times
  //GL_STATIC:vertices will be modified once and used many times
  //GL_DYNAMIC:vertices will be modified multiple and used many times
  //__DRAW:vertices will be modified and be used to draw an image on screen
  //__READ:
  //__COPY:
  */
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
  //-configure vao
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);

  //bind vao and vbo to 0 just in case
  glBindBuffer(GL_ARRAY_BUFFER,0);
  glBindVertexArray(0);

  //-give window a background color
  //specify window background color,alpha=transparency
  glClearColor(0.07f,0.13f,0.17f,1.0f);
  //clear back buffer and assign the color to it
  glClear(GL_COLOR_BUFFER_BIT);
  //load back buffer data to front buffer for display
  glfwSwapBuffers(window);

  //-keep program alive untill window closes
  while(!glfwWindowShouldClose(window))
  {
    //-draw each frame
    //specify window background color,alpha=transparency
    glClearColor(0.07f,0.13f,0.17f,1.0f);
    //clear back buffer and assign the color to it
    glClear(GL_COLOR_BUFFER_BIT);
    //activate our shader program
    glUseProgram(shaderProgram);
    //bind vao so that opengl uses this vao
    glBindVertexArray(VAO);
    //drawing function
    glDrawArrays(GL_TRIANGLES,0,3);
    //swap buffers so that image gets updated each frame
    glfwSwapBuffers(window);

    //-take care of glfw events while window is open
    glfwPollEvents();
  }

  //-terminate objects
  glDeleteVertexArrays(1,&VAO);
  glDeleteBuffers(1,&VBO);
  glDeleteProgram(shaderProgram);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}