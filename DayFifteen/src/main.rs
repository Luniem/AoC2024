use std::{collections::VecDeque, fs};

#[allow(dead_code)]
const TEST_FILE_INPUT: &str = "/home/nico/projects/AoC2024/DayFifteen/testInput.txt";
const FILE_INPUT: &str = "/home/nico/projects/AoC2024/DayFifteen/input.txt";

fn main() {
    let first_solution = first_solution(FILE_INPUT);
    let second_solution = second_solution(FILE_INPUT);

    println!("First solution: {}", first_solution);
    println!("Second solution: {}", second_solution);
}

fn first_solution(file_path: &str) -> i32{
    let file_content = fs::read_to_string(file_path).expect("Error reading file");
    let mut lines = file_content.lines().collect::<Vec<&str>>();

    let mut instructions: Vec<char> = Vec::new();
    let mut walls: Vec<GridElement> = Vec::new();
    let mut boxes: Vec<GridElement> = Vec::new();
    let mut robot: GridElement = GridElement::new(0, 0, 0);
    let mut grid: Vec<&str> = Vec::new();

    // get the movement grid out of the input
    let mut current_line = lines.remove(0);
    while !current_line.is_empty() {
        grid.push(current_line);
        current_line = lines.remove(0);
    }

    // get all the walls, boxes and the robots
    for y in 0..grid.len() {
        for x in 0..grid[y].len() {
            match grid[y].chars().nth(x).unwrap() {
                '#' => {
                    walls.push(GridElement::new(x as i32, x as i32, y as i32));
                },
                'O' => {
                    boxes.push(GridElement::new(x as i32, x as i32, y as i32));
                },
                '@' => robot = GridElement::new(x as i32, x as i32, y as i32),
                _ => (),
            };
        }
    }

    // get all the instructions
    while lines.len() > 0 {
        current_line = lines.remove(0);
        
        for c in current_line.chars() {
            instructions.push(c);
        }
    }

    proceed_all_instructions_and_calculate_gps_score(instructions, robot, walls, boxes)
}

fn second_solution(file_path: &str) -> i32 {
    let file_content = fs::read_to_string(file_path).expect("Error reading file");
    let mut lines = file_content.lines().collect::<Vec<&str>>();

    let mut instructions: Vec<char> = Vec::new();
    let mut walls: Vec<GridElement> = Vec::new();
    let mut boxes: Vec<GridElement> = Vec::new();
    let mut robot: GridElement = GridElement::new(0, 0, 0);
    let mut grid: Vec<String> = Vec::new();

    // get the movement grid out of the input
    let mut current_line = lines.remove(0);
    while !current_line.is_empty() {
        let mut line: String = String::new();

        for char in current_line.chars(){
            match char {
                '#' => line.push_str("##"),
                'O' => line.push_str("[]"),
                '@' => line.push_str("@."),
                '.' => line.push_str(".."),
                _ => panic!("Invalid character in grid"),
            }
        }

        grid.push(line);
        current_line = lines.remove(0);
    }

    // get all the walls, boxes and the robots
    for y in 0..grid.len() {
        for x in 0..grid[y].len() {
            match grid[y].chars().nth(x).unwrap() {
                '#' => {
                    walls.push(GridElement::new(x as i32, x as i32, y as i32));
                },
                '[' => {
                    boxes.push(GridElement::new(x as i32, (x + 1) as i32, y as i32));
                },
                '@' => robot = GridElement::new(x as i32, x as i32, y as i32),
                _ => (),
            };
        }
    }

    // get all the instructions
    while lines.len() > 0 {
        current_line = lines.remove(0);
        
        for c in current_line.chars() {
            instructions.push(c);
        }
    }

    proceed_all_instructions_and_calculate_gps_score(instructions, robot, walls, boxes)
}


fn proceed_all_instructions_and_calculate_gps_score(instructions: Vec<char>, mut robot: GridElement, walls: Vec<GridElement>, mut boxes: Vec<GridElement>) -> i32 {
    let mut solution = 0;

    'instruction: for instruction in instructions {
        let robots_next_theoretical_position = robot.move_tile(instruction);

        if  !robots_next_theoretical_position.is_intersecting_with_element_from_vector(&walls) {

            // check how many boxes are in front of us
            let mut all_pushed_boxes: Vec<GridElement> = Vec::new();
            let mut move_queue: VecDeque<GridElement> = VecDeque::new();

            // start with the robot
            move_queue.push_back(GridElement::new(robot.x.start, robot.x.end, robot.y));

            while !move_queue.is_empty() {
                // go to next tile of the current element
                let next_grid_elem = move_queue.pop_front().expect("should be here").move_tile(instruction);

                // now we check if it would intersect with a box
                for box_pos in boxes.iter() {

                    if box_pos.is_interesecting(&next_grid_elem) && box_pos.move_tile(instruction) != next_grid_elem {

                        // check if the box would also not hit a wall
                        if box_pos.move_tile(instruction).is_intersecting_with_element_from_vector(&walls) {
                            // one of the boxes we would push is blocked by a wall, we are doing nothing this step
                            continue 'instruction;
                        }

                        if !all_pushed_boxes.contains(&box_pos) {
                            all_pushed_boxes.push(GridElement::new(box_pos.x.start, box_pos.x.end, box_pos.y));
                            move_queue.push_back(GridElement::new(box_pos.x.start, box_pos.x.end, box_pos.y));
                        }
                    }
                }
            }
            
            // move the robot
            robot = robots_next_theoretical_position;

            // remove the moved boxes
            'outer: for box_pos in all_pushed_boxes.iter() {
                for i in 0..boxes.len() {
                    if box_pos == &boxes[i] {
                        boxes.remove(i);

                        continue 'outer;
                    }
                }
            }

            // add the moved boxes
            for box_pos in all_pushed_boxes.iter() {
                let box_pushed = box_pos.move_tile(instruction);
                boxes.push(box_pushed);
            }
        }
    }

    for box_pos in boxes.iter() {
        // solution += min(box_pos.x.start, grid[0].len() as i32 - box_pos.x.end - 1) + min(box_pos.y, grid.len() as i32 - box_pos.y - 1) * 100;
        solution += box_pos.x.start + box_pos.y * 100;
    }

    solution
}

struct Range {
    start: i32,
    end: i32,
}

struct GridElement {
    x: Range,
    y: i32
}

impl GridElement {
    fn new(x_start: i32, x_end: i32, y: i32) -> GridElement {
        GridElement {
            x: Range {
                start: x_start,
                end: x_end,
            },
            y: y,
        }
    }

    fn is_interesecting(&self, other: &GridElement) -> bool {
        self.x.start <= other.x.end && self.x.end >= other.x.start && self.y == other.y
    }

    fn is_intersecting_with_element_from_vector(&self, collection: &Vec<GridElement>) -> bool {
        for elem in collection.iter() {
            if self.is_interesecting(elem) {
                return true;
            }
        }

        false
    }

    fn move_tile(&self, direction: char) -> GridElement {
        let mut new_x_range = Range { start: self.x.start, end: self.x.end };
        let mut new_y = self.y.clone();

        match direction {
            '^' => new_y -= 1,
            'v' => new_y += 1,
            '<' => {
                new_x_range.start -= 1;
                new_x_range.end -= 1;
            },
            '>' => {
                new_x_range.start += 1;
                new_x_range.end += 1;
            },
            _ => (),
        }

        GridElement {
            x: new_x_range,
            y: new_y,
        }
    }
}

impl PartialEq for GridElement {
    fn eq(&self, other: &Self) -> bool {
        self.x.start == other.x.start && self.x.end == other.x.end && self.y == other.y
    }
}