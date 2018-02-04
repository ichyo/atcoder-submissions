fn is_connect(graph: &Vec<Vec<usize>>, a: usize, b: usize) -> bool {
    let n = graph.len();
    let mut queue = VecDeque::new();
    let mut used = vec![false; n];
    queue.push_back(0);
    used[0] = true;
    while let Some(cur) = queue.pop_front() {
        for &next in &graph[cur] {
            if (a, b) == (cur, next) || (b, a) == (cur, next) {
                continue;
            }
            if used[next] {
                continue;
            }
            used[next] = true;
            queue.push_back(next);
        }
    }
    used.into_iter().all(|b| b)
}

fn main() {
    let (n, m): (usize, usize) = readln();
    let mut graph = vec![Vec::new(); n];
    for i in 0..m {
        let (mut a, mut b): (usize, usize) = readln();
        a -= 1;
        b -= 1;
        graph[a].push(b);
        graph[b].push(a);
    }

    let mut answer = 0;
    for u in 0..n {
        for &v in &graph[u] {
            if u < v && !is_connect(&graph, u, v) {
                answer += 1;
            }
        }
    }
    println!("{}", answer);
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
