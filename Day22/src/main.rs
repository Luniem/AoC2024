use std::{collections::{HashMap, HashSet}, fs};

const FILE_INPUT: &str = "/home/nikz/projects/AoC2024/Day22/input.txt";

fn main() {
    let content = fs::read_to_string(FILE_INPUT).expect("Failed to read the file");
    
    let buyers: Vec<u64> = content.lines().map(|line| line.parse::<u64>().expect("Should be able to convert!")).collect();
    let mut first_solution: u64 = 0;

    let mut sequence: HashMap<Vec<i8>, u64> = HashMap::new();

    const RUNS: u32 = 2000;
    const PRUNE_NUMBER: u64 = 16777216;

    for buyer in buyers {
        let mut current_number = buyer;
        let mut current_sequence: Vec<i8> = vec![0, 0, 0, 0];
        let mut used_sequence: HashSet<Vec<i8>> = HashSet::new();

        for run in 0..RUNS {
            let prev_bananas = current_number % 10;

            current_number = ((current_number * 64) ^ current_number) % PRUNE_NUMBER;
            current_number =  ((current_number / 32) ^ current_number) % PRUNE_NUMBER;
            current_number = ((current_number * 2048) ^ current_number) % PRUNE_NUMBER;

            let current_bananas = current_number % 10;

            // remove the last element and push the new element
            current_sequence.remove(0);
            current_sequence.push(current_bananas as i8 - prev_bananas as i8);

            // if we have filled our sequence with 4 entries
            if run > 3 && !used_sequence.contains(&current_sequence) {
                let key = current_sequence.clone();
                used_sequence.insert(key.clone());
                let count = sequence.entry(key).or_insert(0);
                *count += current_bananas;
            }
        }
        first_solution += current_number;
    }

    let second_solution = sequence.values().max();
    
    println!("First Solution: {}", first_solution);
    println!("Second Solution: {}", second_solution.unwrap());
}
