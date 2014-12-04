//
//  Texture.h
//  libpngMem
//
//  Created by Fakhir Shaheen on 02/12/2014.
//  Copyright (c) 2014 Fakhir Shaheen. All rights reserved.
//

#ifndef __libpngMem__Texture__
#define __libpngMem__Texture__

#include <GLES2/gl2.h>
#include <png.h>

#include <string>
#include <istream>
#include <fstream>
#include <sstream>

GLuint LoadFromStream(std::istream & pngDataStream);

#endif /* defined(__libpngMem__Texture__) */
