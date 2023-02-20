#include <iostream>
#include <vector>
#include <stack>

const int N = 3;
const int TARGET = 2;

// Define the initial state of the containers
std::vector<int> initial_state = {0, 7, 4};

// Define the goal state
bool is_goal_state(const std::vector<int>& state) {
  return state.at(1) == TARGET || state.at(2) == TARGET;
}

// Define the pouring operation
std::vector<int> pour(const std::vector<int>& state, int from, int to) {
  std::vector<int> new_state(state);
  int space = N - to;
  int amount = std::min(space, state[from]);
  new_state.at(from) -= amount;
  new_state.at(to) += amount;
  return new_state;
}

// Define the DFS algorithm
bool dfs() {
  std::stack<std::vector<int>> frontier;
  frontier.push(initial_state);
  std::vector<std::vector<int>> visited;
  while (!frontier.empty()) {
    std::vector<int> state = frontier.top();
    frontier.pop();
    if (is_goal_state(state)) {
      return true;
    }
    visited.push_back(state);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
	if (i != j) {
	  std::vector<int> new_state = pour(state, i, j);
	  bool is_new = true;
	  for (int k = 0; k < visited.size(); k++) {
	    if (visited.at(k) == new_state) {
	      is_new = false;
	      break;
	    }
	  }
	  if (is_new) {
	    frontier.push(new_state);
	  }
	}
      }
    }
  }
  return false;
}

int main() {
  bool result = dfs();
  if (result) {
    std::cout << "Si existe un camino donde quedan " << TARGET << " litros en los contenedores" << std::endl;
  } else {
    std::cout << "No existe un camino donde quedan " << TARGET << " litros en los contenedores" << std::endl;
  }
  return 0;
}
