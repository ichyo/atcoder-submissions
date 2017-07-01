fn main() {
    let (n, a, b): (usize, usize, usize) = readln();
    let mut v: Vec<i64> = readln();
    v.sort_by_key(|x| -x);
    let x = v[a-1];
    let mut ave: f64 = 0.0;
    for i in 0..a {
        ave += v[i] as f64 / a as f64;
    }
    let k1 = v.iter().enumerate()
        .filter(|&(i, val)| val - x == 0)
        .map(|(i, val)| i)
        .min().unwrap();
    let k2 = v.iter().enumerate()
        .filter(|&(i, val)| val - x == 0)
        .map(|(i, val)| i)
        .max().unwrap();
    let from = max(a-1, k1);
    let to = if x == v[0] {
        min(b-1, k2)
    } else {
        from
    };
    let mut ans : u64 = 0;

    let mut dp = [[0 as u64; 55]; 55];
    dp[0][0] = 1;
    for i in 1..51 {
        dp[i][0] = 1;
        for j in 1..i+1 {
            dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
        }
    }

    for i in from..to+1 {
        let s = (k2 - k1 + 1) as usize;
        let t = (i - k1 + 1) as usize;
        ans += dp[s][t];
    }
    println!("{}", ave);
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