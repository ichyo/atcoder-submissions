fn solve() -> String {
    let (n, m) = readln();
    let mut g = vec![Vec::new(); n];
    for _ in 0..m {
        let (a, b, c): (usize, usize, i64) = readln();
        g[a-1].push((b-1, -c));
    }
    let mut cost = vec![None; n];
    cost[0] = Some(0);
    for i in 0..n {
        for u in 0..n {
            if let Some(cur) = cost[u] {
                for &(v, c) in &g[u] {
                    let next = cur + c;
                    if cost[v].unwrap_or(i64::max_value()) > next && i == n-1 && v == n-1 {
                        return "inf".to_string();
                    }
                    cost[v] = Some(cost[v].map_or(next, |x| min(x, next)));
                }
            }
        }
    }
    (-(cost[n-1].unwrap())).to_string()
}
fn main() {
    println!("{}", solve());
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