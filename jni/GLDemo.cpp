/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// OpenGL ES 2.0 code

#include "GLDemo.h"

#include "Texture.h"
#include "AssetLoader.h"

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <istream>
#include <sstream>



static const char gVertexShaderTexture[] =
"attribute vec4 vPosition;\n"
"attribute vec4 vUV;\n"
"varying vec2 v_texCoord;\n"
"void main() {\n"
"  gl_Position = vPosition;\n"
"  v_texCoord = vUV.st;\n"
"}\n";

static const char gFragmentShaderTexture[] =
"precision mediump float;\n"
"uniform sampler2D sampler2d;\n"
"varying vec2 v_texCoord;\n"
"void main() {\n"
"  gl_FragColor = texture2D(sampler2d, v_texCoord);\n"
"}\n";


static const char gVertexShader[] =
"attribute vec4 vPosition;\n"
"void main() {\n"
"  gl_Position = vPosition;\n"
"}\n";

static const char gFragmentShader[] =
"precision mediump float;\n"
"void main() {\n"
"  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
"}\n";



GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }
    
    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }
    
    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gvPositionHandle;
GLuint gvUVHandle;

bool setupGraphics(int w, int h, std::string bundlePath) {

    gProgram = createProgram(gVertexShaderTexture, gFragmentShaderTexture);
    if (!gProgram) {
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    gvUVHandle = glGetAttribLocation(gProgram, "vUV");
    
    glViewport(0, 0, w, h);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
  
    std::string fullTexturePath = "Candy_Person.png";
    
    std::vector<char> buffer;
    
    AssetLoader::GetAssetStream(fullTexturePath.c_str(), buffer);
    
    std::string pngDataString;
    
    for (int i = 0; i < buffer.size(); i++)
    {
        pngDataString += buffer[i];
    }
    
    std::istringstream pngDataStream( pngDataString );
    
    GLuint texture = LoadFromStream(pngDataStream);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    return true;
}

const GLfloat gSquareVertices[] = { -0.5f, -0.5f, 0.0f, 0.0f,
                                    0.5f, -0.5f, 1.0f, 0.0f,
                                    0.5f, 0.5f, 1.0f, 1.0f,
                                    -0.5f, -0.5f, 0.0f, 0.0f,
                                    0.5f, 0.5f, 1.0f, 1.0f,
                                    -0.5f, 0.5f, 0.0f, 1.0f };




void renderFrame() {

    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    glUseProgram(gProgram);
    
    int stride = 4*sizeof(GLfloat);
    
    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, stride, &gSquareVertices[0]);
    glVertexAttribPointer(gvUVHandle, 2, GL_FLOAT, GL_FALSE, stride, &gSquareVertices[2]);
    
    glEnableVertexAttribArray(gvPositionHandle);
    glEnableVertexAttribArray(gvUVHandle);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);

}
