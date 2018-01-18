fn main() {
    let n = readln();
    let x: Vec<i32> = readln();
    let a: Vec<i32> = readln();
    let mut cs: Vec<Vec<usize>> = vec![Vec::new(); n];
    for i in 1..n {
        cs[ (a[(i-1) as usize]-1) as usize ].push(i);
    }
}

// --- template ---
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::{HashSet, BTreeMap};

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

pub trait Permutation {
    fn next_permutation(&mut self) -> bool;
    fn prev_permutation(&mut self) -> bool;
}

impl<T> Permutation for [T]
where
    T: Ord,
{
    fn next_permutation(&mut self) -> bool {
        if self.len() <= 1 {
            return false;
        }

        let mut i = self.len() - 1;
        while i > 0 && self[i - 1] >= self[i] {
            i -= 1;
        }

        if i == 0 {
            return false;
        }

        let mut j = self.len() - 1;
        while self[j] <= self[i - 1] {
            j -= 1;
        }

        self.swap(j, i - 1);

        self[i..].reverse();

        true
    }

    fn prev_permutation(&mut self) -> bool {
        if self.len() <= 1 {
            return false;
        }

        let mut i = self.len() - 1;
        while i > 0 && self[i - 1] <= self[i] {
            i -= 1;
        }

        if i == 0 {
            return false;
        }

        self[i..].reverse();

        let mut j = self.len() - 1;
        while self[j - 1] < self[i - 1] {
            j -= 1;
        }

        self.swap(i - 1, j);

        true
    }
}
