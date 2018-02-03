const MAX: usize = 4001;
fn main() {
    let (n, k): (usize, usize) = readln();
    let mut b = [[0i32; MAX]; MAX];
    let mut w = [[0i32; MAX]; MAX];
    for _ in 0..n {
        let (x, y, c): (usize, usize, String) = readln();
        let (bx, by) = (x % (2 * k), y % (2 * k));
        let (ex, ey) = (bx + k, by + k);
        if &c == "B" {
            b[by][bx] += 1;
            b[by][ex] -= 1;
            b[ey][bx] -= 1;
            b[ey][ex] += 1;
        } else {
            w[by][bx] += 1;
            w[by][ex] -= 1;
            w[ey][bx] -= 1;
            w[ey][ex] += 1;
        }
    }
    for y in 0..MAX {
        for x in 1..MAX {
            b[y][x] += b[y][x - 1];
            w[y][x] += w[y][x - 1];
        }
    }
    for y in 1..MAX {
        for x in 0..MAX {
            b[y][x] += b[y - 1][x];
            w[y][x] += w[y - 1][x];
        }
    }
    let mut ans = 0;
    for y in 0..2 * k {
        for x in 0..2 * k {
            let (bx, by) = (x, y);
            let (cx, cy) = ((x + k) % (2 * k), (y + k) % (2 * k));
            let mut s = 0;
            for b1 in &[0, 2 * k] {
                for b2 in &[0, 2 * k] {
                    s += w[by + b1][bx + b2];
                    s += w[cy + b1][cx + b2];
                    s += b[by + b1][cx + b2];
                    s += b[cy + b1][bx + b2];
                }
            }
            ans = max(ans, s);
        }
    }
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
