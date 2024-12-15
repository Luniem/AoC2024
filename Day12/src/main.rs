use std::{collections::HashSet, fs};

const FILE_INPUT: &str = "/home/nico/projects/AoC2024/Day12/input.txt";

const NEIGHBORS: [(i32, i32); 4] = [
    (0, 1), // right
    (1, 0), // down
    (0, -1), // left
    (-1, 0), // up
];

fn main() {
    let content = fs::read_to_string(FILE_INPUT).expect("Test");

    let matrix: Vec<Vec<char>> = content.lines().map(|line| line.chars().collect()).collect();
    let mut visited_sets: Vec<HashSet<(i32, i32)>> = Vec::new();

    let mut first_solution = 0;
    let mut second_solution = 0;

    // loop over every element in matrix and flood fill on char
    for y in 0..matrix.len() {
        for x in 0..matrix[y].len() {
            // skip if the current element was already visited
            if visited_sets.iter().any(|set| set.contains(&(y as i32, x as i32))) {
                continue;
            }

            let curr_elem = matrix[y][x];
            
            let visited = flood_fill(y as i32, x as i32, &matrix, curr_elem);
            // print_matrix_with_replacement(&matrix, &visited);
            visited_sets.push(visited);
        }
    }

    // calculate perimeter - just check how many neighbors are in the same group and subtract from 4
    for i in 0..visited_sets.len() {
        let region = &visited_sets[i];
        
        for (y, x) in region.iter() {
            let mut perimeter = 4;

            for (dy, dx) in NEIGHBORS.iter() {
                let new_y = y + dy;
                let new_x = x + dx;

                if region.contains(&(new_y, new_x)) {
                    perimeter -= 1;
                }
            }


            first_solution += perimeter * region.len();
        }
    }

    // calculate amount of sides
    for i in 0..visited_sets.len() {
        let region = &visited_sets[i];
        let mut sides = 0;

        for (dy, dx) in NEIGHBORS.iter() {
            let mut no_neighbors_elems: Vec<(i32, i32)> = Vec::new();

            // check which elements in region have no neighbor of the same region in the direction of dy, dx
            for (y, x) in region.iter() {
                let new_x = x + dx;
                let new_y = y + dy;
                
                if !region.contains(&(new_y, new_x)) {
                    no_neighbors_elems.push((*y, *x));
                }
            }

            // group them to elements on the same line
            let mut line_groups: Vec<Vec<(i32, i32)>> = Vec::new();
            for (y, x) in no_neighbors_elems.iter() {
                let mut found_group = false;

                for group in line_groups.iter_mut() {
                    let (first_y, first_x) = group[0];
                    
                    // check if we are considering y or x
                    if dy == &0 {
                        // we are considering x
                        if &first_x == x {
                            group.push((*y, *x));
                            found_group = true;
                            break;
                        }
                    } else {
                        // we are considering y
                        if &first_y == y {
                            group.push((*y, *x));
                            found_group = true;
                            break;
                        }
                    }
                }

                // if we didn't find a group we create a new one
                if !found_group {
                    line_groups.push(vec![(*y, *x)]);
                }
            }

            // check how many connected groups are in the line
            for group in line_groups.iter() {
                let mut not_connected_sides = 0;

                for (y, x) in group.iter() {
                    // if we are looking at border-elems for bottom, we want to check if left and right are connected and vice versa
                    let new_y1  = y + dx;
                    let new_x1 = x + dy;

                    let new_y2  = y + (dx * -1);
                    let new_x2 = x + (dy * -1);

                    if !group.contains(&(new_y1, new_x1)) {
                        not_connected_sides += 1;
                    }

                    if !group.contains(&(new_y2, new_x2)) {
                        not_connected_sides += 1;
                    }
                }
                
                sides += not_connected_sides / 2;
            }
        }

        second_solution += sides * region.len();
    }

    println!("First solution: {}", first_solution);
    println!("Second solution: {}", second_solution);
}

// flood fill based on char and return visited elements
fn flood_fill(y: i32, x: i32, matrix: &Vec<Vec<char>>, plot: char) -> HashSet<(i32, i32)> {
    let mut reachable_but_not_visited: Vec<(i32, i32)> = vec![(y, x)];
    let mut visited: HashSet<(i32, i32)> = HashSet::new();

    while !reachable_but_not_visited.is_empty() {
        let (curr_y, curr_x) = reachable_but_not_visited.pop().unwrap();
        visited.insert((curr_y, curr_x));

        for (dy, dx) in NEIGHBORS.iter() {
            let new_y = curr_y + dy;
            let new_x = curr_x + dx;

            if is_oob(new_y, new_x, matrix) || visited.contains(&(new_y, new_x)) || reachable_but_not_visited.contains(&(new_y, new_x)) {
                continue;
            }

            if matrix[new_y as usize][new_x as usize] == plot {
                reachable_but_not_visited.push((new_y, new_x));
            }
        }
    }

    visited
}

fn is_oob(y: i32, x: i32, matrix: &Vec<Vec<char>>) -> bool {
    y < 0 || x < 0 || y >= matrix.len() as i32 || x >= matrix[0].len() as i32
}