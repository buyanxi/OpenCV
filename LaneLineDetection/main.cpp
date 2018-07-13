#include <iostream>
#include<highgui.hpp>
#include<imgproc.hpp>

using namespace std;
using namespace cv;


const int ROIImageHeight = 310;

int main()
{
    char chVideoPath[256] = "Resource/Video/CAM62535114.avi";
    VideoCapture cInputVideo;
    cInputVideo.open(chVideoPath);

    if (!cInputVideo.isOpened()) {
        printf("Open video failed!\n");
        return 0;
    }

    Mat sInputSrcImage;
    Mat sROIImage;

    while (1) {
        if (!cInputVideo.read(sInputSrcImage)) {
            printf("Open video failed!\n");
            break;
        }
        imshow("Src Image", sInputSrcImage);

        sROIImage = sInputSrcImage(Rect(0, sInputSrcImage.rows - ROIImageHeight, sInputSrcImage.cols, ROIImageHeight));
        // Rect(left_top_point_X, left_top_point_Y, rectangle_width(cols), rectangle_height(rows));
        imshow("ROI Image", sROIImage);

        char chChar = waitKey(1);
        if (chChar == 27) {
            break;
        }
    }

    return 0;
}
