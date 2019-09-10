#include <iostream>
#include <thread>
#include <opencv2/opencv.hpp>

using namespace std;

string gstreamer_pipeline (int capture_width, int capture_height, int display_width, int display_height, int framerate, int flip_method) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(capture_width) + ", height=(int)" +
           std::to_string(capture_height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(framerate) +
           "/1 ! nvvidconv flip-method=" + std::to_string(flip_method) + " ! video/x-raw, width=(int)" + std::to_string(display_width) + ", height=(int)" +
           std::to_string(display_height) + ", format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}

int main() {
    #ifdef __APPLE__ || __MACH__
        cv::VideoCapture cap = cv::VideoCapture(0);
        cout << "Using MacOS Device Capture" << endl;
    #elif __linux__
        string pipeline = gstreamer_pipeline(1920, 1080, 1920, 1080, 60, 0);
        cv::VideoCapture cap = cv::VideoCapture(pipeline, cv::CAP_GSTREAMER);
        cout << "Using Linux Device Capture (PiCam)" << endl;
    #endif
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