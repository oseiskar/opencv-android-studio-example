# OpenCV example for Android Studio

OpenCV mixed-processing example modified to run in Android Studio.
The folder `opencv-sdk/build` is assumed to contain an OpenCV Android SDK build created with

    # git clone opencv to the folder opencv and checkout 4.0.1
    cd opencv/platforms/android

    export ANDROID_HOME=~/Android/Sdk
    export ANDROID_NDK=~/Android/Sdk/ndk-bundle
    export ANDROID_SDK=~Android/Sdk

    ./build_sdk.py /path/to/opencv-sdk/build

On Debian Stretch, these packages needed to be installed with apt-get to succeed in this

 * ninja
 * ccache
 * openjdk-8-jdk