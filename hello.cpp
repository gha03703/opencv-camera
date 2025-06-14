#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

int main() {
    cv::VideoCapture cap(0);
    
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open camera" << std::endl;
        return -1;
    }
    
    cv::Mat frame;
    const std::string windowName = "USB Camera Live Feed with FPS";
    
    // FPS計算用変数
    auto start_time = std::chrono::high_resolution_clock::now();
    int frame_count = 0;
    double fps = 0.0;
    
    std::cout << "Press 'q' to quit the camera feed" << std::endl;
    
    while (true) {
        cap >> frame;
        
        if (frame.empty()) {
            std::cerr << "Error: Could not capture frame" << std::endl;
            break;
        }
        
        // FPS計算
        frame_count++;
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time);
        
        if (elapsed.count() >= 1000) {  // 1秒ごとにFPS更新
            fps = frame_count * 1000.0 / elapsed.count();
            frame_count = 0;
            start_time = current_time;
        }
        
        // FPSを画面に描画
        std::string fps_text = "FPS: " + std::to_string(static_cast<int>(fps));
        cv::putText(frame, fps_text, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);
        
        cv::imshow(windowName, frame);
        
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }
    
    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}