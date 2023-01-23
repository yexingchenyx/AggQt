#include <iostream>
#include <opencv2/opencv.hpp>
#include <agg_rendering_buffer.h>
#include <agg_pixfmt_rgb.h>

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

    for(int i = 0; i < rbuf.height() / 2; ++i)
    {
        pixf.copy_pixel(i, i, agg::rgba8(255, 0, 0));
    }

    rbuf.attach(buffer + 
                20 * frame_width * frame_channel + 
                20 * frame_channel,
                frame_width - 40,
                frame_height - 40,
                - frame_width * frame_channel); // - 翻转y

    for(int i = 0; i < rbuf.height() / 2; ++i)
    {
        pixf.copy_pixel(i, i, agg::rgba8(0, 0, 255));
    }

    rbuf.attach(buffer, frame_width, frame_height, frame_width * frame_channel);
    pixf.copy_hline(0, rbuf.height() / 2, rbuf.width(), agg::rgba8(0, 255, 0));
    pixf.copy_vline(rbuf.width() / 2, 0, rbuf.height(), agg::rgba8(0, 255, 0));

    rbuf.attach(buffer + frame_width / 2 * frame_channel,
                frame_width / 2,
                frame_height / 2,
                frame_width * frame_channel);
    for (int i = 0; i < rbuf.height(); ++i) {
        pixf.copy_hline(0, i, rbuf.width(), agg::rgba8(0, 0, 0));
    }

    agg::rgba8 span[frame_width];
    agg::int8u cover[frame_width];
    for (int i = 0; i < frame_width; ++i) {
        double wavelength = 380.0 + 400.0 * i / frame_width;
        agg::rgba c(wavelength, 0.8);
        span[i] = agg::rgba8(c);
        cover[i] = i % 255;
    }

    for (int i = 0; i < rbuf.height(); ++i) {
        pixf.blend_color_hspan(0, i, rbuf.width(), span, cover, 0);
        // pixf.blend_color_hspan(0, i, rbuf.width(), span, nullptr, 255);
    }

    rbuf.attach(buffer + 
                frame_height / 2 * frame_width * frame_channel +
                frame_width / 2 * frame_channel,
                frame_width / 2,
                frame_height / 2,
                frame_width * frame_channel);
    for (int i = 0; i < rbuf.width(); ++i) {
        pixf.blend_solid_vspan(i, 0, rbuf.height(), agg::rgba8(127, 60, 30), cover);
    }

    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
    cv::imshow("frame", frame);
    cv::waitKey(0);

    return 0;
}
