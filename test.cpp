#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 画像の読み込み
    cv::Mat img = cv::imread("image/img.png");

    if(img.empty()) {
        std::cout << "Error" << std::endl;
        return -1;
    }

    // 画像の表示
    cv::imshow("Sample Image", img);
    cv::waitKey(0);

    return 0;
}