//
//  Loader.h
//
//  Created by Fakhir Shaheen on 02/12/2014.
//  Copyright (c) 2014 Fakhir Shaheen. All rights reserved.
//

#ifndef __libpngMem__AssetLoader__
#define __libpngMem__AssetLoader__

#include <GLES2/gl2.h>


#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <vector>

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>


class AssetLoader
{
public:
    ~AssetLoader(){}
    
    static void GetAssetStream(std::string assetPath, std::vector<char> & buffer);
    
    static AAssetManager * assetManager;
    
private:
    AssetLoader(){}
    
};



#endif /* defined(__libpngMem__AssetLoader__) */
