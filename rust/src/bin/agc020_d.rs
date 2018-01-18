fn solve_ab(a: i64, b: i64, c: usize, d: usize) -> String {
    // aaa ab
    // aaa ab
    // aaa ab
    // aaa ab
    // a   ab
    //     ab
    // ??
    
    let height = b;
    let rest = a - b;
    let full_width = (rest + height) / (height + 1);
    let full_height = if full_width != 0 { rest / full_width } else { 0 };
    let last_width = rest - full_width * full_height;

    let mut s = String::new();
    println!("full:{}", full_height);
    for y in 0..(height+1) {
        let width = 
            if y < full_height {
                full_width
            } else if y == full_height {
                last_width
            } else {
                0
            };
        s.extend((0..width).map(|_| "A"));
        if y < height {
            s += "AB";
        }
    }
    s[(c-1)..d].to_owned()
}
fn solve_ba(a: i64, b: i64, c: usize, d: usize) -> String {
    let height = a;
    let rest = b - a;
    let full_width1 = (rest + height - 1) / height;
    let full_width2 = ((rest-1) + height) / (height + 1);

    let mut s = String::new();
    if full_width1 == full_width2 {
        let full_width = full_width1;
        let full_height = if full_width != 0 { rest / full_width } else { 0 };
        let last_width = rest - full_width * full_height;

        for y in 0..(height) {
            s += "AB";
            let width = 
                if y >= (height - full_height) {
                    full_width
                } else if y == (height - full_height - 1) {
                    last_width
                } else {
                    0
                };
            s.extend((0..width).map(|_| "B"));
        }

    } else {
        let full_width = full_width2;
        let full_height = if full_width != 0 { rest / full_width } else { 0 };
        let last_width = (rest-1) - full_width * full_height;

        for y in 0..(height+1) {
            let width = 
                if y >= (height - full_height) {
                    full_width
                } else if y == (height - full_height - 1) {
                    last_width
                } else {
                    0
                };
            s.extend((0..width).map(|_| "B"));
            if y < height {
                s += "BA";
            } else {
                s += "B"
            }
        }
    }

    s[(c-1)..d].to_owned()
}
fn solve(a: i64, b: i64, c: usize, d: usize) -> String {
    if a >= b {
        solve_ab(a, b, c, d)
    } else {
        solve_ba(a, b, c, d)
    }
}
fn main() {
    let q = readln();
    for _ in 0..q {
        let (a, b, c, d) = readln();
        println!("{}", solve(a, b, c, d));
    }
}

// --- template ---
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::HashSet;

pub trait FromLn {
    fn fromln(s: &str) -> Self;
}
pub fn readln<T: FromLn>() -> T {
    let mut buf = String::new();
    let _ = ::std::io::stdin().read_line(&mut buf).unwrap();
    T::fromln(buf.trim())
}
pub fn readlns<T: FromLn>(n: usize) -> Vec<T> {
    let mut vs = vec![];
    for _ in 0..n { vs.push(readln()); }
    vs
}
macro_rules! fromln_primitives {
    ($($t:ty),*) => { $(
        impl FromLn for $t {
            fn fromln(s: &str) -> $t {
                s.parse().unwrap()
            }
        }
    )* }
}
fromln_primitives!(String, bool, f32, f64, isize, i8, i16, i32, i64, usize, u8, u16, u32, u64);
impl<T> FromLn for Vec<T> where T: FromLn {
    fn fromln(s: &str) -> Vec<T> {
        s.split_whitespace().map(T::fromln).collect()
    }
}
impl FromLn for Vec<char> {
    fn fromln(s: &str) -> Vec<char> {
        s.chars().collect()
    }
}
macro_rules! fromln_tuple {
    ($($t:ident),*) => {
        impl<$($t),*> FromLn for ($($t),*) where $($t: FromLn),* {
            fn fromln(s: &str) -> ($($t),*) {
                let mut it = s.split_whitespace();
                let t = ($($t::fromln(it.next().unwrap())),*);
                assert_eq!(it.next(), None);
                t
            }
        }
    }
}
fromln_tuple!(A, B);
fromln_tuple!(A, B, C);
fromln_tuple!(A, B, C, D);
fromln_tuple!(A, B, C, D, E);
fromln_tuple!(A, B, C, D, E, F);
