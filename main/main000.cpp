#include <iostream>
#include <opencv2/opencv.hpp>
#include <agg_rendering_buffer.h>

int main(int argc, char** argv) {

    const int frame_width = 320;
    const int frame_height = 200;
    const int frame_channel = 3;

    cv::Mat3b frame(frame_height, frame_width);

    unsigned char* buffer = frame.data;

    memset(buffer, 255, frame_width * frame_height * frame_channel);

    agg::rendering_buffer rbuf(buffer, 
                               frame_width, 
                               frame_height, 
                               frame_width * frame_channel);

    for(int i = 0; i < rbuf.height() / 2; ++i)
    {
        unsigned char* ptr = rbuf.row_ptr(i) + i * frame_channel;
        
        *ptr++ = 0;     // R
        *ptr++ = 0;     // G
        *ptr++ = 255;   // B
    }

    rbuf.attach(buffer + 
                20 * frame_width * frame_channel + 
                20 * frame_channel,
                frame_width - 40,
                frame_height - 40,
                - frame_width * frame_channel); // - 翻转y

    for(int i = 0; i < rbuf.height() / 2; ++i)
    {
        unsigned char* ptr = rbuf.row_ptr(i) + i * frame_channel;
        
        *ptr++ = 255;   // R
        *ptr++ = 0;     // G
        *ptr++ = 0;     // B
    }

    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
    cv::imshow("frame", frame);
    cv::waitKey(0);

    return 0;
}
