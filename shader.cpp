#include "shader.h"

Shader::Shader(const char *vsPath, const char *fsPath) {
    std::string vsCode, fsCode;
    std::ifstream vsFile, fsFile;
    std::stringstream vsStream, fsStream;

    vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vsFile.open(vsPath);
        fsFile.open(fsPath);

        vsStream << vsFile.rdbuf();
        fsStream << fsFile.rdbuf();

        vsFile.close();
        fsFile.close();

        vsCode = vsStream.str();
        fsCode = fsStream.str();
    } catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char * vsSource = vsCode.c_str();
    const char * fsSource = fsCode.c_str();

    int success; 
    char infoLog[512];

    unsigned int vsid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsid, 1, &vsSource, NULL);
    glCompileShader(vsid);
    glGetShaderiv(vsid, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vsid, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } 

    unsigned int fsid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsid, 1, &fsSource, NULL);
    glCompileShader(fsid);
    glGetShaderiv(fsid, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fsid, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::????::COMPILATION_FAILED\n" << infoLog << std::endl;
    } 

    ID = glCreateProgram();
    glAttachShader(ID, vsid);
    glAttachShader(ID, fsid);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vsid);
    glDeleteShader(fsid);
}

unsigned int Shader::getID() { return ID; }

void Shader::use() { glUseProgram(ID); }

void Shader::bye() { glDeleteProgram(ID); }

void Shader::setBool(const std::string &name, bool value) const {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 
