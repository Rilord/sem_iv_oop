#ifndef RENDER_H_
#define RENDER_H_

#define TINYOBJ_LOADER_C_IMPLEMENTATION

#define SUCCESS (0x00)

#define RENDER_FILE_READ_ERR (0x03)
#define RENDER_VERTEX_SHADER_COMPILATION_ERR (0x04)
#define RENDER_FRAGMENT_SHADER_COMPILATION_ERR (0x05)
#define RENDER_LINLKING_ERR (0x06)

#include "tinyobj_loader_c.h"
#include "camera.hpp"
#include "RenderLog.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>

typedef struct {
    GLuint vb;
    int num;
} DrawObject;

typedef struct {
    DrawObject model;
    void (*render) (DrawObject &obj, camera_t &cam, GLFWwindow &window);

} Renderer;

#ifdef __linux__
static const char * vs_src[] = 
{
    "#version 330\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 u_projectionMat44;\n"
    "uniform mat4 u_viewMat44;\n"
    "uniform mat4 u_modelMat44;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = u_modelMat44 * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = u_viewMat44 * modelPos;\n"
    "    gl_Position   = u_projectionMat44 * viewPos;\n"
    "}\n"
};

static const char * fs_src[] = 
{
    "#version 400\n"
    "in vec3 vertCol;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4( vertCol, 1.0 );\n"
    "}\n"
};

#endif /* linux */

#ifdef __APPLE__
static const char * vs_src[] = 
{
    "#version 150\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 u_projectionMat44;\n"
    "uniform mat4 u_viewMat44;\n"
    "uniform mat4 u_modelMat44;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = u_modelMat44 * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = u_viewMat44 * modelPos;\n"
    "    gl_Position   = u_projectionMat44 * viewPos;\n"
    "}\n"
};


static const char * fs_src[] = 
{
    "#version 150\n"
    "in vec3 vertCol;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4( vertCol, 1.0 );\n"
    "}\n"
};

#endif /* APPLE */


std::string readFile(const char *filePath);

int LoadShader(const char *vertex_path, const char *fragment_path);

int loadObj(const char *filePath);


void setupModel(DrawObject &obj);

void draw(DrawObject &obj, camera_t &cam, GLFWwindow &window);

int setMat4(const std::string &name, const mat4 &mat);


#endif /* RENDER_H_ */
