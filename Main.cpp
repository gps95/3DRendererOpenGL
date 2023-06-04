#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef GLFWwindow* GLFWwindowPtr;

int main()
{
  //initialize
  if(!glfwInit())
  {
    std::cout<<"Error while initializing glfw\n";
    return 1;
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
  
  //create window
  int width=800,height=800;
  GLFWwindowPtr window=glfwCreateWindow(width,height,"My Window",NULL,NULL);
  if(!window)
  {
    std::cout<<"Error while creating window\n";
    return 1;
  }
  glfwMakeContextCurrent(window);

  //use glad to load opengl configs
  gladLoadGL();
  //set viewport for opengl
  glViewport(0,0,width,height);
  //specify background color,alpha=transparency
  glClearColor(0.07f,0.13f,0.17f,1);
  //clear back buffer and assign the colorj to it
  glClear(GL_COLOR_BUFFER_BIT);
  //load back buffer data to front buffer for display
  glfwSwapBuffers(window);

  //keep program alive untill window closes
  while(!glfwWindowShouldClose(window))
  {
    //take care of glfw events while window is open
    glfwPollEvents();
  }

  //terminate
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}