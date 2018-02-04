fn dfs(x: &Vec<i32>, i: usize, s: i32, res: String) -> Option<String> {
    if i == x.len() {
        if s == 7 {
            return Some(res + "=7");
        } else {
            return None;
        }
    } else {
        {
            let mut ns = res.clone();
            ns += "+";
            ns += &x[i].to_string();
            if let Some(r) = dfs(x, i + 1, s + x[i], ns) {
                return Some(r);
            }
        }
        {
            let mut ns = res.clone();
            ns += "-";
            ns += &x[i].to_string();
            if let Some(r) = dfs(x, i + 1, s - x[i], ns) {
                return Some(r);
            }
        }
    }
    None
}
fn main() {
    let s: Vec<char> = readln();
    let x: Vec<i32> = s.iter().map(|&x| (x as u8 - '0' as u8) as i32).collect();

    let ans = dfs(&x, 1, x[0], x[0].to_string()).unwrap();
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
