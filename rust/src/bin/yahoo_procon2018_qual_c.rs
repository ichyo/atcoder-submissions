/*
fn dfs(
    ng: u32,
    used: u32,
    cur: usize,
    xs: &Vec<u64>,
    cs: &Vec<u64>,
    vs: &Vec<u64>,
    memo: &mut HashMap<(u32, u32), u64>,
) -> u64 {
    let n = xs.len();
    if cur == n || cur == 6 {
        return 0;
    }

    if memo.contains_key(&(ng, used)) {
        return memo[&(ng, used)];
    }

    let mut rest = 0;
    for i in 0..cur {
        rest += xs[i];
    }
    let mut res = 0;
    for i in 0..n {
        if (used >> i & 1) == 1 {
            rest -= cs[i];
        }
    }

    for i in 0..n {
        if (used >> i & 1) == 0 && (ng >> i & 1) == 0 && rest >= cs[i] {
            res = max(res, vs[i] + dfs(ng, used | (1 << i), cur, xs, cs, vs, memo));
        }
    }

    let mut next = u64::max_value();
    for i in 0..n {
        if (ng >> i & 1) == 0 && (used >> i & 1) == 0 {
            next = min(next, dfs(ng | (1 << i), used, cur + 1, xs, cs, vs, memo));
        }
    }
    if next == u64::max_value() {
        next = 0;
    }

    res = max(res, next);
    memo.insert((ng, used), res);

    return res;
}
*/

fn main() {
    let n: usize = readln();
    let x: Vec<u64> = readln();
    let c: Vec<u64> = readln();
    let v: Vec<u64> = readln();
    let ways = 1u64 << n;
    let mask = ways - 1;
    let mut vs = Vec::new();
    for s in 0..ways {
        let mut costs = 0;
        let mut values = 0;
        for i in 0..n {
            if (s >> i & 1) == 1 {
                costs += c[i];
                values += v[i];
            }
        }
        vs.push((values, costs, s));
    }
    vs.sort();
    vs.reverse();
    let mut answer = 0;

    let mut maxcost = 0;
    for i in 0..n {
        maxcost += x[i];
        let mut dp = vec![0; ways as usize];
        for &(values, costs, bit) in &vs {
            if costs <= maxcost {
                let inv = (!bit) & mask;
                dp[inv as usize] = max(dp[inv as usize], values);
            }
        }

        for s in (0..ways).rev() {
            for i in 0..n {
                let ns = (s & (mask ^ (1 << i))) as usize;
                dp[ns] = max(dp[ns], dp[s as usize]);
            }
        }

        let mut localans = u64::max_value();
        for s in (0..ways) {
            if s.count_ones() == (i + 1) as u32 {
                localans = min(localans, dp[s as usize]);
            }
        }

        //println!("{}", localans);
        answer = max(answer, localans);
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
