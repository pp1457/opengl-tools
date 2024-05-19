#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader {
    private:
        unsigned int ID;
    public:
        Shader(const char *vspath, const char *fspath);
        unsigned int getID();
        void use();
        void bye();
        void setBool(const std::string &name, bool val) const;
        void setInt(const std::string &name, int val) const;
        void setFloat(const std::string &name, float val) const;
};

#endif
