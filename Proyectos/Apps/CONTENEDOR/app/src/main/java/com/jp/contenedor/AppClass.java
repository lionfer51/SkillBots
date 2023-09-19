package com.jp.contenedor;
import android.app.Application;

import com.onesignal.Continue;
import com.onesignal.OneSignal;
import com.onesignal.debug.LogLevel;

public class AppClass extends Application {

    // Replace the below with your own ONESIGNAL_APP_ID
    private static final String ONESIGNAL_APP_ID = "41a6c95c-169f-4c55-8c76-51327e5aa424";

    @Override
    public void onCreate() {
        super.onCreate();

        // Verbose Logging set to help debug issues, remove before releasing your app.
        OneSignal.getDebug().setLogLevel(LogLevel.VERBOSE);

        // OneSignal Initialization
        OneSignal.initWithContext(this, ONESIGNAL_APP_ID);


    }
}