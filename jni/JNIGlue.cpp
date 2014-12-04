
#include <string>
#include <sstream>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

#include "GLDemo.h"
#include "AssetLoader.h"

#define  LOG_TAG    "JNIGlue"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)


void DisplayDebugHeader();


extern "C" 
{
    JNIEXPORT void JNICALL Java_com_fakhir_GL2libpng_JNIGlue_Init( JNIEnv* env, jobject thiz, jint width, jint height, jobject assetMgrJava);
    JNIEXPORT void JNICALL Java_com_fakhir_GL2libpng_JNIGlue_Step( JNIEnv* env, jobject thiz);
}

JNIEXPORT void JNICALL Java_com_fakhir_GL2libpng_JNIGlue_Init( JNIEnv* env, jobject thiz, jint width, jint height, jobject assetMgrJava)
{
    
    LOGI("Width %d: ", width);
    LOGI("Height %d: ", height);
    
    std::string bundlePath = "";
 
     DisplayDebugHeader();
    
    AssetLoader::assetManager = AAssetManager_fromJava(env, assetMgrJava);
    
    if(AssetLoader::assetManager == NULL)
    {
        LOGI("------------------Error loading asset manager-----------------");
        return;
    } 
    LOGI("------------------ Asset manager loaded-----------------");
    
    setupGraphics(width, height, bundlePath);
    
}


JNIEXPORT void JNICALL Java_com_fakhir_GL2libpng_JNIGlue_Step( JNIEnv* env, jobject thiz)
{
    renderFrame();
}



void DisplayDebugHeader()
{
    LOGI("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("............................................................");
    LOGI("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    
}