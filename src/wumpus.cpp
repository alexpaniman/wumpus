#include "gl.h"

using namespace math;

struct wumpus_map {
    enum cell: uint8_t { empty, wumpus, hole };
    std::vector<std::vector<cell>> cells;

    std::size_t rows = 20, cols = 20;
};

class wumpus: public gl::simple_drawing_window {
public:
    using gl::simple_drawing_window::simple_drawing_window;

    void loop_draw(gl::drawing_manager mgr) override {
        draw_map(mgr);
    }

private:
    wumpus_map m_current_map;

    void draw_map(gl::drawing_manager mgr) const {
        mgr.set_color({ 0.3f, 0.35f, 0.5f });

        const axes map_view = {
            { -0.9f, -0.9f },
            {  0.9f,  0.9f }
        };
        draw_cells(mgr.with_applied(map_view));

        mgr.set_color({ 0.7f, 0.3f, 0.4f });
        mgr.set_width(0.02f);

        const axes box_view = {
            { -0.95f, -0.95f },
            {  0.95f,  0.95f }
        };
        draw_bounding_box(mgr.with_applied(box_view));
    }

    void draw_bounding_box(gl::drawing_manager mgr) const {
        mgr.draw_line({ -1.0f, -1.0f }, { -1.0f,  1.0f });
        mgr.draw_line({ -1.0f,  1.0f }, {  1.0f,  1.0f });
        mgr.draw_line({ -1.0f, -1.0f }, {  1.0f, -1.0f });
        mgr.draw_line({  1.0f, -1.0f }, {  1.0f,  1.0f });
    }

    void draw_cells(gl::drawing_manager mgr) const {
        const vec step = { 2.0f / m_current_map.rows, 2.0f / m_current_map.cols };

        const vec spacing = { 0.003f, 0.003f };
        for (std::size_t i = 0; i < m_current_map.rows; ++ i)
            for (std::size_t j = 0; j < m_current_map.cols; ++ j) {
                axes current_cell = {
                    vec { 1.0f, 1.0f } - (step * vec { i,     j     } + spacing),
                    vec { 1.0f, 1.0f } - (step * vec { i + 1, j + 1 } - spacing)
                };

                draw_cell(mgr.with_applied(current_cell));
            }

    }

    static void draw_cell(gl::drawing_manager mgr) {
        mgr.draw_rectangle({ -1.0f, -1.0f }, { 1.0f, 1.0f });
    }

    void on_fps_updated() override {
        std::cout << "FPS: " << get_fps() << "\n";
    }

};

int main() {
    wumpus drawer(1080, 1080, "Wumpus | OpenGL");
    drawer.draw_loop();
}
 
