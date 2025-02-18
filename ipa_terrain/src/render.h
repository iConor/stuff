GLuint create_shader(GLenum shader_type, const char* shader_source)
{
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source, NULL);
    glCompileShader(shader);
    return shader;
}

GLuint create_program(const char* vertex_source, const char* fragment_source)
{
    GLuint program = glCreateProgram();

    // TODO:
    //      Instead of specifying locations inside the shader,
    //      they can be done like so:
    //      glBindAttribLocation(program, 0, "position");

    GLuint vertex_shader =  create_shader(GL_VERTEX_SHADER, vertex_source);
    GLuint fragment_shader =  create_shader(GL_FRAGMENT_SHADER, fragment_source);

    // TODO:
    //      Check the status of each shader, something like so:
    // GLint fragment_compiled;
    // glGetShaderiv(fshader, GL_COMPILE_STATUS, &fragment_compiled);
    // if (fragment_compiled != GL_TRUE)
    // {
    //     GLsizei log_length = 0;
    //     GLchar message[1024];
    //     glGetShaderInfoLog(fshader, 1024, &log_length, message);
    //     // Write the error to a log
    // }

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    // TODO:
    //      This flags the shaders to be freed. The will not be freed until they
    //      are no longer attached to anythihng (glDetatchShader
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}
