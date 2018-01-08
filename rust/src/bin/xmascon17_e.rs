struct Memo([[Option<bool>; 1010]; 1010]);
fn solve(i: usize, j: usize, s: &Vec<char>, t: &Vec<char>, memo: &mut Memo) -> bool {
    if let Some(v) = memo.0[i][j] {
        return v;
    }
    if i == s.len() && j == t.len() {
        memo.0[i][j] = Some(true);
        return memo.0[i][j].unwrap();
    }
    if i < s.len() && j < t.len() && s[i] == t[j] && solve(i + 1, j + 1, s, t, memo) {
        memo.0[i][j] = Some(true);
        return memo.0[i][j].unwrap();
    }
    if i < s.len() && s[i] == 'A' && solve(i + 1, j, s, t, memo) {
        memo.0[i][j] = Some(true);
        return memo.0[i][j].unwrap();
    }
    if j < t.len() && t[j] == 'B' && solve(i, j + 1, s, t, memo) {
        memo.0[i][j] = Some(true);
        return memo.0[i][j].unwrap();
    }
    memo.0[i][j] = Some(false);
    return memo.0[i][j].unwrap();
}

fn main() {
    let s: String = readln();
    let t: String = readln();
    let s = s.chars().collect();
    let t = t.chars().collect();
    let mut memo = Memo([[None; 1010]; 1010]);
    let ans = if solve(0, 0, &s, &t, &mut memo) {
        "YES"
    } else {
        "NO"
    };
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
