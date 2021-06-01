#include "route_planner.h"

#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y) : m_Model(model) {
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  // Find the closest nodes to the starting and ending coordinates and store them in the RoutePlanner's start_node and 
  // end_node attributes.
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

// Calculates the h value as beeline from current node to end_node .
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  return node->distance(*end_node);
}

// Expands the current node by adding all unvisited neighbors to the open list.
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  // Populate current_node.neighbors vector with all neighbors
  current_node->FindNeighbors();  // Returns only un-visited neighbors

  for (auto *neighbor : current_node->neighbors) {
    neighbor->parent = current_node;
    neighbor->h_value = CalculateHValue(neighbor);
    neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
    neighbor->visited = true;
    open_list.push_back(neighbor);
  }
}

// Returns true if f value of node_a is larger than f value of node_b.
bool Compare(RouteModel::Node *node_a, RouteModel::Node *node_b) {
  float f_a = node_a->g_value + node_a->h_value;
  float f_b = node_b->g_value + node_b->h_value;
  return f_a > f_b;
}

// Sorts the open list according to h value and removes and returns the node with the lowest h value.
RouteModel::Node *RoutePlanner::NextNode() {
  // Sort open_list from highest to lowest f_value
  // This is expensive, it would probably be better to use a heap as open_list
  std::sort(open_list.begin(), open_list.end(), Compare);

  RouteModel::Node *lowest = open_list.back();
  open_list.pop_back();
  return lowest;
}

// Returns the final path found via A* search and stores its distance in this->distance.
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(
    RouteModel::Node *current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;
  distance = current_node->g_value;

  // Go through all parents to reconstruct the path from end_note to start_node
  while (current_node != start_node) {
    path_found.push_back(*current_node);
    current_node = current_node->parent;
  }

  // Add start_node to path
  path_found.push_back(*current_node);

  // Reverse path_found such that it is ordered from start_node to end_node
  std::reverse(path_found.begin(), path_found.end());

  // Multiply the distance by the scale of the map to get meters
  distance *= m_Model.MetricScale();
  return path_found;
}

// Performs A* Search and stores final path in m_Model.path.
void RoutePlanner::AStarSearch() {
  RouteModel::Node *current_node = start_node;
  open_list.push_back(current_node);
  current_node->visited = true;

  while (!open_list.empty()) {
    // Check if we have reached the goal
    if (current_node == end_node) {
      m_Model.path = ConstructFinalPath(current_node);
      return;
    }
    AddNeighbors(current_node);
    current_node = NextNode();
  }
}