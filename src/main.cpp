#include "engine/app.hpp"
#include "engine/engine.hpp"
#include "engine/rendering.hpp"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <type_traits>
#include <variant>
#include <vector>
#include <map>
#include <optional>
#include <string>

int main() {
  App app;
  int w = 800;
  int h = 600;
  app.build(w, h, "Window name");

  int frame_w = 50;
  int frame_h = 50;

  std::map<std::pair<int,int>, size_t> tile_map;
  
  std::string str = "Current rendering objects: " + std::to_string(app.amount_rendered());
  ENGText t{
    .x = 0, .y = 0, .s = 20, .inside = str, .c = ENGRED, .sticky = true, .id = 2
  };
  app.objects.push_back(t);

  static std::optional<ENGCursorPosition> gc;
  int camera_x = 0;
  int camera_y = 0;
  int buffer = 2;

  while (app.is_running()) {
    app.drawer.EngBGColor(ENGWHITE);

    app.EngGetUserInput();
    std::vector<ENGKeys> current_input = app.EngCurrentUserInputExtract();

    if (std::ranges::find(current_input, ENGKeys::LMB) != current_input.end()) {
      ENGCursorPosition c = app.EngGetCursorPosition();
      if (!gc) {
        gc = c;
      } else {
        int dx = c.x - gc->x;
        int dy = c.y - gc->y;
        
        camera_x -= dx;
        camera_y -= dy;
        
        gc = c;
      }
    } else {
      gc.reset();
    }

    int left_bound   = -buffer * frame_w;
    int right_bound  = w + buffer * frame_w;
    int top_bound    = -buffer * frame_h;
    int bottom_bound = h + buffer * frame_h;

    int start_col = (camera_x + left_bound) / frame_w;
    int end_col   = (camera_x + right_bound) / frame_w;
    int start_row = (camera_y + top_bound) / frame_h;
    int end_row   = (camera_y + bottom_bound) / frame_h;

    std::cout << "-----------Frame-----------" << "\n";
    std::cout << "camera_x: " << camera_x << ", camera_y: " << camera_y << "\n";
    std::cout << "Tile count: " << tile_map.size() << "\n";
    std::cout << "Visible range - cols: [" << start_col << ", " << end_col 
              << "], rows: [" << start_row << ", " << end_row << "]\n";

    for (int col = start_col; col <= end_col; ++col) {
      for (int row = start_row; row <= end_row; ++row) {
        int world_x = col * frame_w;
        int world_y = row * frame_h;
        
        if (tile_map.contains({world_x, world_y})) {
          continue;
        }
        
        int screen_x = world_x - camera_x;
        int screen_y = world_y - camera_y;
        
        std::cout << "Creating tile at world(" << world_x << ", " << world_y 
                  << ") screen(" << screen_x << ", " << screen_y << ")\n";
        
        app.objects.push_back(ENGFrame{
          .x = screen_x, .y = screen_y,
          .w = frame_w, .h = frame_h, .c = ENGRED, .id = 1
        });
        
        tile_map[{world_x, world_y}] = app.objects.size() - 1;
      }
    }

    for (auto& [world_coords, obj_index] : tile_map) {
      auto& obj = app.objects[obj_index];
      
      std::visit([&](auto &item){
        using T = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<T, ENGFrame>) {
          if (item.id == 1) {
            item.x = world_coords.first - camera_x;
            item.y = world_coords.second - camera_y;
            
            item.draw = !(item.x + item.w < 0 || item.y + item.h < 0 || 
                         item.x > w || item.y > h);
          }
        }
      }, obj);
    }

    int rendering_amount = app.amount_rendered();
    for (auto &obj : app.objects) {
      std::visit([rendering_amount](auto &item){
        using T = std::decay_t<decltype(item)>;
        if constexpr (std::is_same_v<T, ENGText>) {
          item.inside = "Current rendering objects: " + std::to_string(rendering_amount);
        }
      }, obj);
    }

    app.drawer.EngDrawAll(app.objects);
    app.run_frame();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
  
  app.print_all_objects();
  return 0;
}
