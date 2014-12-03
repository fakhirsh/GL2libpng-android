GL2libpng-android
=================

This code first loads raw png stream from the apk asset folder using JNI asset manager. Then it passes that stream to libPNG to extract bitmap data. Finally it generates openGL textures and renders the picture on the screen.
