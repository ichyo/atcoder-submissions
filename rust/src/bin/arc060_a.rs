fn rec(
    x: &Vec<usize>,
    idx: usize,
    sum: usize,
    num: usize,
    memo: &mut HashMap<(usize, usize, usize), usize>,
    a: usize,
) -> usize {
    if memo.contains_key(&(idx, sum, num)) {
        return memo[&(idx, sum, num)];
    }
    let mut res = 0;
    if idx + 1 < x.len() {
        res += rec(x, idx + 1, sum, num, memo, a);
        res += rec(x, idx + 1, sum + x[idx], num + 1, memo, a);
    }
    if sum + x[idx] == (num + 1) * a {
        res += 1;
    }
    memo.insert((idx, sum, num), res);
    res
}
fn main() {
    let (n, a): (usize, usize) = readln();
    let x: Vec<usize> = readln();
    let mut memo = HashMap::new();
    let ans = rec(&x, 0, 0, 0, &mut memo, a);
    println!("{}", ans);
}

// --- template ---
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::{HashMap, HashSet, VecDeque};

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
