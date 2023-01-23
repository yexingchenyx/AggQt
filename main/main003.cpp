#include <iostream>
#include <opencv2/opencv.hpp>
#include <agg_rendering_buffer.h>
#include <agg_pixfmt_rgb.h>
#include <agg_renderer_base.h>
#include <agg_renderer_primitives.h>

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

    agg::renderer_primitives<agg::renderer_base<agg::pixfmt_rgb24>> ren_prim(render);

    ren_prim.line_color(agg::rgba8(127, 0, 0));
    ren_prim.fill_color(agg::rgba8(0, 127, 127));
    ren_prim.outlined_rectangle(0, 0, ren_prim.ren().width() - 1, ren_prim.ren().height() - 1);

    ren_prim.line_color(agg::rgba8(0, 90, 20));
    ren_prim.ellipse(ren_prim.ren().width() / 2, ren_prim.ren().height() / 2, ren_prim.ren().width() / 2, ren_prim.ren().height() / 2);

    ren_prim.line_color(agg::rgba8(0, 0, 0));
    ren_prim.move_to(0, 0);
    ren_prim.line_to(ren_prim.coord(100), ren_prim.coord(100));
    ren_prim.line_to(ren_prim.coord(200), ren_prim.coord(60));
    ren_prim.line_to(ren_prim.coord(60), ren_prim.coord(30));
    ren_prim.line_to(0, 0);

    cv::cvtColor(frame, frame, cv::COLOR_RGB2BGR);
    cv::imshow("frame", frame);
    cv::waitKey(0);
    return 0;
}
