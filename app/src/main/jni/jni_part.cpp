#include <jni.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <vector>

extern "C" {
JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_Tutorial2Activity_FindFeatures(JNIEnv*, jobject, jlong addrGray, jlong addrRgba);

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_Tutorial2Activity_FindFeatures(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
{
    auto& mGr  = *reinterpret_cast<cv::Mat*>(addrGray);
    auto& mRgb = *reinterpret_cast<cv::Mat*>(addrRgba);
    std::vector<cv::KeyPoint> v;

    cv::Ptr<cv::FeatureDetector> detector = cv::FastFeatureDetector::create(50);
    detector->detect(mGr, v);
    for (const auto &keyPoint : v)
    {
        cv::circle(mRgb, cv::Point2f(keyPoint.pt.x, keyPoint.pt.y), 10, cv::Scalar(255,0,0,255));
    }
}
}
