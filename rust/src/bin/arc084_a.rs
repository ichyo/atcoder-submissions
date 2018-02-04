fn calc(a: &Vec<i64>, b: &Vec<i64>, t: &Vec<i64>) -> Vec<i64> {
    let n = a.len();
    let mut res = vec![0; n + 1];
    let mut ways = 0;
    let mut idx = n;
    for i in (0..n).rev() {
        while idx != 0 && b[idx - 1] > a[i] {
            idx -= 1;
            ways += t[idx];
        }
        res[i] = ways;
    }
    res
}
fn main() {
    let n: usize = readln();
    let mut a: Vec<i64> = readln();
    a.sort();
    let mut b: Vec<i64> = readln();
    b.sort();
    let mut c: Vec<i64> = readln();
    c.sort();
    let r = vec![1; n + 1];
    let q = calc(&b, &c, &r);
    let p = calc(&a, &b, &q);
    let ans = p.iter().sum::<i64>();
    println!("{}", ans);
}

// --- template ---
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::{HashMap, HashSet};

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
    for _ in 0..n {
        vs.push(readln());
    }
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
fromln_primitives!(
    String,
    bool,
    f32,
    f64,
    isize,
    i8,
    i16,
    i32,
    i64,
    usize,
    u8,
    u16,
    u32,
    u64
);
impl<T> FromLn for Vec<T>
where
    T: FromLn,
{
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
