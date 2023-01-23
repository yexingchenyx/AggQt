#include <iostream>
#include <opencv2/opencv.hpp>
#include <agg_rendering_buffer.h>
#include <agg_pixfmt_rgb.h>
#include <agg_renderer_base.h>
#include <agg_renderer_markers.h>

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

    agg::renderer_markers<agg::renderer_base<agg::pixfmt_rgb24>> ren_mark(render);
    ren_mark.line_color(agg::rgba8(0, 0, 0));
    ren_mark.fill_color(agg::rgba8(255, 0, 0));

    ren_mark.circle(10, 10, 10);
    ren_mark.cross(30, 30, 10);
    ren_mark.crossed_circle(60, 60, 10);
    ren_mark.dash(90, 90, 10);
    ren_mark.diamond(120, 120, 10);
    ren_mark.dot(150, 150, 10);
    ren_mark.four_rays(210, 210, 10);

    for (int i = agg::marker_square; i < agg::end_of_markers; ++i)
        ren_mark.marker(10 + i * 15, ren_mark.ren().height() - 15, 5, agg::marker_e(i));

    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
    cv::imshow("frame", frame);
    cv::waitKey(0);
    return 0;
}
