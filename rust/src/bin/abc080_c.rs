fn main() {
    let n: usize = readln();
    let mut opens = Vec::new();
    for i in 0..n {
        let v: Vec<i32> = readln();
        let open = v.into_iter().fold(0, |acc, x| (acc << 1) | x);
        opens.push(open);
    }

    let costs: Vec<Vec<i64>> = readlns(n);

    let ans = (1..(1 << 10))
        .map(|s| {
            opens
                .iter()
                .zip(costs.iter())
                .map(|(o, c)| {
                    let i = (s & o).count_ones() as usize;
                    c[i]
                })
                .sum::<i64>()
        })
        .max()
        .unwrap();

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
