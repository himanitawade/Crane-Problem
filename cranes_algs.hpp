///////////////////////////////////////////////////////////////////////////////
// cranes_algs.hpp
//
// Algorithms that solve the crane unloading problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crane_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <math.h>

#include "cranes_types.hpp"

namespace cranes {

// Solve the crane unloading problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
  path crane_unloading_exhaustive(const grid& setting) {

    // grid must be non-empty.
    assert(setting.rows() > 0);
    assert(setting.columns() > 0);

    // Compute maximum path length, and check that it is legal.
    const size_t max_steps = setting.rows() + setting.columns() - 2;
    assert(max_steps < 64);

    path best(setting);
    path new_path(setting);

    std::vector<path> all_paths;
    all_paths.insert(all_paths.end(), new_path);


    for (size_t steps = 0; steps <= max_steps; steps++) {
        if (best.final_row()+1 == setting.rows() &&
            best.final_column()+1 == setting.columns()) break;

        std::vector<path> new_paths = all_paths;
        all_paths.clear();

        while (!new_paths.empty()){
          new_path = new_paths.back();
          new_paths.pop_back();

          if (new_path.final_row()+1 == setting.rows() &&
              new_path.final_column()+1 == setting.columns()){
            if (best.total_cranes() < new_path.total_cranes()){
              best = new_path;
            }
          }
          else {
            if (new_path.is_step_valid(STEP_DIRECTION_EAST)){
              path next_path = new_path;
              next_path.add_step(STEP_DIRECTION_EAST);
              all_paths.insert(all_paths.end(), next_path);
            }
            if (new_path.is_step_valid(STEP_DIRECTION_SOUTH)){
              path next_path = new_path;
              next_path.add_step(STEP_DIRECTION_SOUTH);
              all_paths.insert(all_paths.end(), next_path);
            }
          }
        }
    }
    return best;
  }

// Solve the crane unloading problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
  path crane_unloading_dyn_prog(const grid& setting) {

    path best(setting);
    assert(setting.rows() > 0);
    assert(setting.columns() > 0);

    int my_grid[setting.rows()+1][setting.columns()+1];
    cell_kind current_cell;

    for(int i = 0; i < setting.rows()+1; i++){
      for(int j = 0; j < setting.columns()+1; j++){
          if (i == 0 || j == 0) {
            my_grid[i][j] = 0;
          } else {
            if (i == 1 && j == 1) my_grid[i][j] = 1;
            else my_grid[i][j] = 0;
            current_cell = setting.get(i-1,j-1);
            if (current_cell == CELL_BUILDING) {
              my_grid[i][j] = -1;
            } else {
              if (current_cell == CELL_CRANE){
                my_grid[i][j] += 1;
              }
              int max;
              if (my_grid[i-1][j] > my_grid[i][j-1]){
                max = my_grid[i-1][j];
              } else max = my_grid[i][j-1];
              my_grid[i][j] += max;
            }
        }
      }
    }

    const size_t max_steps = setting.rows() + setting.columns() - 2;
    int x = setting.rows();
    int y = setting.columns();
    std::vector<step_direction> directions; 

    for (int i = 0; i < max_steps; i++){
      if ((my_grid[x-1][y] == -1) && (my_grid[x][y-1] == -1)){
        --y;
        --x;
      } else if (my_grid[x][y] == -1){
        --y;
        break;
      } else if ((my_grid[x-1][y] >= my_grid[x][y-1]) && x != 1){
        directions.insert(directions.end(), STEP_DIRECTION_SOUTH);
        --x;
      } else if (y != 1) {
        directions.insert(directions.end(), STEP_DIRECTION_EAST);
        --y;
      }
    }

    int size = directions.size();
    for (int i = size; i > 0; i--) {
      step_direction current_direction = directions.back();
      if (best.is_step_valid(current_direction)) best.add_step(current_direction);
      directions.pop_back(); 
    }
    return best;
    
  }
}
=======
path crane_unloading_dyn_prog(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  
  using cell_type = std::optional<path>;

  std::vector<std::vector<cell_type> > A(setting.rows(),
                                        std::vector<cell_type>(setting.columns()));

  A[0][0] = path(setting);
  assert(A[0][0].has_value());

  for (coordinate r = 0; r < setting.rows(); ++r) {
    for (coordinate c = 0; c < setting.columns(); ++c) {

      if (setting.get(r, c) == CELL_BUILDING){
        A[r][c].reset();
        continue;
        }

    cell_type from_above = std::nullopt;
    cell_type from_left = std::nullopt;

	    // TODO: implement the dynamic programming algorithm, then delete this
  // comment.

   assert(best->has_value());
//  //   std::cout << "total cranes" << (**best).total_cranes() << std::endl;

   return **best;
	}

}
