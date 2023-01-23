#include <iostream>
#include <opencv2/core.hpp>

int main(int argc, char** argv) {
    cv::Mat1b a = cv::Mat1b::zeros(3, 3);
    std::cout << a << std::endl;
}
