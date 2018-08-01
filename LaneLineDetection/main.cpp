#include <iostream>
#include<highgui.hpp>
#include<imgproc.hpp>

using namespace std;
using namespace cv;


const int ROIImageHeight = 210;

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
    Mat sHoughDestImage;

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

        threshold(sROIGrayImage, sROIBinaryImage, 140, 255.0, CV_THRESH_BINARY);
        //adaptiveThreshold(sROIGrayImage, sROIBinaryImage, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 17, 2);
        imshow("ROI Binary Image", sROIBinaryImage);

        Mat sKern = getStructuringElement(MORPH_RECT, Size(7, 7));
        erode(sROIBinaryImage, sROIBinaryImage, sKern);
        dilate(sROIBinaryImage, sROIBinaryImage, sKern);
        imshow("ROI Binary Image1", sROIBinaryImage);

        Canny(sROIBinaryImage, sROIEdgeImage, 50, 120, 3);
        imshow("ROI Edge Image", sROIEdgeImage);

        cvtColor(sROIEdgeImage, sHoughDestImage, CV_GRAY2BGR);
        imshow("ROI Hough Dest Image", sHoughDestImage);

    #pragma region Hough
        vector<Vec2f> lines;

        HoughLines(sROIEdgeImage, lines, 0.5, CV_PI/180, 30, 0, 0);
        printf("Lines number: %d\n", lines.size());

        for (size_t i = 0; i < lines.size(); ++i) {
            float rho = lines[i][0];
            float theta = lines[i][1];

            if (theta < 0.25 * CV_PI || theta >  0.75 * CV_PI) {
                continue;
            }
            printf("theta = %f\n", theta);

            Point pt1, pt2;
            double a = cos(theta), b = sin(theta);
            double x0 = a*rho, y0 = b*rho;
            pt1.x = cvRound(x0 + 1000 * (-b));
            pt1.y = cvRound(y0 + 1000*(a));
            pt2.x = cvRound(x0 - 1000*(-b));
            pt2.y = cvRound(y0 - 1000 * (a));

            line(sHoughDestImage, pt1, pt2, Scalar(0, 0, 255), 1, LINE_AA);

            imshow("ROI Hough Dest Image", sHoughDestImage);
        }
    #pragma endregion

        char chChar = waitKey(1);
        if (chChar == 27) {
            break;
        }
    }

    return 0;
}
