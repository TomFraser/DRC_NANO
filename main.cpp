#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
    cv::VideoCapture cap = cv::VideoCapture(0);
    if(!cap.isOpened()) {
        exit(1);
    }
    while(1) {
        cv::Mat frame;
        cap >> frame;
        if(frame.empty()) {
            break;
        }
        cv::imshow("Frame", frame);

        char c=(char)cv::waitKey(25);
        if(c == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}