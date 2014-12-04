package com.fakhir.GL2libpng;

import android.app.Activity;
import android.os.Bundle;
import android.content.res.AssetManager;

import android.util.Log;
import android.view.WindowManager;

import java.io.File;


public class GL2libpngActivity extends Activity
{
    public static AssetManager assetMgr;
    GL2View _view;
    
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        assetMgr = getResources().getAssets();
        
        _view = new GL2View(getApplication());
        setContentView(_view);
        
    }
    
    @Override protected void onPause() {
        super.onPause();
        _view.onPause();
    }
    
    @Override protected void onResume() {
        super.onResume();
        _view.onResume();
    }
    
}
