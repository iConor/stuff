#include "opengl_shader_program.h"


#include "opengl_shader.h"


namespace renderer
{
    opengl_shader_program::opengl_shader_program(shader_program_desc desc)
    {
        create(desc);
    }


    opengl_shader_program::~opengl_shader_program()
    {
    }


    void opengl_shader_program::create(shader_program_desc desc)
    {
        id = glCreateProgram();

        auto vs = static_cast<opengl_shader*>(desc.vertex);
        glAttachShader(id, vs->get_id());

        auto fs = static_cast<opengl_shader*>(desc.fragment);
        glAttachShader(id, fs->get_id());

        glLinkProgram(id);
    }


    void opengl_shader_program::destroy()
    {

    }


    void opengl_shader_program::bind()
    {
        glUseProgram(id);
    }

    // TODO: Verify shader link status (example pasted in from C renderer)
    // void opengl_shader_program::check()
    // {
    //     GLuint handle = id;
    //     const char* label = "a name to identify this shader_program when printing errors";
    //
    //     GLint status = 0;
    //     glGetProgramiv(handle, GL_LINK_STATUS, &status);
    //     if((GLboolean)status != GL_TRUE)
    //     {
    //         fprintf(stderr, "ERROR: (check_program) %s", label);
    //     }
    //     else
    //     {
    //         fprintf(stderr, "INFO: (check_program) %s", label);
    //     }
    //
    //     GLint log_length = 0;
    //     glGetProgramiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    //     if(log_length > 0)
    //     {
    //         char* buffer = new char[log_length];
    //         glGetProgramInfoLog(handle, log_length, NULL, (GLchar*)buffer);
    //         fprintf(stderr, "%s", buffer);
    //         delete buffer;
    //     }
    //
    //     fprintf(stderr, "\n");
    //
    //     return (GLboolean)status == GL_TRUE;
    // }


    GLuint opengl_shader_program::get_id()
    {
        return id;
    }


    void opengl_shader_program::bind_uniform_block(const int block_binding, const char* block_name)
    {
        GLuint block_index = glGetUniformBlockIndex(id, block_name);
        glUniformBlockBinding(id, block_index, block_binding);
    }


    void opengl_shader_program::bind_sampler(const int target, const char* name)
    {
        GLint sampler_uniform = glGetUniformLocation(id, "texture_sampler");
        glUniform1i(sampler_uniform, 0);
    }
}
