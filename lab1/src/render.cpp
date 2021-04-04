#include "render.hpp"
#include "io.hpp"

void setMat4(GLuint uniformLocation, 
        const mat4 &mat) {
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

void render(DrawObject &obj, 
        camera_t &cam, GLuint program) {
    mat4 projection, view, rotation;
    cameraGetPerspective(cam, projection);
    cameraLookAt(cam, view);

    glUniformMatrix4fv(obj.projection_matrix, 1, GL_FALSE, 
        &projection[0][0]); 

    glUniformMatrix4fv(obj.view_matrix, 1, GL_FALSE, 
        &view[0][0]); 

    buildRotMatrix(rotation, cam.currentQuat);

    glEnable(GL_DEPTH);

    glUseProgram(program);

    glBindVertexArray(obj.vbo);

    glDrawElements(GL_TRIANGLES, obj.num, GL_UNSIGNED_INT, (void *) 0);
}
