export module Shader;
import stringOp;
import "glad/glad.h";
import <string>;
import <fstream>;
import <sstream>;
import <cassert>;
import <vector>;
import <iostream>;
import <functional>;
import <filesystem>;
import <type_traits>;
import <map>;
import <memory>;
import "GLM/glm.hpp";

export class Shader
{
public:
    struct vertexAtrib
    {
        int location; //позиция атрибута
        int type; //тип атрибута
        int lenght; //количество единиц атрибута
        int sinkhr;
        int size();//размер единицы атрибута в байтах
        vertexAtrib(int loc, int t, int len, int s = GL_FALSE)
            :location(loc), type(t), lenght(len), sinkhr(s) {}
    };
protected:
    void useVAtribSettings();
    std::vector<vertexAtrib> atributes;
public:
    //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
    
    //\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
    unsigned int ID;
    
    std::filesystem::path vPath, fPath;

    Shader(const std::filesystem::path vertexPath,
        const std::filesystem::path fragmentPath);
    // Активация шейдера
    
    void use()
    {
        glUseProgram(ID);
        useVAtribSettings();
    }

    // установка значений uniform-переменных

    template<class TCon>
    void set(const std::string& name, TCon value)
    {
        if constexpr      (std::is_same<TCon, int>::value)
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        else if constexpr (std::is_same<TCon, float>::value)
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        else if constexpr (std::is_same<TCon, glm::vec2>::value)
            glUniform2f(glGetUniformLocation(ID, name.c_str()), 
                value.x, value.y);
        else if constexpr (std::is_same<TCon, glm::vec3>::value)
            glUniform3f(glGetUniformLocation(ID, name.c_str()), 
                value.x, value.y, value.z);
        else if constexpr (std::is_same<TCon, glm::vec4>::value)
            glUniform4f(glGetUniformLocation(ID, name.c_str()), 
                value.x, value.y, value.z, value.w);
    }
    void setVertexAtrib(std::vector<vertexAtrib>& vAtrib)
    {
        atributes = vAtrib;
    }
private:
    // Полезные функции для проверки ошибок компиляции/связывания шейдеров
    void checkCompileErrors(unsigned int shader, std::string type);
};
//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//
//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//
//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//
Shader::Shader(const std::filesystem::path vertexPath,
    const std::filesystem::path fragmentPath)
    :vPath(std::filesystem::path(vertexPath).filename()), 
    fPath(std::filesystem::path(fragmentPath).filename())
{

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Убеждаемся, что объекты ifstream могут выбросить исключение
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Открываем файлы
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // Считываем содержимое файловых буферов в потоки 
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // Закрываем файлы
        vShaderFile.close();
        fShaderFile.close();

        // Конвертируем данные из потока в строковые переменные
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure&)
    {
        throw std::string("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    //Компиляция
    unsigned int vertex, fragment;

    // Вершинный шейдер
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Фрагментный шейдер
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Шейдерная программа
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::useVAtribSettings()
{
    int step = 0;
    for (int i = 0; i < atributes.size(); i++)
        step += atributes[i].lenght * atributes[i].size();
    int offset = 0;
    for (int i = 0; i < atributes.size(); i++)
    {
        glVertexAttribPointer(atributes[i].location, atributes[i].lenght,
            atributes[i].type, atributes[i].sinkhr, step, (void*)(static_cast<size_t>(offset)));
        glEnableVertexAttribArray(atributes[i].location);
        offset += atributes[i].lenght * atributes[i].size();
    }
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != std::string("PROGRAM"))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw std::string("ERROR::SHADER_COMPILATION_ERROR of type: " 
                + type + "\n" + infoLog +
                "\n -- --------------------------------------------------- -- ");
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            throw std::string("ERROR::PROGRAM_LINKING_ERROR of type: " 
                + type + "\n" + infoLog +
                "\n -- --------------------------------------------------- -- ");
        }
    }
}

int Shader::vertexAtrib::size()//размер единицы атрибута в байтах
{
    switch (type)
    {
    case GL_FLOAT: return sizeof(float);
    case GL_INT: return sizeof(int);
    case GL_UNSIGNED_INT: return sizeof(int);
    case GL_SHORT: return sizeof(short);
    case GL_UNSIGNED_SHORT: return sizeof(short);
    case GL_BYTE: return 1;
    case GL_UNSIGNED_BYTE: return 1;
    default:
        assert(false);
        return -1;
    }
}