use std::cmp::Ordering;
use std::collections::BinaryHeap;
use std::usize;

#[derive(Copy, Clone, Eq, PartialEq)]
struct State {
    cost: usize,
    position: usize,
}

// The priority queue depends on `Ord`.
// Explicitly implement the trait so the queue becomes a min-heap
// instead of a max-heap.
impl Ord for State {
    fn cmp(&self, other: &State) -> Ordering {
        // Notice that the we flip the ordering on costs.
        // In case of a tie we compare positions - this step is necessary
        // to make implementations of `PartialEq` and `Ord` consistent.

        let ord = other.cost.cmp(&self.cost);
        match ord {
            Ordering::Equal => self.position.cmp(&other.position),
            _ => ord,
        }
    }
}

// `PartialOrd` needs to be implemented as well.
impl PartialOrd for State {
    fn partial_cmp(&self, other: &State) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

// Each node is represented as an `usize`, for a shorter implementation.
#[derive(Copy, Clone)]
struct Edge {
    node: usize,
    cost: usize,
}

// Dijkstra's shortest path algorithm.

// Start at `start` and use `dist` to track the current shortest distance
// to each node. This implementation isn't memory-efficient as it may leave duplicate
// nodes in the queue. It also uses `usize::MAX` as a sentinel value,
// for a simpler implementation.
fn shortest_path(adj_list: &Vec<Vec<Edge>>, start: usize, goal: usize) -> Vec<usize> {
    // dist[node] = current shortest distance from `start` to `node`
    let mut dist: Vec<_> = (0..adj_list.len()).map(|_| usize::MAX / 2).collect();

    let mut heap = BinaryHeap::new();

    // We're at `start`, with a zero cost
    dist[start] = 0;
    heap.push(State {
        cost: 0,
        position: start,
    });

    // Examine the frontier with lower cost nodes first (min-heap)
    while let Some(State { cost, position }) = heap.pop() {
        // Alternatively we could have continued to find all shortest paths
        if position == goal {
            break;
        }

        // Important as we may have already found a better way
        if cost > dist[position] {
            continue;
        }

        // For each node we can reach, see if we can find a way with
        // a lower cost going through this node
        for edge in &adj_list[position] {
            let next = State {
                cost: cost + edge.cost,
                position: edge.node,
            };

            // If so, add it to the frontier and continue
            if next.cost < dist[next.position] {
                heap.push(next);
                // Relaxation, we have now found a better way
                dist[next.position] = next.cost;
            }
        }
    }

    dist
}

fn main() {
    let (n, m) = readln();
    let (mut s, mut t) = readln();
    s -= 1;
    t -= 1;
    let mut graph: Vec<Vec<Edge>> = vec![Vec::new(); n];
    for _ in 0..m {
        let (mut u, mut v, d): (usize, usize, usize) = readln();
        u -= 1;
        v -= 1;
        graph[u].push(Edge { node: v, cost: d });
        graph[v].push(Edge { node: u, cost: d });
    }

    let dist = shortest_path(&graph, s, t);
    let mut vs: Vec<usize> = (0..n).filter(|x| dist[*x] <= dist[t]).collect();
    vs.sort_by_key(|x| dist[*x]);
    let mut dps: Vec<Mint> = vec![0.into(); n];
    dps[s] = 1.into();
    for &x in &vs {
        for &e in &graph[x] {
            let (y, c) = (e.node, e.cost);
            if dist[x] + c == dist[y] {
                dps[y] += dps[x];
            }
        }
    }

    let mut dpt: Vec<Mint> = vec![0.into(); n];
    dpt[t] = 1.into();
    for &x in vs.iter().rev() {
        for &e in &graph[x] {
            let (y, c) = (e.node, e.cost);
            if dist[x] - c == dist[y] {
                dpt[y] += dpt[x];
            }
        }
    }
    assert!(dps[t] == dpt[s]);
    let mut ans = dps[t] * dpt[s];

    let total_dist = dist[t];

    // node
    for &x in &vs {
        if dist[x] * 2 == total_dist {
            ans -= (dps[x] * dpt[x]) * (dps[x] * dpt[x]);
        }
    }

    // edge
    for &x in &vs {
        for &e in &graph[x] {
            let (y, c) = (e.node, e.cost);
            if dist[x] * 2 < total_dist && dist[y] * 2 > total_dist && dist[x] + c == dist[y] {
                ans -= (dps[x] * dpt[y]) * (dps[x] * dpt[y]);
            }
        }
    }

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

pub const MOD: u32 = 1_000_000_007;

//TODO: It has to be generics on MOD value.
//TODO: https://github.com/rust-lang/rust/issues/44580 may be releated
#[derive(Debug, Copy, Clone, Eq)]
pub struct Mint {
    val: u32,
}

impl<T: Into<Mint>> std::ops::Add<T> for Mint {
    type Output = Mint;

    fn add(self, other: T) -> Mint {
        let nval = self.val + other.into().val;
        Mint {
            val: if nval >= MOD { nval - MOD } else { nval },
        }
    }
}

impl<T: Into<Mint>> std::ops::Sub<T> for Mint {
    type Output = Mint;

    fn sub(self, other: T) -> Mint {
        let nval = self.val + MOD - other.into().val;
        Mint {
            val: if nval >= MOD { nval - MOD } else { nval },
        }
    }
}

impl<T: Into<Mint>> std::ops::Mul<T> for Mint {
    type Output = Mint;

    fn mul(self, other: T) -> Mint {
        let nval = self.val as u64 * other.into().val as u64;
        Mint {
            val: (nval % (MOD as u64)) as u32,
        }
    }
}

impl<T: Into<Mint>> std::ops::Div<T> for Mint {
    type Output = Mint;

    fn div(self, other: T) -> Mint {
        self * other.into().inv()
    }
}

impl Mint {
    pub fn inv(self) -> Mint {
        let mut a = self.val as i32;
        let mut b = MOD as i32;
        let mut u = 1 as i32;
        let mut v = 0 as i32;
        while b != 0 {
            let t = a / b;
            a -= t * b;
            std::mem::swap(&mut a, &mut b);
            u -= t * v;
            std::mem::swap(&mut u, &mut v);
        }
        Mint {
            val: if u < 0 { u + MOD as i32 } else { u } as u32,
        }
    }
}

impl PartialEq for Mint {
    fn eq(&self, other: &Mint) -> bool {
        self.val == other.val
    }
}

impl std::fmt::Display for Mint {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        self.val.fmt(f)
    }
}

macro_rules! impl_signed_mint {
    ($($t:ty)*) => ($(
        impl From<$t> for Mint {
            #[inline]
            fn from(x: $t) -> Mint {
                let t = (x as i64) % (MOD as i64);
                if x >= 0 {
                    Mint{ val: t as u32 }
                } else {
                    Mint{ val: (MOD as i64 + t) as u32 }
                }
            }
        }
    )*)
}

macro_rules! impl_unsigned_mint {
    ($($t:ty)*) => ($(
        impl From<$t> for Mint {
            #[inline]
            fn from(x: $t) -> Mint {
                let t = x as u64 % MOD as u64;
                Mint{ val: t as u32 }
            }
        }
    )*)
}

impl_signed_mint! { i8 i16 i32 i64 isize }
impl_unsigned_mint! { u8 u16 u32 u64 usize }

impl<T: Into<Mint>> std::ops::AddAssign<T> for Mint {
    fn add_assign(&mut self, other: T) {
        *self = *self + other.into();
    }
}

impl<T: Into<Mint>> std::ops::SubAssign<T> for Mint {
    fn sub_assign(&mut self, other: T) {
        *self = *self - other.into();
    }
}

impl<T: Into<Mint>> std::ops::MulAssign<T> for Mint {
    fn mul_assign(&mut self, other: T) {
        *self = *self * other.into();
    }
}

impl<T: Into<Mint>> std::ops::DivAssign<T> for Mint {
    fn div_assign(&mut self, other: T) {
        *self = *self / other.into();
    }
}
