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
    Mat sROIGrayImage;
    Mat sROIBinaryImage;
    Mat sROIEdgeImage;

    while (1) {
        if (!cInputVideo.read(sInputSrcImage)) {
            printf("Open video failed!\n");
            break;
        }
        imshow("Src Image", sInputSrcImage);

        sROIImage = sInputSrcImage(Rect(0, sInputSrcImage.rows - ROIImageHeight, sInputSrcImage.cols, ROIImageHeight));
        // Rect(left_top_point_X, left_top_point_Y, rectangle_width(cols), rectangle_height(rows));
        imshow("ROI Image", sROIImage);


        cvtColor(sROIImage, sROIGrayImage, CV_BGR2GRAY);
        imshow("ROI Gray Image", sROIGrayImage);

        threshold(sROIGrayImage, sROIBinaryImage, 120, 255.0, CV_THRESH_BINARY);
        //adaptiveThreshold(sROIGrayImage, sROIBinaryImage, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 17, 2);
        imshow("ROI Binary Image", sROIBinaryImage);

        Mat sKern = getStructuringElement(MORPH_RECT, Size(7, 7));
        erode(sROIBinaryImage, sROIBinaryImage, sKern);
        dilate(sROIBinaryImage, sROIBinaryImage, sKern);
        imshow("ROI Binary Image", sROIBinaryImage);

        Canny(sROIBinaryImage, sROIEdgeImage, 50, 120);
        imshow("ROI Edge Image", sROIEdgeImage);

        char chChar = waitKey(1);
        if (chChar == 27) {
            break;
        }
    }

    return 0;
}
