#!/bin/bash

export ANDROID_HOME=~/Android/Sdk
export ANDROID_NDK=~/Android/Sdk/ndk-bundle
export ANDROID_SDK=~/Android/Sdk

cd opencv/platforms/android
./build_sdk.py ../../../opencv-sdk/build