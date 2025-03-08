#include "opengl_program.h"


#include "opengl_shader.h"


namespace render
{
    opengl_program::opengl_program(const program_desc& desc)
    {
        id = glCreateProgram();

        auto vs = static_cast<opengl_shader*>(desc.vertex);
        glAttachShader(id, vs->get_id());

        auto fs = static_cast<opengl_shader*>(desc.fragment);
        glAttachShader(id, fs->get_id());

        glLinkProgram(id);
    }


    opengl_program::~opengl_program()
    {
        glDeleteProgram(id);
    }


    void opengl_program::bind()
    {
        glUseProgram(id);
    }


    void opengl_program::unbind()
    {
        glUseProgram(0);
    }


    void opengl_program::bind_uniform_block(const int block_binding, const char* block_name)
    {
        GLuint block_index = glGetUniformBlockIndex(id, block_name);
        glUniformBlockBinding(id, block_index, block_binding);
    }


    void opengl_program::bind_sampler(const int target, const char* name)
    {
        GLint sampler_uniform = glGetUniformLocation(id, "texture_sampler");
        glUniform1i(sampler_uniform, 0);
    }


    void opengl_program::bind_vs_const_block(buffer* vs_cb)
    {
    }


    void opengl_program::bind_fs_const_block(buffer* fs_cb)
    {
    }


    void opengl_program::bind_texture(texture* rt)
    {
    }


    void opengl_program::bind_sampler(sampler* rs)
    {
    }


    void opengl_program::bind_layout(layout* lo)
    {
        // ID3D11InputLayout* input_layout;
        // m_pd3dDevice->CreateInputLayout(ied, 3, vertex_shader_blob->GetBufferPointer(), vertex_shader_blob->GetBufferSize(), &input_layout);

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
}
