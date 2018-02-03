fn grundy(mut level: usize) -> i64 {
    assert!(level != 0);
    let mut res = 1;
    while level & 1 == 0 {
        level >>= 1;
        res += 1;
    }
    res
}

struct Node {
    next: (Option<usize>, Option<usize>),
}

impl Node {
    fn new() -> Node {
        Node { next: (None, None) }
    }
}

fn add(v: &Vec<char>, trie: &mut Vec<Node>) {
    let mut cur = 0;
    for c in v {
        let next = match *c {
            '0' => trie[cur].next.0,
            '1' => trie[cur].next.1,
            _ => panic!(),
        };
        let next = match next {
            Some(idx) => idx,
            None => {
                trie.push(Node::new());
                trie.len() - 1
            }
        };
        match *c {
            '0' => trie[cur].next.0 = Some(next),
            '1' => trie[cur].next.1 = Some(next),
            _ => panic!(),
        };
        cur = next;
    }
}

fn dfs(cur: usize, l: usize, trie: &Vec<Node>) -> i64 {
    if l >= 1 {
        match trie[cur].next {
            (Some(left), Some(right)) => dfs(left, l - 1, trie) ^ dfs(right, l - 1, trie),
            (Some(left), None) => dfs(left, l - 1, trie) ^ grundy(l),
            (None, Some(right)) => grundy(l) ^ dfs(right, l - 1, trie),
            (None, None) => 0,
        }
    } else {
        0
    }
}

fn main() {
    let (n, l): (usize, usize) = readln();
    let v: Vec<Vec<char>> = readlns(n);

    let mut trie = vec![Node::new()];
    for s in &v {
        add(s, &mut trie);
    }

    let grundy = dfs(0, l, &trie);
    if grundy == 0 {
        println!("Bob");
    } else {
        println!("Alice");
    }
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
