#include <iostream>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int OpenCameraVideo()
{
    char chFilePath[256] = "Resource/";
    char chVideoPath[256] = "";
    strcpy(chVideoPath, chFilePath);
    strcat(chVideoPath, "Video/video_test.wmv");

    VideoCapture cInputVideo;
    cInputVideo.open(chVideoPath);

    if (!cInputVideo.isOpened()) {
        return 0;
    }

    Mat sInputSrc;
    static int iIndex = 0;

    while(1) {
        if (!cInputVideo.read(sInputSrc)) {
            return 0;
            break;
        }
        imshow("Input Src", sInputSrc);

        char chPictureIndex[50] = "";
        sprintf(chPictureIndex, "%d.jpg", iIndex);

        char chPicturePath[256] = "";
        strcpy(chPicturePath, chFilePath);
        strcat(chPicturePath, "Picture/");
        strcat(chPicturePath, chPictureIndex);

        if (iIndex < 10) {
            imwrite(chPicturePath, sInputSrc);
        }

        ++iIndex;

        char chChar = waitKey(1);
        if (chChar == 27) {
            break;
        }
    }

    return 1;
}

int main()
{
    int iRet = OpenCameraVideo();
    if (!iRet) {
        printf("Open video failed!\n");
    }

	return 0;
}
