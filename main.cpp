#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "rgbd/camera/DS325.h"

using namespace rgbd;
using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {

    std::shared_ptr<DepthCamera> camera(new DS325(0, FRAME_FORMAT_WXGA_H));
    camera->start();

    cv::Mat depth = cv::Mat::zeros(camera->depthSize(), CV_16U);
    cv::Mat amplitude = cv::Mat::zeros(camera->depthSize(), CV_16U);
    cv::Mat color = cv::Mat::zeros(camera->colorSize(), CV_8UC3);

//    cv::namedWindow("Depth", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
//    cv::namedWindow("Amplitude", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
//    cv::namedWindow("Color", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);

    char key;
    ColoredPointCloud::Ptr coloredPC(new ColoredPointCloud(
                camera->depthSize().width, camera->depthSize().height));
    cv::Mat projectColor(480, 640, CV_8UC3);
    cv::Mat projectDepth(480, 640, CV_16UC1);
    while (key != 'q') {
//        camera->captureDepth(depth);
//        camera->captureAmplitude(amplitude);
//        camera->captureColor(color);
        camera->captureColoredPointCloud(coloredPC);        
        for (int i = 0; i < coloredPC->points.size(); ++i) {
            float zc = coloredPC->points.at(i).z;
            if(zc > 1.0f) continue;
            float xc = coloredPC->points.at(i).x/zc * 319.f + 159.f;
            float yc = 1.3333f * coloredPC->points.at(i).y/zc * 239.f + 119.f;
//            xc = xc > 319.f? 319.f : xc;
//            yc = yc > 239.f? 239.f : yc;
            xc = roundf(xc);
            yc = roundf(yc);
            unsigned int r = coloredPC->points.at(i).r;
            unsigned int g = coloredPC->points.at(i).g;
            unsigned int b = coloredPC->points.at(i).b;
            projectColor.at<Vec3b>(yc, xc).val[0] = b;
            projectColor.at<Vec3b>(yc, xc).val[1] = g;
            projectColor.at<Vec3b>(yc, xc).val[2] = r;
            projectDepth.at<ushort>(yc, xc) = zc * 1000;
        }
        flip(projectColor, projectColor, -1);
        flip(projectDepth, projectDepth, -1);
//        cv::Mat d, a;
//        depth.convertTo(d, CV_8U, 255.0 / 1000.0);
//        flip(d, d, 1);
//        amplitude.convertTo(a, CV_8U, 255.0 / 1000.0);
//        cv::imshow("Depth", d);
        cv::imshow("Projected Depth", projectDepth);
        cv::imshow("UV mapping", projectColor);
        projectColor.setTo(0);
        projectDepth.setTo(0);
//        cv::imshow("Amplitude", a);
//        cv::imshow("Color", color);
        key = cv::waitKey(30);
    }    

    return 0;
}
