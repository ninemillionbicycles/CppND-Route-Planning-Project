#include "render.h"
#include "route_model.h"
#include "route_planner.h"
#include <fstream>
#include <io2d.h>
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <vector>

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path) {
  // Prefer initializer syntax {} over () per C++ Core Guidelines
  // Second parameter specifies the mode, multiple modes can be combined using
  // "|"
  std::ifstream is{path, std::ios::binary | std::ios::ate};
  if (!is)
    return std::nullopt;

  auto size = is.tellg();
  std::vector<std::byte> contents(size);

  is.seekg(0);
  is.read((char *)contents.data(), size);

  if (contents.empty())
    return std::nullopt;
  return std::move(contents);
}

int main(int argc, const char **argv) {
  std::string osm_data_file = "";
  // If input looks like [executable] -f [filename.osm], choose map accordingly
  if (argc > 1) {
    for (int i = 1; i < argc; ++i)
      if (std::string_view{argv[i]} == "-f" && ++i < argc)
        osm_data_file = argv[i];
  }
  // If input not given or not usable use default map
  else {
    std::cout << "To specify a map file use the following format: " << std::endl;
    std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
    osm_data_file = "../map.osm";
  }

  std::vector<std::byte> osm_data;

  if (osm_data.empty() && !osm_data_file.empty()) {
    std::cout << "Reading OpenStreetMap data from the following file: "
              << osm_data_file << std::endl;
    auto data = ReadFile(osm_data_file);
    if (!data)
      std::cout << "Failed to read." << std::endl;
    else
      osm_data = std::move(*data);
  }

  std::cout << "Please enter the coordinates of the start and end point "
               "between which you want to find the shortest path. \n";

  std::vector<std::string> input_text{
      "start_x",
      "start_y",
      "end_x",
      "end_y",
  };

  float input;
  std::vector<float> inputs;
  int index = 0;

  while (index < 4) {
    std::cout << input_text[index] << ": ";
    while (!(std::cin >> input)) { // Check whether the input is a number
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input, please try again. " << input_text[index] << ": ";
    }
    if (input >= 0 &&
        input <= 100) { // Check whether the number is in the range
      inputs.push_back(input);
      index++;
    } else {
      std::cout << "Number must be between 0 and 100, please try again. ";
    }
  }

  // Build Model.
  RouteModel model{osm_data};

  // Create RoutePlanner object and perform A* search.
  RoutePlanner route_planner{model, inputs[0], inputs[1], inputs[2], inputs[3]};
  route_planner.AStarSearch();

  std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

  // Render results of search.
  Render render{model};

  auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
  display.size_change_callback([](io2d::output_surface &surface) {
    surface.dimensions(surface.display_dimensions());
  });
  display.draw_callback( [&](io2d::output_surface &surface) { render.Display(surface); });
  display.begin_show();
}
