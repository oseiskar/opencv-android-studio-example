#include <jni.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/video.hpp>
#include <cmath>
#include <memory>
#include <vector>

namespace {
    struct Workspace {
        cv::Mat prevGrayFrame;

        cv::Ptr<cv::FastFeatureDetector> featureDetector;
        cv::Ptr<cv::DenseOpticalFlow> opticalFlow;
        cv::Mat flow, colorConv;

        std::vector<cv::KeyPoint> keyPoints;

        explicit Workspace(const cv::Mat &grayFrame) :
            prevGrayFrame(grayFrame.clone()),
            featureDetector(cv::FastFeatureDetector::create(50)),
            opticalFlow(cv::DISOpticalFlow::create(cv::DISOpticalFlow::PRESET_ULTRAFAST)),
            colorConv(1,1,CV_8UC3)
        {}
    };

    std::unique_ptr<Workspace> work;

    void ensureWorkspace(const cv::Mat &mGr) {
        if (!work) work = std::unique_ptr<Workspace>(new Workspace(mGr));
    }
}

extern "C" {
JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_Tutorial2Activity_FindFeatures(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
{
    auto& mGr  = *reinterpret_cast<cv::Mat*>(addrGray);
    auto& mRgb = *reinterpret_cast<cv::Mat*>(addrRgba);

    ensureWorkspace(mGr);

    work->keyPoints.clear();
    work->featureDetector->detect(mGr, work->keyPoints);
    for (const auto &keyPoint : work->keyPoints)
    {
        cv::circle(mRgb, cv::Point2f(keyPoint.pt.x, keyPoint.pt.y), 10, cv::Scalar(255,0,0,255));
    }
}

JNIEXPORT void JNICALL Java_org_opencv_samples_tutorial2_Tutorial2Activity_FindOpticalFlow(JNIEnv*, jobject, jlong addrGray, jlong addrRgba)
{
    auto& mGr  = *reinterpret_cast<cv::Mat*>(addrGray);
    auto& mRgb = *reinterpret_cast<cv::Mat*>(addrRgba);

    ensureWorkspace(mGr);

    work->opticalFlow->calc(work->prevGrayFrame, mGr, work->flow);

    constexpr int VISU_BLOCK_SZ = 20;
    constexpr float SCALE = 0.5;

    for (int yb = VISU_BLOCK_SZ/2; yb < mRgb.rows; yb += VISU_BLOCK_SZ) {
        for (int xb = VISU_BLOCK_SZ/2; xb < mRgb.cols; xb += VISU_BLOCK_SZ) {
            const auto flow = work->flow.at<cv::Point2f>(yb, xb);
            cv::Point2f p(xb, yb);
            const float l = std::sqrt(flow.dot(flow));
            work->colorConv = cv::Scalar(
                    (std::atan2(flow.y, flow.x)/M_PI*0.5+0.5)*180, // hue
                    std::min(l/10.0, 1.0)*255, // saturation
                    std::min(l/30.0, 1.0)*255); // brightness;
            cv::cvtColor(work->colorConv, work->colorConv, cv::COLOR_HSV2BGR);
            cv::line(mRgb, p, p + flow*SCALE, work->colorConv.at<cv::Vec3b>(0, 0));
        }
    }

    mGr.copyTo(work->prevGrayFrame);
}
}
