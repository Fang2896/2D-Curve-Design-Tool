//
// Created by fangl on 2023/6/7.
//

#include "Headers/Shader.h"

Shader::Shader(QOpenGLWidget *parent) {
    shaderProgram = new QOpenGLShaderProgram(parent);
}

void Shader::compile(const QString &vertexSource, const QString &fragmentSource) {
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    bool success = vertexShader.compileSourceFile(vertexSource);
    if(!success){
        qDebug() << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << Qt::endl;
        qDebug() << vertexShader.log() << Qt::endl;
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    success  = fragmentShader.compileSourceFile(fragmentSource);
    if(!success){
        qDebug() << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << Qt::endl;
        qDebug() << fragmentShader.log() << Qt::endl;
    }

    shaderProgram->addShader(&vertexShader);
    shaderProgram->addShader(&fragmentShader);
    success = shaderProgram->link();
    if(!success){
        qDebug() << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << Qt::endl;
        qDebug() << shaderProgram->log() << Qt::endl;
    } else {
        qDebug() << "Successfully Link" << Qt::endl;
    }
}
