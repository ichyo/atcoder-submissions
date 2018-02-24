// cargo-deps: serde_json

extern crate serde_json;

use serde_json::{Error, Value};
use std::{fs, mem};
use std::io::{BufRead, BufReader, Read};

fn parse_line_range(s: &str) -> Option<(usize, usize)> {
    let v: Value = serde_json::from_str(&s).expect("failed to parse");
    if let Some(root) = v.get("message") {
        if let Some(message) = root.get("message").and_then(|m| m.as_str()) {
            if message.contains("is never used") && !message.starts_with("struct") {
                if let Some(spans) = root.get("spans").and_then(|m| m.as_array()).map(|a| &a[0]) {
                    return Some((
                        spans.get("line_start").unwrap().as_u64().unwrap() as usize,
                        spans.get("line_end").unwrap().as_u64().unwrap() as usize,
                    ));
                }
            }
        }
    }
    None
}

fn main() {
    let stdin = std::io::stdin();
    let target = std::env::args().nth(1).unwrap();
    let reader = BufReader::new(fs::File::open(target).unwrap());

    let mut ranges: Vec<(usize, usize)> = Vec::new();

    for s in stdin.lock().lines() {
        let s = s.unwrap();
        if let Some((b, e)) = parse_line_range(&s) {
            ranges.push((b - 1, e));
        }
    }

    ranges.sort();

    let mut idx = 0;

    for (l, s) in reader.lines().enumerate() {
        while idx < ranges.len() && ranges[idx].1 <= l {
            idx += 1;
        }
        if idx < ranges.len() && ranges[idx].0 <= l && l < ranges[idx].1 {
        } else {
            println!("{}", s.unwrap());
        }
    }
}
