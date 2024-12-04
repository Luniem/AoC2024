use std::fs;

const FILE_INPUT: &str = "input.txt";

fn main() {
    
    let content = fs::read_to_string(FILE_INPUT).expect("Failed to read the file");
    
    let matrix: Vec<Vec<char>> = content.lines().map(|line| line.chars().collect()).collect();

    let directions: Vec<(i32, i32)> = vec![
        (0, 1), // right
        (1, 0), // down
        (0, -1), // left
        (-1, 0), // up
        (1, 1), // down-right
        (1, -1), // down-left
        (-1, 1), // up-right
        (-1, -1) // up-left
    ];
    let xmas_array = vec!['M', 'A', 'S'];

    let mut first_solution = 0;
    
    // loop through every entry in matrix
    for y in 0..matrix.len() {
        for x in 0..matrix[y].len() {

            // if the current value is 'X' we can start searching for the xmas entry
            let curr_value = matrix[y][x];
            if curr_value == 'X' {
                // check for every direction if we can find the xmas entry
                'direction_loop: for (dy, dx) in directions.iter() {
                    // iterate over the current depth
                    for depth in 0..xmas_array.len() {
                        // calculate the next position depending on the direction and the depth
                        let (new_y, new_x) = calc_next_xy(y as i32, x as i32, dy, dx, depth as i32);

                        if !check_for_match(new_y, new_x, &matrix, xmas_array[depth]) {
                            // if the curr char is not the one we are searching, we got no match, so lets skip to the next direction
                            continue 'direction_loop;
                        }
                    }
                    
                    // we got through all the depth of this direction ==> we found a match
                    first_solution += 1;
                }
            }
        }
    }

    println!("First solution: {}", first_solution);

    let mut second_solution = 0;

    for y in 0..matrix.len() {
        for x in 0..matrix[y].len() {

            // if the current value is 'A' we can start searching for the MAS-cross
            let curr_value = matrix[y][x];
            if curr_value == 'A' {
                let ny: i32 = y as i32;
                let nx = x as i32;

                // check top-left to bottom-right
                if (check_for_match(ny- 1, nx - 1, &matrix, 'M') && check_for_match(ny + 1, nx + 1, &matrix, 'S')) || 
                    (check_for_match(ny - 1, nx - 1, &matrix, 'S') && check_for_match(ny + 1, nx + 1, &matrix, 'M')) {
                    // check top-right to bottom-left
                    if (check_for_match(ny - 1, nx + 1, &matrix, 'M') && check_for_match(ny + 1, nx - 1, &matrix, 'S')) || 
                        (check_for_match(ny - 1, nx + 1, &matrix, 'S') && check_for_match(ny + 1, nx - 1, &matrix, 'M')) {
                        second_solution += 1;
                    }
                }
            }
        }
    }

    println!("Second solution: {}", second_solution);
}

fn is_valid_position(y: i32, x: i32, matrix_y_length: i32, matrix_x_length: i32) -> bool {
    // check if we are out of bounds
    return y >= 0 && y < matrix_y_length && x >= 0 && x < matrix_x_length;
}

fn check_for_match(y: i32, x: i32, matrix: &Vec<Vec<char>>, searched_char: char) -> bool {
    let y_length = matrix.len() as i32;
    let x_length = matrix.get(0).unwrap().len() as i32;

    if is_valid_position(y, x, y_length, x_length) && matrix[y as usize][x as usize] == searched_char {
        return true;
    }

    return false;
}

fn calc_next_xy(y: i32, x: i32, dy: &i32, dx: &i32, depth: i32) -> (i32, i32) {
    let new_y = y + dy * (depth + 1);
    let new_x = x + dx * (depth + 1);

    return (new_y, new_x);
}