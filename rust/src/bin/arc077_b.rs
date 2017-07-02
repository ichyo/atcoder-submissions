const MAX_P: usize = 100010;
const MOD: i64 = 1_000_000_007;

struct Comb {
    inv: [i64; MAX_P],
    fact: [i64; MAX_P],
    rfact: [i64; MAX_P]
}

impl Comb {
    fn new() -> Self {
        Comb {
            inv: [0; MAX_P],
            fact: [0; MAX_P],
            rfact: [0; MAX_P]
        }
    }

    fn calc(&mut self) {
        self.inv[1] = 1;
        for i in 2..MAX_P as i64 {
            self.inv[i as usize] = self.inv[(MOD % i) as usize] * (MOD - MOD / i) % MOD;
        }
        self.fact[0] = 1;
        self.rfact[0] = 1;
        for i in 1..MAX_P as i64 {
            self.fact[i as usize] = (self.fact[(i - 1) as usize] * i) % MOD;
            self.rfact[i as usize] = (self.rfact[(i - 1) as usize] * self.inv[i as usize]) % MOD;
        }
    }

    fn comb(&self, n: usize, k: usize) -> i64 {
        if n < k {
            0
        } else {
            ((self.fact[n] * self.rfact[n - k]) % MOD) * self.rfact[k] % MOD
        }
    }
}


fn find_dist(a: Vec<i64>) -> i64 {
    let mut s = HashMap::new();
    for (i, x) in a.iter().enumerate() {
        if s.contains_key(x) {
            return (i - s.get(x).unwrap()) as i64;
        } else {
            s.insert(x, i);
        }
    }
    panic!("no reach")
}

use std::ops::*;


#[derive(Debug, Copy, Clone, Eq)]
struct Mint {
    val: u32
}

impl Mint {
    fn inv(self) -> Mint {
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
            val: if u < 0 { u + MOD as i32 } else { u } as u32
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
                let t = x as i64 % MOD;
                if x >= 0 {
                    Mint{ val: t as u32 }
                } else {
                    Mint{ val: (MOD + t) as u32 }
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

impl<T: Into<Mint>> Add<T> for Mint {
    type Output = Mint;

    fn add(self, other: T) -> Mint {
        let nval = self.val + other.into().val;
        let lmod = MOD as u32;
        Mint {
            val: if nval >= lmod { nval - lmod } else { nval }
        }
    }
}

impl<T: Into<Mint>> AddAssign<T> for Mint {
    fn add_assign(&mut self, other: T) {
        *self = *self + other.into();
    }
}

impl<T: Into<Mint>> Sub<T> for Mint {
    type Output = Mint;

    fn sub(self, other: T) -> Mint {
        let nval = self.val + MOD as u32 - other.into().val;
        let lmod = MOD as u32;
        Mint {
            val: if nval >= lmod { nval - lmod } else { nval }
        }
    }
}

impl<T: Into<Mint>> SubAssign<T> for Mint {
    fn sub_assign(&mut self, other: T) {
        *self = *self - other.into();
    }
}

impl<T: Into<Mint>> Mul<T> for Mint {
    type Output = Mint;

    fn mul(self, other: T) -> Mint {
        let nval = self.val as u64 * other.into().val as u64;
        Mint {
            val: (nval % (MOD as u64)) as u32
        }
    }
}

impl<T: Into<Mint>> MulAssign<T> for Mint {
    fn mul_assign(&mut self, other: T) {
        *self = *self * other.into();
    }
}

impl<T: Into<Mint>> Div<T> for Mint {
    type Output = Mint;

    fn div(self, other: T) -> Mint {
        self * other.into().inv()
    }
}

impl<T: Into<Mint>> DivAssign<T> for Mint {
    fn div_assign(&mut self, other: T) {
        *self = *self / other.into();
    }
}

fn main() {
    let mut comb = Comb::new();
    comb.calc();

    let n: usize = readln();
    let a: Vec<i64> = readln();
    let l = find_dist(a);
    //println!("l: {}", l);

    for k in 1..n+1 {
        let mut ans: Mint = 0.into();
        ans += comb.comb(n, k);
        if k >= 2 {
            ans += comb.comb(n-1, k-1);
            if n > l as usize {
                ans -= comb.comb(n-1-(l-1) as usize, k-1);
            }
            ans += comb.comb(n-1, k-2);
            //println!("l, n, k: {} {} {} -> {}", l-1, n-1, k-2, comb.comb(n-1, k-2));
        }
        println!("{}", ans);
    }
    println!("1");
}

// --- template ---
#[allow(unused_imports)]
use std::cmp::{max, min};
#[allow(unused_imports)]
use std::collections::HashMap;

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