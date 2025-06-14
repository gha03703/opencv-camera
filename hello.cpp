#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        return -1;
    }
    
    cv::Mat frame;
    const std::string windowName = "USB Camera Live Feed";
    
    std::cout << "Press 'q' to quit the camera feed" << std::endl;
    
    while (true) {
        cap >> frame;
        
        if (frame.empty()) {
            std::cerr << "Error: Could not capture frame" << std::endl;
            break;
        }
        
        cv::imshow(windowName, frame);
        
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}