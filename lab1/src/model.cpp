#include "model.hpp"
#include "errors.hpp"

void setVertex(model_t &model, vec3 buf) {
    model.vertices[model.vert_num][0] = buf[0];
    model.vertices[model.vert_num][1] = buf[1];
    model.vertices[model.vert_num++][2] = buf[2];
}

void setFace(model_t &model, vec3i face) {
    model.indices[model.indices_num++] = face[0];
    model.indices[model.indices_num++] = face[1];
    model.indices[model.indices_num++] = face[2];
}

err_t loadVertexBuffer(DrawObject &obj, model_t &model, GLuint programID) {
    err_t error = SUCCESS;

    glGenBuffers(1, &obj.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);
    glBufferData(GL_ARRAY_BUFFER, 
            sizeof(&model.vertices), model.vertices, GL_STATIC_DRAW);


    obj.attrib_v_coord = glGetAttribLocation(programID, "inPos");

    if (obj.attrib_v_coord == -1) {
        error = SHADER_ERR;
        return error;
    }

    obj.projection_matrix = glGetUniformLocation(programID, "projMatrix");
    if (obj.projection_matrix == -1) {
        error = SHADER_ERR;
        return error;
    }
    obj.view_matrix = glGetUniformLocation(programID, "viewMatrix");
    if (obj.view_matrix == -1) {
        error = SHADER_ERR;
        return error;
    }
    obj.model_matrix = glGetUniformLocation(programID, "modelMatrix");
    if (obj.model_matrix == -1) {
        error = SHADER_ERR;
        return error;
    }

    glGenBuffers(1, &obj.elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.elementBuffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices_num * sizeof(int), &model.indices[0], GL_STATIC_DRAW);


    return error;
}

err_t DestroyData(model_t &model) {
    auto error = SUCCESS; 

    delete [] model.vertices;
    delete model.indices;

    return error;
}
