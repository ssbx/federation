#include "federation.h"

#include "fed_gl.h"
#include "fed_log.h"




// local
#include <stdlib.h>

void FGlInit0()
{

    FDebugMsg("FGl_prepare");

    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    fed_window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
    if (!fed_window)
    {
        FErrorMsg("fed_gl_init Failed to open GLFW window.\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(fed_window);


    if (glewInit() != GLEW_OK)
    {
        FErrorMsg("fed_gl_init Failed to initialize GLEW\n");
        FGlCleanup();
        exit(1);
    }

    glfwSwapInterval(1);

}

void FGlInit()
{

    FDebugMsg("FGl_prepare");

    if (!glfwInit()) {
        exit(1);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    fed_window = glfwCreateWindow(1024, 768, "Simple example", NULL, NULL);
    if (!fed_window)
    {
        FErrorMsg("fed_gl_init Failed to open GLFW window.\n");
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(fed_window);


    if (glewInit() != GLEW_OK)
    {
        FErrorMsg("fed_gl_init Failed to initialize GLEW\n");
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(1);

}


void FGlCleanup()
{

    FDebugMsg("FGl_cleanup");
    glfwDestroyWindow(fed_window);
    glfwTerminate();

}
