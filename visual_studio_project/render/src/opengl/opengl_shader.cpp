#include "opengl_shader.h"


namespace render
{
    opengl_shader::opengl_shader(const shader_desc& desc)
    {
        type = desc.type;
        id = glCreateShader(translate(type));

        glShaderSource(id, 1, &desc.source, nullptr);
        glCompileShader(id);
    }


    opengl_shader::~opengl_shader()
    {
        glDeleteShader(id);
    }


    GLuint opengl_shader::get_id()
    {
        return id;
    }


    GLenum opengl_shader::translate(shader_type st)
    {
        switch(st)
        {
            case shader_type::vertex:   return GL_VERTEX_SHADER;
            case shader_type::fragment: return GL_FRAGMENT_SHADER;
        }
        return 0;
    }


    // // TODO: Verify shader compile status (example pasted in from C renderer)
    // bool opengl_shader::check()
    // {
    //     GLuint handle = id;
    //     const char* label = "a name to identify this shader when printing errors";
    //
    //     GLint status = 0;
    //     glGetShaderiv(handle, GL_COMPILE_STATUS, &status);
    //     if((GLboolean)status != GL_TRUE)
    //     {
    //         fprintf(stderr, "ERROR: (check_shader) %s\n", label);
    //     }
    //     else
    //     {
    //         fprintf(stderr, "INFO: (check_shader) %s\n", label);
    //     }
    //
    //     GLint log_length = 0;
    //     glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &log_length);
    //     if(log_length > 0)
    //     {
    //         char* buffer = new char[log_length];
    //         glGetShaderInfoLog(handle, log_length, NULL, (GLchar*)buffer);
    //         fprintf(stderr, "%s", buffer);
    //         delete buffer;
    //     }
    //
    //     fprintf(stderr, "\n");
    //
    //     return (GLboolean)status == GL_TRUE;
    // }
}
