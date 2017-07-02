fn interval(w: &[usize], m: usize) -> (usize, usize) {
    let (x, y) = (w[0], w[1]);
    if x <= y {
        (x, y)
    } else {
        (x, y + m)
    }
}

fn main() {
    let (_, m): (i32, usize) = readln();
    let a: Vec<usize> = readln::<Vec<usize>>().iter().map(|x| x-1).collect();
    let mut cost: Vec<i64> = vec![0; m*2 + 2];
    let mut num: Vec<i64> = vec![0; m*2 + 2];
    let mut all_cost: i64 = 0;

    for (u, v) in a.windows(2).map(|w| interval(w, m)).filter(|&(u, v)| u != v) {
        let d = (v - u) as i64;
        all_cost += d;
        num[u+1] += 1;
        num[v+1] -= 1;
    }

    let num_sum: Vec<i64> = num.iter()
        .scan(0, |s, &x| { *s = *s + x; Some(*s) })
        .collect();

    let mut cost_diff = num_sum.clone();

    for (u, v) in a.windows(2).map(|w| interval(w, m)).filter(|&(u, v)| u != v) {
        let d = (v - u) as i64;
        cost_diff[v+1] -= d;
    }

    let cost_sum: Vec<i64> = cost_diff.iter()
        .scan(0, |s, &x| { *s = *s + x; Some(*s) })
        .collect();

    let ans = all_cost - (0..m).map(|i| {
        cost_sum[i] + cost_sum[i+m] - num_sum[i] - num_sum[i+m]
    }).max().unwrap();

    println!("{}", ans);
}

// --- template ---
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::HashMap;

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