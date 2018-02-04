fn calc(s: &Vec<char>, t: &Vec<char>, base: usize) -> Option<String> {
    let mut ns = s.clone();
    for i in 0..t.len() {
        if s[i + base] != '?' && s[i + base] != t[i] {
            return None;
        }
    }
    for i in 0..t.len() {
        if ns[i + base] == '?' {
            ns[i + base] = t[i];
        }
    }
    for i in 0..ns.len() {
        if ns[i] == '?' {
            ns[i] = 'a';
        }
    }
    Some(ns.into_iter().collect::<String>())
}
fn main() {
    let s: Vec<char> = readln();
    let t: Vec<char> = readln();
    let n = (s.len() - t.len() + 1);
    let ans = (0..n)
        .filter_map(|i| calc(&s, &t, i))
        .min()
        .unwrap_or("UNRESTORABLE".to_string());
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
