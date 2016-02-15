// Include standard headers
#include <stdio.h>
#include "federation.h"

#include <GL/glew.h>
#include <GL/glfw.h>


main(int argc, char* argv) {


  if ( !glfwInit() )
  {

    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;

  }


  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
  glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // Open a window and create its OpenGL context
  if ( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
  {

    fprintf( stderr, "Failed to open GLFW window.\n");
    glfwTerminate();
    return -1;

  }

  // Initialize GLEW
  if ( glewInit() != GLEW_OK ) {

    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;

  }


  glfwSetWindowTitle( "Federation" );

  // Ensure we can capture the escape key being pressed below
  glfwEnable( GLFW_STICKY_KEYS );

  // Dark blue background
  glClearColor(0.0f, 0.0f, 0.3f, 0.0f);

  do{
    // Draw nothing, see you in tutorial 2 !

    // Swap buffers
    glfwSwapBuffers();

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
      glfwGetWindowParam( GLFW_OPENED ) );

  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;

}
