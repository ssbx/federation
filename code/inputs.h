#ifndef FINPUT_H
#define FINPUT_H

#include "sounds.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cglm.h>
#include <clog.h>
#include <stdio.h>


typedef struct {
    
    double x;     // x position
    double y;     // y position
    double last;  // last move
    float  speed; // mouse speed
    float  xAngle; // horizontal angle
    float  yAngle; // vertical angle
    
} FINPUTcursor;

static FINPUTcursor cursor;


static float horizontalAngle;
static float verticalAngle;
static float fieldOfView;
static double keyLastMove;
static CGLMvec3 position;
static CGLMvec3 direction;
static CGLMmat4 proj;
static CGLMmat4 view;
static CGLMmat4 model;
static CGLMvec3 up;

// from fGl.h
extern float       FED_screenRatio;
extern GLFWwindow* MAIN_WINDOW;
extern CGLMmat4    FED_mvp;

void print_debug_input()
{
    clogInfo("up is %f %f %f\n", up.x, up.y, up.z);
    clogInfo("cursor is %f %f \n", cursor.x, cursor.y);
}

void init_inputs(
    float mouseSpeed_v,
    float horizontalAngle_v,
    float verticalAngle_v,
    float fieldOfView_v,
    CGLMvec3 position_v,
    CGLMvec3 direction_v)
{

    horizontalAngle = horizontalAngle_v;
    verticalAngle   = verticalAngle_v;
    fieldOfView     = fieldOfView_v;
    position        = position_v;
    direction       = direction_v;
    cursor.speed    = mouseSpeed_v;
    cursor.last = glfwGetTime();
    glfwGetCursorPos(MAIN_WINDOW, &(cursor.x), &(cursor.y));
    //glfwGetCursorPos(FED_window, &cursorLastXPos, &cursorLastYPos);
   
    model = cglmMat4(1);
    up = (CGLMvec3) {0,1,0};
    
    proj  = cglmPerspective(fieldOfView, FED_screenRatio, 0.1, 100.0);
    view  = cglmLookAt(position, direction, up);
    
    FED_mvp = cglmMultMat4(cglmMultMat4(proj, view), model);
   
    print_debug_input();
}

void handle_real_time_key_inputs()
{

    if (glfwGetKey(MAIN_WINDOW, GLFW_KEY_W) == GLFW_PRESS)
    {
        position.z -= 1;
        view    = cglmLookAt(position, direction, up);
        FED_mvp = cglmMultMat4(cglmMultMat4(proj, view), model);
        return;
    }
    
    if (glfwGetKey(MAIN_WINDOW, GLFW_KEY_S) == GLFW_PRESS) {
        position.z += 1;
        view    = cglmLookAt(position, direction, up);
        FED_mvp = cglmMultMat4(cglmMultMat4(proj, view), model);
        return;
    }
}


void handle_keyboard_inputs_callback(
    GLFWwindow* window,
    int         key,
    int         scancode,
    int         action,
    int         mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    /*
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        glfwIconifyWindow(FED_window);
    }
    */
    

    
}

void handle_scroll_inputs_callback(
    GLFWwindow* window,
    double xoffset,
    double yoffset)
{
}

void handle_cursor_position_callback(
    GLFWwindow* window,
    double      xpos,  
    double      ypos)
{
    
    double now       = glfwGetTime();
    double deltaTime = now - cursor.last;
    clogInfo("Delta %f\n", deltaTime);
    
    clogInfo("pos %f %f \n", cursor.x, cursor.y);
    horizontalAngle += cursor.speed * (cursor.x - xpos);
    verticalAngle   += cursor.speed * (cursor.y - ypos);
    
    direction = (CGLMvec3) {
        cos(verticalAngle) * sin(horizontalAngle), 
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    };
    
    CGLMvec3 right = {
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    };
    
    //up = cglmCross(right, direction);
    
    
    proj = cglmPerspective(fieldOfView, FED_screenRatio, 0.1, 100.0);
    view = cglmLookAt(
        position,
        cglmAddVec3(position, direction),
        up
    );
    
    cursor.last = now;
    cursor.x = xpos;
    cursor.y = ypos;
    
    FED_mvp = cglmMultMat4(cglmMultMat4(proj, view), model);
    
    print_debug_input();
    
}


void handle_mouse_button_inputs_callback(
    GLFWwindow* window,
    int         button,
    int         action,
    int         mods)
{
    if (action == GLFW_PRESS) 
    {
        switch(button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                play_sound(FED_SOUND_GunShot);
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                play_sound(FED_SOUND_GunShot);
                if (fieldOfView == 45.0) {
                    fieldOfView = 360.0;
                    proj = cglmPerspective(fieldOfView, FED_screenRatio, 0.1, 100.0);
                    FED_mvp = cglmMultMat4(cglmMultMat4(proj, view), model);
                } else {
                    fieldOfView = 45.0;
                    proj = cglmPerspective(fieldOfView, FED_screenRatio, 0.1, 100.0);
                    FED_mvp = cglmMultMat4(cglmMultMat4(proj, view), model);
                }
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                play_sound(FED_SOUND_GunShot);
                break;
        }
    }
}

#endif


