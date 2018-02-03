fn visit(
    g: &Vec<Vec<usize>>,
    v: usize,
    scc: &mut Vec<Vec<usize>>,
    stk: &mut Vec<usize>,
    inS: &mut Vec<bool>,
    low: &mut Vec<i32>,
    num: &mut Vec<i32>,
    time: &mut i32,
) {
    *time += 1;
    low[v] = *time;
    num[v] = *time;
    stk.push(v);
    inS[v] = true;
    for &w in &g[v] {
        if num[w] == 0 {
            visit(g, w, scc, stk, inS, low, num, time);
            low[v] = min(low[v], low[w]);
        } else if inS[w] {
            low[v] = min(low[v], num[w]);
        }
    }
    if low[v] == num[v] {
        let mut ls = Vec::new();
        loop {
            let w = stk.pop().unwrap();
            inS[w] = false;
            ls.push(w);
            if v == w {
                break;
            }
        }
        scc.push(ls);
    }
}
fn scc(g: &Vec<Vec<usize>>, mut sc: &mut Vec<Vec<usize>>) {
    let n = g.len();
    let mut num = vec![0i32; n];
    let mut low = vec![0i32; n];
    let mut stk: Vec<usize> = Vec::new();
    let mut inS = vec![false; n];
    let mut time = 0;
    for u in 0..n {
        if num[u] == 0 {
            visit(
                g,
                u,
                &mut sc,
                &mut stk,
                &mut inS,
                &mut low,
                &mut num,
                &mut time,
            );
        }
    }
}
fn main() {
    let (n, m) = readln();
    let mut edges: Vec<(usize, usize, i64)> = Vec::new();
    let mut g: Vec<Vec<usize>> = vec![Vec::new(); n];
    let mut bg: Vec<Vec<usize>> = vec![Vec::new(); n];
    for i in 0..m {
        let (x, y, d): (usize, usize, i64) = readln();
        edges.push((x - 1, y - 1, d));
        g[x - 1].push(y - 1);
        bg[y - 1].push(x - 1);
    }
    let mut sc = Vec::new();
    scc(&g, &mut sc);
    let mut group = vec![0; n];
    for (i, ref v) in sc.iter().enumerate() {
        for x in *v {
            group[*x as usize] = i;
        }
    }

    let answer = if edges
        .iter()
        .any(|&(x, y, d)| group[x] == group[y] && d != 0)
    {
        "No"
    } else {
        let mut solve = || {
            let t = group.len();
            let mut dp = vec![None; t];
            let mut used = vec![false; t];
            for i in 0..t {
                if !used[i] {
                    used[i] = true;
                    dp[i] = Some(0);
                    let mut que: VecDeque<usize> = VecDeque::new();
                    for &x in &sc[i] {
                        que.push_back(x);
                    }
                    while let Some(e) = que.pop_front() {
                        for &y in &g[e] {
                            let gy = group[y];
                            if !used[gy] {
                                used[gy] = true;
                                for &x in &sc[gy] {
                                    que.push_back(x);
                                }
                            }
                        }
                        for &y in &bg[e] {
                            let gy = group[y];
                            if !used[gy] {
                                used[gy] = true;
                                for &x in &sc[gy] {
                                    que.push_back(x);
                                }
                            }
                        }
                    }
                }
            }
            edges.sort_by_key(|&(x, _, _)| group[x]);
            let mut rest = Vec::new();
            rest.append(&mut edges);
            loop {
                let mut nrest = Vec::new();
                if rest.len() == 0 {
                    break;
                }
                for &(x, y, d) in &rest {
                    let gx = group[x];
                    let gy = group[y];
                    match (dp[gx], dp[gy]) {
                        (Some(l), Some(r)) => {
                            if l + d != r {
                                return "No";
                            }
                        }
                        (None, Some(r)) => {
                            dp[gx] = Some(r - d);
                        }
                        (Some(l), None) => {
                            dp[gy] = Some(l + d);
                        }
                        (None, None) => {
                            nrest.push((x, y, d));
                        }
                    }
                }
                rest.clear();
                rest.append(&mut nrest);
            }
            "Yes"
        };
        solve()
    };
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
