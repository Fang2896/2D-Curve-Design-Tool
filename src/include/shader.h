//
// Created by fangl on 2023/9/10.
//

#ifndef SHADER_H
#define SHADER_H

#include <QColor>
#include <QDebug>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>

class Shader {
   public:
    explicit Shader(QOpenGLWidget* parent);
    ~Shader() = default;

    void compile(const QString& vertexSource, const QString& fragmentSource);

    Shader& use() {
        shaderProgram->bind();
        return *this;
    }

    void release() { shaderProgram->release(); }

    void setFloat(const QString& name, const GLfloat& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setInteger(const QString& name, const GLint& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setVector2f(const QString& name, const GLfloat& x, const GLfloat& y) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, QVector2D(x, y));
    }

    void setVector2f(const QString& name, const QVector2D& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setVector3f(const QString& name, const GLfloat& x, const GLfloat& y,
                     const GLfloat& z) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, QVector3D(x, y, z));
    }

    void setVector3f(const QString& name, const QVector3D& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setVector4f(const QString& name, const GLfloat& x, const GLfloat& y,
                     const GLfloat& z, const GLfloat& w) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, QVector4D(x, y, z, w));
    }

    void setVector4f(const QString& name, const QVector4D& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setColor(const QString& name, const QColor& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setMatrix4f(const QString& name, const QMatrix4x4& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

    void setBool(const QString& name, const GLboolean& value) {
        int loc = shaderProgram->uniformLocation(name);
        shaderProgram->setUniformValue(loc, value);
    }

   private:
    QOpenGLShaderProgram* shaderProgram;
};

#endif  //SHADER_H
