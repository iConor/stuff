
static float vertices[] =
{
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     0.0f,  0.5f, 0.0f, 0.5f, 1.0f,
};


static int indices[] =
{
    0, 1, 2
};


int main()

//  Shader
    char* vertex_shader_source = sdl_read_entire_file("shader.vert");
    char* fragment_shader_source = sdl_read_entire_file("shader.frag");
    GLuint shader_program = opengl_create_shader_program(vertex_shader_source, fragment_shader_source);

//  Buffer Objects
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

//  Buffer Layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

//  Texture Object
    GLuint texture_handle;
    glGenTextures(1, &texture_handle);
    glBindTexture(GL_TEXTURE_2D, texture_handle);

//  Texture Sampling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_LINEAR_MIPMAP_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//  Texture Loading
    texture image;
    load_texture(&image, "wall.jpg");

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    free_texture(&image);

//  Texture Slot in Shader
    glUseProgram(shader_program);
    glUniform1i(glGetUniformLocation(shader_program, "tex_sampler"), 0);

    while()

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_handle);

        glUseProgram(shader_program);
        GLuint model_uniform = glGetUniformLocation(shader_program, "model");
        glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.e);
        GLuint view_uniform = glGetUniformLocation(shader_program, "view");
        glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view.e);
        GLuint projection_uniform = glGetUniformLocation(shader_program, "projection");
        glUniformMatrix4fv(projection_uniform, 1, GL_FALSE, projection.e);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
