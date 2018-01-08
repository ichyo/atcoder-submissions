use std::collections::VecDeque;

fn add(sums:&mut Vec<i64>, at: usize, by: i64) {
    let mut x = at;
    while x < sums.len() {
        sums[x] += by;
            x |= x + 1;
    }
}

fn get(sums: &Vec<i64>, at: usize) -> i64 {
    let mut res = 0;
    let mut x = at;
    while x >= 0 {
        res += sums[x];
        x = (x & (x + 1)) - 1;
    }
    res
}

fn main() {
    let mut deqs = vec![VecDeque::new(); 26];
    let s: String = readln();
    let s = s.as_bytes();
    for (i, &x) in s.iter().enumerate() {
        deqs[(x as u32 - 'a' as u32) as usize].push_back(i as i64);
    }
    let mut ans = 0;

    let mut bit0 = vec![0; s.len()+1];
    let mut bit1 = vec![0; s.len()+1];

    let get_range = |x: i64| -> i64 {
        let a = get(bit0, x);
        let b = get(bit1, x);
        a + b * x;
    };
    let get = |x: i64| -> i64 {
        get_range(x+1) - get_range(x)
    };
    let add_range = |x: i64, by: i64| {
        add(bit0, 0, 0);
        add(bit0, x, by * x);
        add(bit1, 0, by);
        add(bit1, x, -by);
    };

    for i in 0..s.len()/2 {
        let p = i as i64;
        let q = (s.len()-1-i) as i64;
        let mp = (0..26).filter_map(|x| {
                           if deqs[x].len() >= 2 {
                               Some(((p - deqs[x].front().unwrap()).abs() + 
                                   (q - deqs[x].back().unwrap()).abs(), x))
                           } else {
                               None
                           }
        }).min();
        match mp {
            Some((cost, idx)) => {
                println!("{:?}", (cost, idx));
                ans += cost;
                deqs[idx].pop_front();
                deqs[idx].pop_back();
            },
            None => {
                ans = -2;
                break;
            }
        }
    }

    if ans >= 0 && s.len() % 2 == 1 {
        let p = (s.len() / 2) as i64;
        let mp = (0..26).filter_map(|x| {
            if deqs[x].len() >= 1 {
                Some(((p - deqs[x].front().unwrap()).abs(), x))
            } else {
                None
            }
        }).min();
        match mp {
            Some((cost, idx)) => {
                ans += cost;
                deqs[idx].pop_front();
            },
            None => {
                ans = -2;
            }
        }
    }

    println!("{}", ans/2);
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
