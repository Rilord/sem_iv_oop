#include "shaders.hpp"

static const char *vs_src[] = 
{
    "#version 140\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 projectionMat;\n"
    "uniform mat4 viewMat;\n"
    "uniform mat4 modelMat;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = modelMat * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = viewMat * modelPos;\n"
    "    gl_Position   = projectionMat * viewPos;\n"
    "}\n"
};


static const char *fs_src[] = 
{
    "#version 140\n"
    "in vec3 vertCol;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4( vertCol, 1.0 );\n"
    "}\n"
};

err_t LoadShader(GLuint program) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Load shaders */


    GLint result = GL_FALSE;
    int logLen;

    /* Compile vertex shader */
    glShaderSource(vertShader, 1, vs_src, NULL);
    glCompileShader(vertShader);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(vertShader, logLen, NULL, &ErrorLog[0]);

        return SHADER_ERR;
    }

    glShaderSource(fragShader, 1, fs_src, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(fragShader, logLen, NULL, &ErrorLog[0]);


        return SHADER_ERR;
    }

    /* Linking program */

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(fragShader, logLen, NULL, &ErrorLog[0]);


        glDeleteShader(fragShader);
        glDeleteShader(vertShader);

        return SHADER_ERR;

    }

    return SUCCESS;
}

void setMat4(GLuint program, const char *name, const mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &mat[0][0]);
}

void CheckErrors(const char* desc) {
  GLenum e = glGetError();
  if (e != GL_NO_ERROR) {
    fprintf(stderr, "OpenGL error in \"%s\": %d (%d)\n", desc, e, e);
  }
}
