static DX: [isize; 4] = [0, 1, 0, -1];
static DY: [isize; 4] = [1, 0, -1, 0];

fn main() {
    let (h, w): (usize, usize) = readln();
    let grid: Vec<Vec<char>> = readlns(h);
    let mut dist = vec![vec![-1; w]; h];
    let mut queue = VecDeque::new();
    dist[0][0] = 1;
    queue.push_back((0, 0));
    while let Some((x, y)) = queue.pop_front() {
        for r in 0..4 {
            let nx = x as isize + DX[r];
            let ny = y as isize + DY[r];
            if nx >= 0 && nx < w as isize && ny >= 0 && ny < h as isize {
                let nx = nx as usize;
                let ny = ny as usize;
                if grid[ny][nx] != '#' && dist[ny][nx] == -1 {
                    dist[ny][nx] = dist[y][x] + 1;
                    queue.push_back((nx, ny));
                }
            }
        }
    }
    if dist[h - 1][w - 1] != -1 {
        let count: usize = grid.iter()
            .map(|row| row.iter().filter(|&&c| c == '.').count())
            .sum::<usize>();
        println!("{}", count as isize - dist[h - 1][w - 1]);
    } else {
        println!("-1");
    }
}

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
mod comp {
    pub mod math {
        pub mod comb {
            use super::mint::{Mint, MOD};
            pub struct Comb {
                fact: Vec<Mint>,
                factinv: Vec<Mint>,
            }
            impl Comb {
                pub fn new(n: usize) -> Comb {
                    let mut fact: Vec<Mint> = vec![0.into(); n + 1];
                    let mut factinv: Vec<Mint> = vec![0.into(); n + 1];
                    fact[0] = 1.into();
                    for i in 0..n {
                        fact[i + 1] = fact[i] * (i + 1);
                    }
                    factinv[n] = fact[n].inv();
                    for i in (0..n).rev() {
                        factinv[i] = factinv[i + 1] * (i + 1);
                    }
                    Comb {
                        fact: fact,
                        factinv: factinv,
                    }
                }
                pub fn fact(&self, n: u64) -> Mint {
                    if let Some(x) = self.fact.get(n as usize) {
                        *x
                    } else if n >= MOD as u64 {
                        Mint::from(0)
                    } else {
                        let base = 1000000;
                        let p = n / base;
                        let mut res = PRECALC_FACT[p as usize].into();
                        for a in (p * base + 1)..(n + 1) {
                            res *= a;
                        }
                        res
                    }
                }
                pub fn factinv(&self, n: u64) -> Mint {
                    if let Some(x) = self.factinv.get(n as usize) {
                        *x
                    } else {
                        self.fact(n).inv()
                    }
                }
                pub fn perm(&self, n: u64, r: u64) -> Mint {
                    if n >= r {
                        self.fact(n) * self.factinv((n - r) as u64)
                    } else {
                        0.into()
                    }
                }
                pub fn comb(&self, n: u64, r: u64) -> Mint {
                    let m = MOD as u64;
                    if n >= m {
                        self.comb(n % m, r % m) * self.comb(n / m, r / m)
                    } else if n >= r {
                        self.fact(n) * self.factinv(n - r) * self.factinv(r)
                    } else {
                        Mint::from(0)
                    }
                }
                pub fn multi_comb(&self, n: u64, r: u64) -> Mint {
                    if r == 0 {
                        Mint::from(1)
                    } else {
                        self.comb(n + r - 1, r)
                    }
                }
            }
            static PRECALC_FACT: &'static [u32] = &[
                1, 641102369, 578095319, 5832229, 259081142, 974067448, 316220877, 690120224,
                251368199, 980250487, 682498929, 134623568, 95936601, 933097914, 167332441,
                598816162, 336060741, 248744620, 626497524, 288843364, 491101308, 245341950,
                565768255, 246899319, 968999, 586350670, 638587686, 881746146, 19426633, 850500036,
                76479948, 268124147, 842267748, 886294336, 485348706, 463847391, 544075857,
                898187927, 798967520, 82926604, 723816384, 156530778, 721996174, 299085602,
                323604647, 172827403, 398699886, 530389102, 294587621, 813805606, 67347853,
                497478507, 196447201, 722054885, 228338256, 407719831, 762479457, 746536789,
                811667359, 778773518, 27368307, 438371670, 59469516, 5974669, 766196482, 606322308,
                86609485, 889750731, 340941507, 371263376, 625544428, 788878910, 808412394,
                996952918, 585237443, 1669644, 361786913, 480748381, 595143852, 837229828,
                199888908, 526807168, 579691190, 145404005, 459188207, 534491822, 439729802,
                840398449, 899297830, 235861787, 888050723, 656116726, 736550105, 440902696,
                85990869, 884343068, 56305184, 973478770, 168891766, 804805577, 927880474,
                876297919, 934814019, 676405347, 567277637, 112249297, 44930135, 39417871,
                47401357, 108819476, 281863274, 60168088, 692636218, 432775082, 14235602,
                770511792, 400295761, 697066277, 421835306, 220108638, 661224977, 261799937,
                168203998, 802214249, 544064410, 935080803, 583967898, 211768084, 751231582,
                972424306, 623534362, 335160196, 243276029, 554749550, 60050552, 797848181,
                395891998, 172428290, 159554990, 887420150, 970055531, 250388809, 487998999,
                856259313, 82104855, 232253360, 513365505, 244109365, 1559745, 695345956,
                261384175, 849009131, 323214113, 747664143, 444090941, 659224434, 80729842,
                570033864, 664989237, 827348878, 195888993, 576798521, 457882808, 731551699,
                212938473, 509096183, 827544702, 678320208, 677711203, 289752035, 66404266,
                555972231, 195290384, 97136305, 349551356, 785113347, 83489485, 66247239, 52167191,
                307390891, 547665832, 143066173, 350016754, 917404120, 296269301, 996122673,
                23015220, 602139210, 748566338, 187348575, 109838563, 574053420, 105574531,
                304173654, 542432219, 34538816, 325636655, 437843114, 630621321, 26853683,
                933245637, 616368450, 238971581, 511371690, 557301633, 911398531, 848952161,
                958992544, 925152039, 914456118, 724691727, 636817583, 238087006, 946237212,
                910291942, 114985663, 492237273, 450387329, 834860913, 763017204, 368925948,
                475812562, 740594930, 45060610, 806047532, 464456846, 172115341, 75307702,
                116261993, 562519302, 268838846, 173784895, 243624360, 61570384, 481661251,
                938269070, 95182730, 91068149, 115435332, 495022305, 136026497, 506496856,
                710729672, 113570024, 366384665, 564758715, 270239666, 277118392, 79874094,
                702807165, 112390913, 730341625, 103056890, 677948390, 339464594, 167240465,
                108312174, 839079953, 479334442, 271788964, 135498044, 277717575, 591048681,
                811637561, 353339603, 889410460, 839849206, 192345193, 736265527, 316439118,
                217544623, 788132977, 618898635, 183011467, 380858207, 996097969, 898554793,
                335353644, 54062950, 611251733, 419363534, 965429853, 160398980, 151319402,
                990918946, 607730875, 450718279, 173539388, 648991369, 970937898, 500780548,
                780122909, 39052406, 276894233, 460373282, 651081062, 461415770, 358700839,
                643638805, 560006119, 668123525, 686692315, 673464765, 957633609, 199866123,
                563432246, 841799766, 385330357, 504962686, 954061253, 128487469, 685707545,
                299172297, 717975101, 577786541, 318951960, 773206631, 306832604, 204355779,
                573592106, 30977140, 450398100, 363172638, 258379324, 472935553, 93940075,
                587220627, 776264326, 793270300, 291733496, 522049725, 579995261, 335416359,
                142946099, 472012302, 559947225, 332139472, 499377092, 464599136, 164752359,
                309058615, 86117128, 580204973, 563781682, 954840109, 624577416, 895609896,
                888287558, 836813268, 926036911, 386027524, 184419613, 724205533, 403351886,
                715247054, 716986954, 830567832, 383388563, 68409439, 6734065, 189239124, 68322490,
                943653305, 405755338, 811056092, 179518046, 825132993, 343807435, 985084650,
                868553027, 148528617, 160684257, 882148737, 591915968, 701445829, 529726489,
                302177126, 974886682, 241107368, 798830099, 940567523, 11633075, 325334066,
                346091869, 115312728, 473718967, 218129285, 878471898, 180002392, 699739374,
                917084264, 856859395, 435327356, 808651347, 421623838, 105419548, 59883031,
                322487421, 79716267, 715317963, 429277690, 398078032, 316486674, 384843585,
                940338439, 937409008, 940524812, 947549662, 833550543, 593524514, 996164327,
                987314628, 697611981, 636177449, 274192146, 418537348, 925347821, 952831975,
                893732627, 1277567, 358655417, 141866945, 581830879, 987597705, 347046911,
                775305697, 125354499, 951540811, 247662371, 343043237, 568392357, 997474832,
                209244402, 380480118, 149586983, 392838702, 309134554, 990779998, 263053337,
                325362513, 780072518, 551028176, 990826116, 989944961, 155569943, 596737944,
                711553356, 268844715, 451373308, 379404150, 462639908, 961812918, 654611901,
                382776490, 41815820, 843321396, 675258797, 845583555, 934281721, 741114145,
                275105629, 666247477, 325912072, 526131620, 252551589, 432030917, 554917439,
                818036959, 754363835, 795190182, 909210595, 278704903, 719566487, 628514947,
                424989675, 321685608, 50590510, 832069712, 198768464, 702004730, 99199382,
                707469729, 747407118, 302020341, 497196934, 5003231, 726997875, 382617671,
                296229203, 183888367, 703397904, 552133875, 732868367, 350095207, 26031303,
                863250534, 216665960, 561745549, 352946234, 784139777, 733333339, 503105966,
                459878625, 803187381, 16634739, 180898306, 68718097, 985594252, 404206040,
                749724532, 97830135, 611751357, 31131935, 662741752, 864326453, 864869025,
                167831173, 559214642, 718498895, 91352335, 608823837, 473379392, 385388084,
                152267158, 681756977, 46819124, 313132653, 56547945, 442795120, 796616594,
                256141983, 152028387, 636578562, 385377759, 553033642, 491415383, 919273670,
                996049638, 326686486, 160150665, 141827977, 540818053, 693305776, 593938674,
                186576440, 688809790, 565456578, 749296077, 519397500, 551096742, 696628828,
                775025061, 370732451, 164246193, 915265013, 457469634, 923043932, 912368644,
                777901604, 464118005, 637939935, 956856710, 490676632, 453019482, 462528877,
                502297454, 798895521, 100498586, 699767918, 849974789, 811575797, 438952959,
                606870929, 907720182, 179111720, 48053248, 508038818, 811944661, 752550134,
                401382061, 848924691, 764368449, 34629406, 529840945, 435904287, 26011548,
                208184231, 446477394, 206330671, 366033520, 131772368, 185646898, 648711554,
                472759660, 523696723, 271198437, 25058942, 859369491, 817928963, 330711333,
                724464507, 437605233, 701453022, 626663115, 281230685, 510650790, 596949867,
                295726547, 303076380, 465070856, 272814771, 538771609, 48824684, 951279549,
                939889684, 564188856, 48527183, 201307702, 484458461, 861754542, 326159309,
                181594759, 668422905, 286273596, 965656187, 44135644, 359960756, 936229527,
                407934361, 267193060, 456152084, 459116722, 124804049, 262322489, 920251227,
                816929577, 483924582, 151834896, 167087470, 490222511, 903466878, 361583925,
                368114731, 339383292, 388728584, 218107212, 249153339, 909458706, 322908524,
                202649964, 92255682, 573074791, 15570863, 94331513, 744158074, 196345098,
                334326205, 9416035, 98349682, 882121662, 769795511, 231988936, 888146074,
                137603545, 582627184, 407518072, 919419361, 909433461, 986708498, 310317874,
                373745190, 263645931, 256853930, 876379959, 702823274, 147050765, 308186532,
                175504139, 180350107, 797736554, 606241871, 384547635, 273712630, 586444655,
                682189174, 666493603, 946867127, 819114541, 502371023, 261970285, 825871994,
                126925175, 701506133, 314738056, 341779962, 561011609, 815463367, 46765164,
                49187570, 188054995, 957939114, 64814326, 933376898, 329837066, 338121343,
                765215899, 869630152, 978119194, 632627667, 975266085, 435887178, 282092463,
                129621197, 758245605, 827722926, 201339230, 918513230, 322096036, 547838438,
                985546115, 852304035, 593090119, 689189630, 555842733, 567033437, 469928208,
                212842957, 117842065, 404149413, 155133422, 663307737, 208761293, 206282795,
                717946122, 488906585, 414236650, 280700600, 962670136, 534279149, 214569244,
                375297772, 811053196, 922377372, 289594327, 219932130, 211487466, 701050258,
                398782410, 863002719, 27236531, 217598709, 375472836, 810551911, 178598958,
                247844667, 676526196, 812283640, 863066876, 857241854, 113917835, 624148346,
                726089763, 564827277, 826300950, 478982047, 439411911, 454039189, 633292726,
                48562889, 802100365, 671734977, 945204804, 508831870, 398781902, 897162044,
                644050694, 892168027, 828883117, 277714559, 713448377, 624500515, 590098114,
                808691930, 514359662, 895205045, 715264908, 628829100, 484492064, 919717789,
                513196123, 748510389, 403652653, 574455974, 77123823, 172096141, 819801784,
                581418893, 15655126, 15391652, 875641535, 203191898, 264582598, 880691101,
                907800444, 986598821, 340030191, 264688936, 369832433, 785804644, 842065079,
                423951674, 663560047, 696623384, 496709826, 161960209, 331910086, 541120825,
                951524114, 841656666, 162683802, 629786193, 190395535, 269571439, 832671304,
                76770272, 341080135, 421943723, 494210290, 751040886, 317076664, 672850561,
                72482816, 493689107, 135625240, 100228913, 684748812, 639655136, 906233141,
                929893103, 277813439, 814362881, 562608724, 406024012, 885537778, 10065330,
                60625018, 983737173, 60517502, 551060742, 804930491, 823845496, 727416538,
                946421040, 678171399, 842203531, 175638827, 894247956, 538609927, 885362182,
                946464959, 116667533, 749816133, 241427979, 871117927, 281804989, 163928347,
                563796647, 640266394, 774625892, 59342705, 256473217, 674115061, 918860977,
                322633051, 753513874, 393556719, 304644842, 767372800, 161362528, 754787150,
                627655552, 677395736, 799289297, 846650652, 816701166, 687265514, 787113234,
                358757251, 701220427, 607715125, 245795606, 600624983, 10475577, 728620948,
                759404319, 36292292, 491466901, 22556579, 114495791, 647630109, 586445753,
                482254337, 718623833, 763514207, 66547751, 953634340, 351472920, 308474522,
                494166907, 634359666, 172114298, 865440961, 364380585, 921648059, 965683742,
                260466949, 117483873, 962540888, 237120480, 620531822, 193781724, 213092254,
                107141741, 602742426, 793307102, 756154604, 236455213, 362928234, 14162538,
                753042874, 778983779, 25977209, 49389215, 698308420, 859637374, 49031023,
                713258160, 737331920, 923333660, 804861409, 83868974, 682873215, 217298111,
                883278906, 176966527, 954913, 105359006, 390019735, 10430738, 706334445, 315103615,
                567473423, 708233401, 48160594, 946149627, 346966053, 281329488, 462880311,
                31503476, 185438078, 965785236, 992656683, 916291845, 881482632, 899946391,
                321900901, 512634493, 303338827, 121000338, 967284733, 492741665, 152233223,
                165393390, 680128316, 917041303, 532702135, 741626808, 496442755, 536841269,
                131384366, 377329025, 301196854, 859917803, 676511002, 373451745, 847645126,
                823495900, 576368335, 73146164, 954958912, 847549272, 241289571, 646654592,
                216046746, 205951465, 3258987, 780882948, 822439091, 598245292, 869544707,
                698611116,
            ];
            #[cfg(test)]
            mod tests {
                use super::*;
                #[test]
                fn test_simple() {
                    let c = Comb::new(100);
                    assert_eq!(Mint::from(336), c.perm(8, 3));
                    assert_eq!(Mint::from(56), c.comb(8, 3));
                    assert_eq!(Mint::from(10), c.multi_comb(3, 3));
                }
                #[test]
                fn test_fact() {
                    let c = Comb::new(100);
                    let p = 8721234;
                    let mut f = Mint::from(1);
                    for i in 1..(p + 1) {
                        f *= i;
                    }
                    assert_eq!(f, c.fact(p));
                }
            }
        }
        pub mod mint {
            use std;
            pub const MOD: u32 = 1000000007;
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
            macro_rules! impl_signed_mint(( $ ( $ t : ty ) * ) => (
                                      $ (
                                      impl From < $ t > for Mint {
                                      # [ inline ] fn from ( x : $ t ) -> Mint
                                      {
                                      let t = ( x as i64 ) % ( MOD as i64 ) ;
                                      if x >= 0 { Mint { val : t as u32 } }
                                      else {
                                      Mint { val : ( MOD as i64 + t ) as u32 }
                                      } } } ) * ));
            macro_rules! impl_unsigned_mint(( $ ( $ t : ty ) * ) => (
                                        $ (
                                        impl From < $ t > for Mint {
                                        # [ inline ] fn from ( x : $ t ) ->
                                        Mint {
                                        let t = x as u64 % MOD as u64 ; Mint {
                                        val : t as u32 } } } ) * ));
            impl_signed_mint! (i8 i16 i32 i64 isize);
            impl_unsigned_mint! (u8 u16 u32 u64 usize);
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
            #[cfg(test)]
            mod tests {
                use super::*;
                #[test]
                fn test_simple() {
                    let a: Mint = Mint::from(3);
                    let b: Mint = Mint::from(1000000000);
                    assert_eq!(Mint::from(3000000000u64 % MOD as u64), a * b);
                }
            }
        }
        pub mod prime {
            pub fn is_prime(n: u64) -> bool {
                const HINT: &'static [u64] = &[2];
                const WITNESSES: &'static [(u64, &'static [u64])] = &[
                    (2046, HINT),
                    (1373652, &[2, 3]),
                    (9080190, &[31, 73]),
                    (25326000, &[2, 3, 5]),
                    (4759123140, &[2, 7, 61]),
                    (1112004669632, &[2, 13, 23, 1662803]),
                    (2152302898746, &[2, 3, 5, 7, 11]),
                    (3474749660382, &[2, 3, 5, 7, 11, 13]),
                    (341550071728320, &[2, 3, 5, 7, 11, 13, 17]),
                    (18446744073709551615, &[2, 3, 5, 7, 11, 13, 17, 19, 23]),
                ];
                if n % 2 == 0 {
                    return n == 2;
                }
                if n == 1 {
                    return false;
                }
                let mut d = n - 1;
                let mut s = 0;
                while d % 2 == 0 {
                    d /= 2;
                    s += 1
                }
                let witnesses = WITNESSES
                    .iter()
                    .find(|&&(hi, _)| hi >= n)
                    .map(|&(_, wtnss)| wtnss)
                    .unwrap();
                'next_witness: for &a in witnesses.iter() {
                    let mut power = mod_exp(a, d, n);
                    assert!(power < n);
                    if power == 1 || power == n - 1 {
                        continue 'next_witness;
                    }
                    for _r in 0..s {
                        power = mod_sqr(power, n);
                        assert!(power < n);
                        if power == 1 {
                            return false;
                        }
                        if power == n - 1 {
                            continue 'next_witness;
                        }
                    }
                    return false;
                }
                true
            }
            #[derive(Copy, Clone, PartialEq, PartialOrd, Ord, Eq, Debug)]
            struct U128 {
                hi: u64,
                lo: u64,
            }
            fn modulo(mut a: U128, m: u64) -> u64 {
                if a.hi >= m {
                    a.hi -= (a.hi / m) * m;
                }
                let mut x = a.hi;
                let mut y = a.lo;
                for _ in 0..64 {
                    let t = (x as i64 >> 63) as u64;
                    x = (x << 1) | (y >> 63);
                    y <<= 1;
                    if (x | t) >= m {
                        x = x.wrapping_sub(m);
                        y += 1;
                    }
                }
                x
            }
            fn mul128(u: u64, v: u64) -> U128 {
                let u1 = u >> 32;
                let u0 = u & (!0 >> 32);
                let v1 = v >> 32;
                let v0 = v & (!0 >> 32);
                let t = u0 * v0;
                let w0 = t & (!0 >> 32);
                let k = t >> 32;
                let t = u1 * v0 + k;
                let w1 = t & (!0 >> 32);
                let w2 = t >> 32;
                let t = u0 * v1 + w1;
                let k = t >> 32;
                U128 {
                    lo: (t << 32) + w0,
                    hi: u1 * v1 + w2 + k,
                }
            }
            fn mod_mul_(a: u64, b: u64, m: u64) -> u64 {
                modulo(mul128(a, b), m)
            }
            fn mod_mul(a: u64, b: u64, m: u64) -> u64 {
                match a.checked_mul(b) {
                    Some(r) => if r >= m {
                        r % m
                    } else {
                        r
                    },
                    None => mod_mul_(a, b, m),
                }
            }
            fn mod_sqr(a: u64, m: u64) -> u64 {
                if a < (1 << 32) {
                    let r = a * a;
                    if r >= m {
                        r % m
                    } else {
                        r
                    }
                } else {
                    mod_mul_(a, a, m)
                }
            }
            fn mod_exp(mut x: u64, mut d: u64, n: u64) -> u64 {
                let mut ret: u64 = 1;
                while d != 0 {
                    if d % 2 == 1 {
                        ret = mod_mul(ret, x, n)
                    }
                    d /= 2;
                    x = mod_sqr(x, n);
                }
                ret
            }
        }
    }
    pub mod data_structure {
        pub mod bit {
            pub struct BIT {
                tree: Vec<i64>,
            }
            pub struct BITRange {
                bit0: BIT,
                bit1: BIT,
            }
            impl BIT {
                pub fn new(n: usize) -> BIT {
                    BIT { tree: vec![0; n] }
                }
                pub fn add(&mut self, at: usize, by: i64) {
                    let mut idx = at;
                    while idx < self.tree.len() {
                        self.tree[idx] += by;
                        idx |= idx + 1;
                    }
                }
                pub fn get(&self, begin: usize, end: usize) -> i64 {
                    if begin >= end {
                        return 0;
                    }
                    let a = if end > 0 {
                        self.cum(end - 1)
                    } else {
                        0
                    };
                    let b = if begin > 0 {
                        self.cum(begin - 1)
                    } else {
                        0
                    };
                    a - b
                }
                fn cum(&self, last: usize) -> i64 {
                    let mut res = 0;
                    let mut idx = last as i64;
                    while idx >= 0 {
                        res += self.tree[idx as usize];
                        idx = (idx & (idx + 1)) - 1;
                    }
                    res
                }
            }
            impl BITRange {
                pub fn new(n: usize) -> BITRange {
                    BITRange {
                        bit0: BIT::new(n + 1),
                        bit1: BIT::new(n + 1),
                    }
                }
                pub fn add(&mut self, begin: usize, end: usize, by: i64) {
                    let a = begin as i64;
                    let b = end as i64;
                    self.bit0.add(begin, -by * a);
                    self.bit0.add(end, by * b);
                    self.bit1.add(begin, by);
                    self.bit1.add(end, -by);
                }
                pub fn get(&self, begin: usize, end: usize) -> i64 {
                    if begin >= end {
                        return 0;
                    }
                    self.cum(end) - self.cum(begin)
                }
                fn cum(&self, end: usize) -> i64 {
                    let a = self.bit0.get(0, end);
                    let b = self.bit1.get(0, end);
                    return a + b * end as i64;
                }
            }
            #[cfg(test)]
            mod tests {
                use super::*;
                #[test]
                fn test_simple() {
                    let mut bit = BIT::new(10);
                    bit.add(2, 1);
                    bit.add(3, 3);
                    bit.add(5, 10);
                    bit.add(0, -4);
                    bit.add(9, -5);
                    assert_eq!(5, bit.get(0, 10));
                    assert_eq!(4, bit.get(2, 4));
                    assert_eq!(1, bit.get(2, 3));
                    assert_eq!(0, bit.get(2, 2));
                    assert_eq!(0, bit.get(2, 0));
                    assert_eq!(-4, bit.get(0, 1));
                    assert_eq!(5, bit.get(5, 10));
                    let mut bit = BITRange::new(10);
                    bit.add(1, 3, 1);
                    bit.add(2, 5, 2);
                    assert_eq!(1, bit.get(1, 2));
                    assert_eq!(4, bit.get(1, 3));
                    assert_eq!(6, bit.get(1, 4));
                    assert_eq!(6, bit.get(0, 4));
                }
            }
        }
        pub mod union_find {
            pub struct UnionFind {
                data: Vec<i32>,
            }
            impl UnionFind {
                pub fn new(n: usize) -> UnionFind {
                    UnionFind { data: vec![-1; n] }
                }
                pub fn unite(&mut self, x: usize, y: usize) -> bool {
                    let x = self.root(x);
                    let y = self.root(y);
                    if x != y {
                        let (x, y) = if self.data[x] <= self.data[y] {
                            (x, y)
                        } else {
                            (y, x)
                        };
                        self.data[x] += self.data[y];
                        self.data[y] = x as i32;
                    }
                    x != y
                }
                pub fn same(&mut self, x: usize, y: usize) -> bool {
                    self.root(x) == self.root(y)
                }
                pub fn size(&mut self, x: usize) -> u32 {
                    let r = self.root(x);
                    (-self.data[r]) as u32
                }
                pub fn root(&mut self, x: usize) -> usize {
                    if self.data[x] < 0 {
                        x
                    } else {
                        let nx = self.data[x] as usize;
                        let r = self.root(nx);
                        self.data[x] = r as i32;
                        r
                    }
                }
            }
            #[cfg(test)]
            mod tests {
                use super::*;
                #[test]
                fn test_simple() {
                    let mut uf = UnionFind::new(3);
                    assert_eq!(1, uf.size(0));
                    assert_eq!(1, uf.size(1));
                    assert_eq!(1, uf.size(2));
                    assert_eq!(0, uf.root(0));
                    assert_eq!(1, uf.root(1));
                    assert_eq!(2, uf.root(2));
                    assert!(!uf.same(1, 2));
                    uf.unite(1, 2);
                    assert_ne!(uf.root(0), uf.root(2));
                    assert_eq!(uf.root(1), uf.root(2));
                    assert_eq!(1, uf.size(0));
                    assert_eq!(2, uf.size(1));
                    assert_eq!(2, uf.size(2));
                    assert!(uf.same(1, 2));
                    uf.unite(0, 1);
                    assert_eq!(uf.root(0), uf.root(2));
                    assert_eq!(uf.root(1), uf.root(2));
                    assert_eq!(3, uf.size(0));
                    assert_eq!(3, uf.size(1));
                    assert_eq!(3, uf.size(2));
                    assert!(uf.same(1, 2));
                    assert!(uf.same(0, 2));
                }
            }
        }
    }
    pub mod util {
        pub mod permutation {
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
            #[cfg(test)]
            mod tests {
                use super::*;
                #[test]
                fn test_simple() {
                    let mut data = [0, 0, 1, 1, 2];
                    data.next_permutation();
                    assert_eq!(&data, &[0, 0, 1, 2, 1]);
                    data.next_permutation();
                    assert_eq!(&data, &[0, 0, 2, 1, 1]);
                    data.next_permutation();
                    assert_eq!(&data, &[0, 1, 0, 1, 2]);
                    data.next_permutation();
                    assert_eq!(&data, &[0, 1, 0, 2, 1]);
                    data.next_permutation();
                    assert_eq!(&data, &[0, 1, 1, 0, 2]);
                    data.prev_permutation();
                    assert_eq!(&data, &[0, 1, 0, 2, 1]);
                    data.prev_permutation();
                    assert_eq!(&data, &[0, 1, 0, 1, 2]);
                    data.prev_permutation();
                    assert_eq!(&data, &[0, 0, 2, 1, 1]);
                    data.prev_permutation();
                    assert_eq!(&data, &[0, 0, 1, 2, 1]);
                    data.prev_permutation();
                    assert_eq!(&data, &[0, 0, 1, 1, 2]);
                    assert!(!data.prev_permutation());
                }
            }
        }
        pub mod rand {
            use std::{marker, mem};
            use std::io::{self, Read};
            use std::fs::File;
            use std::char;
            #[derive(Debug, Clone, Copy)]
            pub struct Xoroshiro128Rng {
                state: [u64; 2],
            }
            impl Xoroshiro128Rng {
                pub fn new_unseeded() -> Self {
                    Xoroshiro128Rng {
                        state: [1817879012901901417, 10917585336602961851],
                    }
                }
                pub fn from_seed(x: u64, y: u64) -> Self {
                    Xoroshiro128Rng { state: [x, y] }
                }
                pub fn new() -> Self {
                    let mut rng = OsRng::new().unwrap();
                    Self::from_seed(rng.gen(), rng.gen())
                }
            }
            impl Rng for Xoroshiro128Rng {
                fn next_u32(&mut self) -> u32 {
                    self.next_u64() as u32
                }
                fn next_u64(&mut self) -> u64 {
                    let s0: u64 = self.state[0];
                    let mut s1: u64 = self.state[1];
                    let result: u64 = s0.wrapping_add(s1);
                    s1 ^= s0;
                    self.state[0] = s0.rotate_left(55) ^ s1 ^ (s1 << 14);
                    self.state[1] = s1.rotate_left(36);
                    result
                }
            }
            pub trait Rand: Sized {
                fn rand<R: Rng>(rng: &mut R) -> Self;
            }
            pub trait Rng {
                fn next_u32(&mut self) -> u32;
                fn next_u64(&mut self) -> u64 {
                    let x = self.next_u32() as u64;
                    let y = self.next_u32() as u64;
                    (y << 32) | x
                }
                fn next_f32(&mut self) -> f32 {
                    const UPPER_MASK: u32 = 1065353216;
                    const LOWER_MASK: u32 = 8388607;
                    let tmp = UPPER_MASK | (self.next_u32() & LOWER_MASK);
                    let result: f32 = unsafe { mem::transmute(tmp) };
                    result - 1.0
                }
                fn next_f64(&mut self) -> f64 {
                    const UPPER_MASK: u64 = 4607182418800017408;
                    const LOWER_MASK: u64 = 4503599627370495;
                    let tmp = UPPER_MASK | (self.next_u64() & LOWER_MASK);
                    let result: f64 = unsafe { mem::transmute(tmp) };
                    result - 1.0
                }
                #[inline(always)]
                fn gen<T: Rand>(&mut self) -> T
                where
                    Self: Sized,
                {
                    Rand::rand(self)
                }
                fn gen_iter<'a, T: Rand>(&'a mut self) -> Generator<'a, T, Self>
                where
                    Self: Sized,
                {
                    Generator {
                        rng: self,
                        _marker: marker::PhantomData,
                    }
                }
                fn shuffle<T>(&mut self, values: &mut [T])
                where
                    Self: Sized,
                {
                    let mut i = values.len();
                    while i >= 2 {
                        i -= 1;
                        values.swap(i, (self.next_u64() as usize) % i);
                    }
                }
            }
            #[derive(Debug)]
            pub struct Generator<'a, T, R: 'a> {
                rng: &'a mut R,
                _marker: marker::PhantomData<fn() -> T>,
            }
            impl<'a, T: Rand, R: Rng> Iterator for Generator<'a, T, R> {
                type Item = T;
                fn next(&mut self) -> Option<T> {
                    Some(self.rng.gen())
                }
            }
            pub struct OsRng {
                reader: File,
            }
            impl OsRng {
                pub fn new() -> io::Result<OsRng> {
                    let reader = File::open("/dev/urandom")?;
                    Ok(OsRng { reader: reader })
                }
            }
            impl Rng for OsRng {
                fn next_u32(&mut self) -> u32 {
                    let mut dest = [0u8; 4];
                    self.reader.read_exact(&mut dest).unwrap();
                    unsafe { mem::transmute::<[u8; 4], u32>(dest) }
                }
            }
            impl Rand for isize {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> isize {
                    if mem::size_of::<isize>() == 4 {
                        rng.gen::<i32>() as isize
                    } else {
                        rng.gen::<i64>() as isize
                    }
                }
            }
            impl Rand for i8 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> i8 {
                    rng.next_u32() as i8
                }
            }
            impl Rand for i16 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> i16 {
                    rng.next_u32() as i16
                }
            }
            impl Rand for i32 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> i32 {
                    rng.next_u32() as i32
                }
            }
            impl Rand for i64 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> i64 {
                    rng.next_u64() as i64
                }
            }
            #[cfg(feature = "i128_support")]
            impl Rand for i128 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> i128 {
                    rng.gen::<u128>() as i128
                }
            }
            impl Rand for usize {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> usize {
                    if mem::size_of::<usize>() == 4 {
                        rng.gen::<u32>() as usize
                    } else {
                        rng.gen::<u64>() as usize
                    }
                }
            }
            impl Rand for u8 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> u8 {
                    rng.next_u32() as u8
                }
            }
            impl Rand for u16 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> u16 {
                    rng.next_u32() as u16
                }
            }
            impl Rand for u32 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> u32 {
                    rng.next_u32()
                }
            }
            impl Rand for u64 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> u64 {
                    rng.next_u64()
                }
            }
            #[cfg(feature = "i128_support")]
            impl Rand for u128 {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> u128 {
                    ((rng.next_u64() as u128) << 64) | (rng.next_u64() as u128)
                }
            }
            impl Rand for f64 {
                fn rand<R: Rng>(rng: &mut R) -> f64 {
                    rng.next_f64()
                }
            }
            impl Rand for f32 {
                fn rand<R: Rng>(rng: &mut R) -> f32 {
                    rng.next_f32()
                }
            }
            impl Rand for char {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> char {
                    const CHAR_MASK: u32 = 2097151;
                    loop {
                        match char::from_u32(rng.next_u32() & CHAR_MASK) {
                            Some(c) => return c,
                            None => {}
                        }
                    }
                }
            }
            impl Rand for bool {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> bool {
                    rng.gen::<u8>() & 1 == 1
                }
            }
            macro_rules! tuple_impl(( $ ( $ tyvar : ident ) , * ) => {
                                impl < $ ( $ tyvar : Rand ) , * > Rand for (
                                $ ( $ tyvar ) , * , ) {
                                # [ inline ] fn rand < R : Rng > (
                                _rng : & mut R ) -> ( $ ( $ tyvar ) , * , ) {
                                ( $ ( _rng . gen :: < $ tyvar > (  ) ) , * , )
                                } } });
            impl Rand for () {
                #[inline]
                fn rand<R: Rng>(_: &mut R) -> () {
                    ()
                }
            }
            tuple_impl!(A);
            tuple_impl!(A, B);
            tuple_impl!(A, B, C);
            tuple_impl!(A, B, C, D);
            tuple_impl!(A, B, C, D, E);
            tuple_impl!(A, B, C, D, E, F);
            tuple_impl!(A, B, C, D, E, F, G);
            tuple_impl!(A, B, C, D, E, F, G, H);
            tuple_impl!(A, B, C, D, E, F, G, H, I);
            tuple_impl!(A, B, C, D, E, F, G, H, I, J);
            tuple_impl!(A, B, C, D, E, F, G, H, I, J, K);
            tuple_impl!(A, B, C, D, E, F, G, H, I, J, K, L);
            macro_rules! array_impl({
                                $ n : expr , $ t : ident , $ ( $ ts : ident ,
                                ) * } => {
                                array_impl ! { ( $ n - 1 ) , $ ( $ ts , ) * }
                                impl < T > Rand for [ T ; $ n ] where T : Rand
                                {
                                # [ inline ] fn rand < R : Rng > (
                                _rng : & mut R ) -> [ T ; $ n ] {
                                [
                                _rng . gen :: < $ t > (  ) , $ (
                                _rng . gen :: < $ ts > (  ) ) , * ] } } } ; {
                                $ n : expr , } => {
                                impl < T > Rand for [ T ; $ n ] {
                                fn rand < R : Rng > ( _rng : & mut R ) -> [
                                T ; $ n ] { [  ] } } } ;);
            array_impl!(
                32,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
                T,
            );
            impl<T: Rand> Rand for Option<T> {
                #[inline]
                fn rand<R: Rng>(rng: &mut R) -> Option<T> {
                    if rng.gen() {
                        Some(rng.gen())
                    } else {
                        None
                    }
                }
            }
        }
    }
}
