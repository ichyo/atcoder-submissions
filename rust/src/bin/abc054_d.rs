fn get_min(cur: Option<u64>, next: u64) -> u64 {
    match cur {
        Some(x) => min(x, next),
        None => next
    }
}
fn main() {
    let (n, ma, mb): (usize, usize, usize) = readln();
    let mut a = Vec::new();
    let mut b = Vec::new();
    let mut c = Vec::new();
    for _ in 0..n {
        let (x, y, z): (usize, usize, u64) = readln();
        a.push(x);
        b.push(y);
        c.push(z);
    }
    const MAX: usize = 404;
    let mut dp = [[None; MAX]; MAX];
    dp[0][0] = Some(0 as u64);
    for k in 0..n {
        let x = a[k];
        let y = b[k];
        let z = c[k];
        let mut next = [[None; MAX]; MAX];
        for i in 0..MAX {
            for j in 0..MAX {
                if let Some(val) = dp[i][j] {
                    next[i][j] = Some(get_min(next[i][j], val));
                    let ni = i + x;
                    let nj = j + y;
                    let nval = val + z;
                    next[ni][nj] = Some(get_min(next[ni][nj], nval));
                }
            }
        }
        dp = next;
    }
    let mut answer: u64 = u64::max_value();
    for i in 0..MAX {
        for j in 0..MAX {
            if i * mb == j * ma && i != 0 && j != 0 {
                if let Some(val) = dp[i][j] {
                    answer = min(answer, val);
                }
            }
        }
    }
    if answer == u64::max_value() {
        println!("-1");
    } else {
        println!("{}", answer);
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