#include "Window.h"
#include "OBJObject.h"
#include "Skybox.h"
#include "Geometry.h"
#include "Transform.h"
#include "Robot.h"
#include "Curve.h"

const char * window_title = "Assignment 3";
Skybox * box;
Transform * robots;
Curve * curve;

GLint shaderProgram;
GLint skyboxShader;
bool scaleSet = false;
glm::vec3 offsets[25];
GLuint quadVAO;
int curveIndex = 0;

// On some systems you need to change this to the absolute path
#define VERTEX_SHADER_PATH "/Users/Meeta/Desktop/CSE 167/HW3/HW3/shader.vert"
#define FRAGMENT_SHADER_PATH "/Users/Meeta/Desktop/CSE 167/HW3/HW3/shader.frag"
#define BOX_VERTEX_SHADER_PATH "/Users/Meeta/Desktop/CSE 167/HW3/HW3/boxShader.vert"
#define BOX_FRAGMENT_SHADER_PATH "/Users/Meeta/Desktop/CSE 167/HW3/HW3/boxShader.frag"

// Default camera parameters
glm::vec3 cam_pos(0.0f, 0.0f, -20.0f);		// e  | Position of camera
glm::vec3 cam_look_at(0.0f, 0.0f, 0.0f);	// d  | This is where the camera looks at
glm::vec3 cam_up(0.0f, 1.0f, 0.0f);			// up | What orientation "up" is

int Window::width;
int Window::height;

glm::mat4 Window::P;
glm::mat4 Window::V;

void Window::initialize_objects()
{
    // Load the shader program. Make sure you have the correct filepath up top
    shaderProgram = LoadShaders(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH);
    skyboxShader = LoadShaders(BOX_VERTEX_SHADER_PATH, BOX_FRAGMENT_SHADER_PATH);
    
    box = new Skybox(skyboxShader, width, height);
    
    robots = new Transform();
    glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 25; i++)
    {
        if (i == 0) {//do nothing
        }
            
        else if (i == 5 || i == 10 || i == 15 || i == 20)
        {
            offset.y += 60.0f;
            offset.x = 0.0f;
        }
        
        else
        {
            offset.x += 70.0f;
        }

        offsets[i] = offset;
        robots->addChild(new Robot(shaderProgram, offset)); //, offset));
    }
    
    curve = new Curve();
}

// Treat this as a destructor function. Delete dynamically allocated memory here.
void Window::clean_up()
{
	glDeleteProgram(shaderProgram);
    glDeleteProgram(skyboxShader);
    delete(robots);
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ // Because Apple hates comforming to standards
	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		fprintf(stderr, "Either GLFW is not installed or your graphics card does not support modern OpenGL.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);
	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height); // In case your Mac has a retina display
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);

	if (height > 0)
	{
		P = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 2000.0f);
		V = glm::lookAt(cam_pos, cam_look_at, cam_up);
	}
}

void Window::idle_callback()
{
    robots->update();
    
    glm::vec3 currPos;
    glm::vec3 newPos;
    if (curveIndex == 0)
        currPos = curve->points[0];
    else
        currPos = curve->points[curveIndex - 1];
    
    newPos = curve->points[curveIndex];
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), newPos - currPos);
    robots->draw(translate);
    
    curveIndex++;
    if (curveIndex >= curve->points.size())
        curveIndex = 0;
    
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Use the shader of programID
	glUseProgram(skyboxShader);
    box->draw();
    
    glUseProgram(shaderProgram);
    /*glGenVertexArrays(1, &quadVAO);
    for (int i = 0; i < 25; i++)
    {
        std::stringstream ss;
        std::string index;
        ss << i;
        index = ss.str();
        glUniform3f(glGetUniformLocation(shaderProgram, ("offsets[" + index + "]").c_str()), offsets[i].x, offsets[i].y, offsets[i].z);
    }
    
    glBindVertexArray(quadVAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 25);*/
    
    glm::mat4 c = glm::mat4(1.0f);
    if (!scaleSet)
    {
        glm::mat4 translation = glm::translate(glm::mat4(1.0f), curve->points[0]);
        //robots->translate(t);
        robots->draw(translation);
        scaleSet = true;
    }
    
    robots->draw(c);
    
    curve->draw(shaderProgram);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

