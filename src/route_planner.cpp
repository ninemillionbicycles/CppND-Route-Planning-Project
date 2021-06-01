#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y,
                           float end_x, float end_y)
    : m_Model(model) {
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to
  // the starting and ending coordinates. Store the nodes you find in the
  // RoutePlanner's start_node and end_node attributes.
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);

  // DELETE
  std::cout << "Found the following start and end nodes: \n";
  std::cout << start_node->x << " " << start_node->y << "\n";
  std::cout << end_node->x << " " << end_node->y << "\n";
}

// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another
// node.
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  float result = node->distance(*end_node);
  std::cout << "Distance to end node (h value) = " << result;
  return result;
}

// TODO 4: Complete the AddNeighbors method to expand the current node by adding
// all unvisited neighbors to the open list. Tips:
// - Use the FindNeighbors() method of the current_node to populate
// current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the
// g_value.
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and
// set the node's visited attribute to true.
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  // Populate current_node.neighbors vector with all neighbors
  current_node->FindNeighbors();

  float tentative_g_value;

  for (RouteModel::Node *node : current_node->neighbors) {
    tentative_g_value = current_node->g_value + current_node->distance(*node);

    if (!node->visited || tentative_g_value < node->g_value) {
      // This path to node is better than any previously found one (if any)
      node->parent = current_node;
      node->g_value = tentative_g_value;
      node->h_value = CalculateHValue(node);
      node->visited = true;

      // If the node is not in the open_list
      if (std::find(open_list.begin(), open_list.end(), node) ==
          open_list.end()) {
        open_list.push_back(node);
      }
    }
  }
}

// Functions returns true if f value of node_a is larger than f value of node_b
bool CompareNodes(RouteModel::Node *node_a, RouteModel::Node *node_b) {
  return ((node_a->g_value + node_a->h_value) >
          (node_b->g_value + node_b->h_value));
}

// TODO 5: Complete the NextNode method to sort the open list and return the
// next node. Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.
RouteModel::Node *RoutePlanner::NextNode() {
  // Sort open_list from highest to lowest f_value
  // This is expensive, it would probably be better to use a heap as open_list
  std::sort(open_list.begin(), open_list.end(), CompareNodes);

  RouteModel::Node *lowest = open_list.back();
  open_list.pop_back();
  return lowest;
}

// TODO 6: Complete the ConstructFinalPath method to return the final path
// found from your A* search. Tips:
// - This method should take the current (final) node as an argument and
// iteratively follow the chain of parents of nodes until the starting node is
// found.
// - For each node in the chain, add the distance from the node to its parent
// to the distance variable.
// - The returned vector should be in the correct order: the start node should
// be the first element of the vector, the end node should be the last element.
std::vector<RouteModel::Node>
RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;

  distance = current_node->g_value;

  // Reconstruct the path from end_note to start_node by going through all
  // parents
  while (current_node != start_node) {
    path_found.push_back(*current_node);
    current_node = current_node->parent;
  }

  // Add start_node to path
  path_found.push_back(*current_node);

  // Reverse path_found such that it is ordered from start_node to end_node
  std::reverse(path_found.begin(), path_found.end());

  distance *= m_Model.MetricScale(); // Multiply the distance by the scale of
                                     // the map to get meters.
  return path_found;
}

// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current
// node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath
// method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method
// exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
  std::cout << "A* Search started.\n";

  RouteModel::Node *current_node = nullptr;
  // TODO: Implement your solution here.
}