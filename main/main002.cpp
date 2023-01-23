#include <iostream>
#include <opencv2/opencv.hpp>
#include <agg_rendering_buffer.h>
#include <agg_pixfmt_rgb.h>
#include <agg_renderer_base.h>

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

    agg::pixfmt_rgb24 pixf(rbuf);

    agg::renderer_base<agg::pixfmt_rgb24> render(pixf);

    render.clip_box(0, 0, render.width() / 2, render.height() - 1); // 仅会作用在box内

    render.blend_bar(0, 0, render.width(), render.height() / 2, agg::rgba8(255, 0, 0), 127);

    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
    cv::imshow("frame", frame);
    cv::waitKey(0);
    return 0;
}