bool rDown = false;
bool lDown = false;

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
        
        /*if (key == GLFW_KEY_F1) //Switch to dragon
        {
            bunnyMode = false;
            bearMode = false;
            dragonMode = true;
        }
        
        if (key == GLFW_KEY_F2) //Switch to bunny
        {
            dragonMode = false;
            bearMode = false;
            bunnyMode = true;
        }
        
        if (key == GLFW_KEY_F3) //Switch to bear
        {
            bunnyMode = false;
            dragonMode = false;
            bearMode = true;
        }
        
        if (key == GLFW_KEY_S) //Scale
        {
            char s = 's';
            if (mods == GLFW_MOD_SHIFT)
                s = 'S';
            if (bunnyMode)
                bunny->scale(s);
            if (dragonMode)
                dragon->scale(s);
            if (bearMode)
                bear->scale(s);
        }
        */
    }
    
    // Check for control button
    if (key == GLFW_KEY_LEFT_CONTROL)
    {
        if (action == GLFW_PRESS)
            rDown = true;
        if (action == GLFW_RELEASE)
            rDown = false;
    }
}

double xPos1, xPos2;
double yPos1, yPos2;
void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            lDown = true;
            glfwGetCursorPos(window, &xPos1, &yPos1);
        }
        if (action == GLFW_RELEASE)
        {
            lDown = false;
        }
    }
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    glm::vec4 cam (cam_pos, 1.0f);
    if (yoffset < 0)
    {
        glm::mat4 positiveZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 10.0f));
        cam = positiveZ * cam;
    }
    
    else if (yoffset > 0)
    {
        glm::mat4 negativeZ = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
        cam = negativeZ * cam;
    }
    
    cam_pos = glm::vec3(cam.x, cam.y, cam.z);
    V = glm::lookAt(cam_pos, cam_look_at, cam_up);
}

void Window::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    xPos2 = xpos;
    yPos2 = ypos;
    
    if (rDown)
    {
        /*xPos = xPos - (float)width / 2.0f;
        yPos = (float)height / 2.0f - yPos;
        xPos /= 24.0f;
        yPos /= 24.0f;*/
        
        /*if (dragonMode)
            dragon->translateXY(xPos, yPos);
        if (bunnyMode)
            bunny->translateXY(xPos, yPos);
        if (bearMode)
            bear->translateXY(xPos, yPos);*/
    }
    
    if (lDown)
    {
        glm::vec3 v1 = trackballCalculation(xPos1, yPos1);
        glm::vec3 v2 = trackballCalculation(xPos2, xPos2);
        glm::vec3 begin (v1.x, v1.y, v1.z);
        glm::vec3 end (v2.x, v2.y, v2.z);
        glm::vec3 axis = glm::cross(v2, v1);
        float angle = glm::dot(v1, v2) / (v1.length() * v2.length()); /// 180.0f * glm::pi<float>();
        angle = acos(angle);
        glm::vec4 cameraPos (cam_pos, 0);
        cameraPos = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * cameraPos;
        cam_pos = glm::vec3(cameraPos.x, cameraPos.y, cameraPos.z);
        V = glm::lookAt(cam_pos, cam_look_at, cam_up);
    }
}

glm::vec3 Window::trackballCalculation(double x, double y)
{
    glm::vec3 v;
    v.x = (2.0f * (float)x - width) / width;
    v.y = (height - 2.0f * (float)y) / height;
    v.z = 0.0f;
    float d = glm::length(v); //v.length();
    d = (d < 1.0f) ? d : 1.0f;
    v.z = sqrtf(1.001f - d*d);
    v = glm::normalize(v);
    return v;
}
