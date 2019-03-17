# OpenCV example for Android Studio

OpenCV mixed-processing example modified to run in Android Studio.

This builds OpenCV from source and uses the generated AAR as a Gradle Java dependency.
The native code is linked to & included with CMake.

The folder `opencv-sdk/build` is assumed to contain an OpenCV Android SDK build created
with the included script `./build-opencv.sh`.

On Debian Stretch, these packages needed to be installed with apt-get to succeed in this

 * ninja
 * ccache
 * openjdk-8-jdk

Worked at the time of writing. Knowing the Android platform, not proabably very future proof.

### License

Original is from the [OpenCV tutorial mixed-processing-example](https://github.com/opencv/opencv/tree/2b35c1708b43e2f9e9173c8ee31808214f6ee3e6/samples/android/tutorial-2-mixedprocessing).
Like the original, the modifications by [`oseiskar`](https://github.com/oseiskar) are
licensed under a BSD 3-clause license.
See LICENSE for the full license text and Git commit history to see how that original code was modified.
