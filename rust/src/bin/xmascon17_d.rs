fn simulate(n: i64, k: i64, m: i64) -> u32 {
}

fn main() {
    let (n, k, m): (i64, i64, i64) = readln();
    let ans = if n >= k {
    } else {
        simulate(n, k, m)
    }
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

pub const MOD: i64 = 1_000_000_007;

#[derive(Debug, Copy, Clone, Eq)]
pub struct Mint {
    val: u32
}

impl<T: Into<Mint>> std::ops::Add<T> for Mint {
    type Output = Mint;

    fn add(self, other: T) -> Mint {
        let nval = self.val + other.into().val;
        let lmod = MOD as u32;
        Mint {
            val: if nval >= lmod { nval - lmod } else { nval }
        }
    }
}

impl<T: Into<Mint>> std::ops::Sub<T> for Mint {
    type Output = Mint;

    fn sub(self, other: T) -> Mint {
        let nval = self.val + MOD as u32 - other.into().val;
        let lmod = MOD as u32;
        Mint {
            val: if nval >= lmod { nval - lmod } else { nval }
        }
    }
}

impl<T: Into<Mint>> std::ops::Mul<T> for Mint {
    type Output = Mint;

    fn mul(self, other: T) -> Mint {
        let nval = self.val as u64 * other.into().val as u64;
        Mint {
            val: (nval % (MOD as u64)) as u32
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

pub struct Comb {
    fact: Vec<Mint>,
    factinv: Vec<Mint>
}

impl Comb {
    pub fn new(n: usize) -> Comb {
        let mut fact: Vec<Mint> = vec![0.into(); n+1];
        let mut factinv: Vec<Mint> = vec![0.into(); n+1];
        fact[0] = 1.into();
        for i in 0..n {
            fact[i+1] = fact[i] * (i+1);
        }
        factinv[n] = fact[n].inv();
        for i in (0..n).rev() {
            factinv[i] = factinv[i+1] * (i+1);
        }
        Comb {
            fact: fact,
            factinv: factinv
        }
    }

    fn fact(&self, n: u64) -> Mint {
        self.fact[n as usize]
    }

    #[allow(non_snake_case)]
    pub fn nPr(&self, n: i64, r: i64) -> Mint {
        if n >= r {
            self.fact[n as usize] * self.factinv[(n - r) as usize]
        } else {
            0.into()
        }
    }

    #[allow(non_snake_case)]
    pub fn nCr(&self, n: i64, r: i64) -> Mint {
        if n >= MOD {
            self.nCr(n % MOD, r % MOD) * self.nCr(n / MOD, r / MOD) // Lucas' theorem
        } else if n >= r {
            self.fact[n as usize] * self.factinv[(n-r) as usize] * self.factinv[r as usize]
        } else {
            0.into()
        }
    }

    #[allow(non_snake_case)]
    pub fn nHr(&self, n: i64, r: i64) -> Mint {
        if r == 0 {
            1.into()
        } else {
            self.nCr(n+r-1, r)
        }
    }
}
