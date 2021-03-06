fn rec(v: usize, used: &mut Vec<bool>, graph: &Vec<Vec<usize>>) -> u64 {
    used[v] = true;
    let n = graph.len();
    let goal = used.iter().all(|&x| x);
    let next: Vec<&usize> = graph[v].iter().filter(|&&x| !used[x]).collect();
    //println!("{:?} {:?} {:?}", v, used, goal);
    let res = match goal {
        true => 1,
        false => next.iter().map(|&&x| rec(x, used, graph)).sum()
    };
    used[v] = false;
    res
}

fn main() {
    let (n, m): (usize, usize) = readln();
    let mut g = vec![vec![]; n];
    for _ in 0..m {
        let (a_, b_): (usize, usize) = readln();
        let (a, b) = (a_-1, b_-1);
        g[a].push(b);
        g[b].push(a);
    }
    let mut used = vec![false; n];
    let ans: u64 = rec(0, &mut used, &g);
    println!("{}", ans);
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