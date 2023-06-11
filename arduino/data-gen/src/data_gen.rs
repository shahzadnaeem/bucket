use rand::prelude::*;
use std::f32::consts::PI;

#[derive(Debug, Clone, Copy)]
pub enum Functions {
    Square,
    Impulse,
    Ramp,
    Triangle,
    Sine,
    Random,
}

fn bits_max(bits: u16) -> u32 {
    (1 << bits) - 1
}

fn func_value(func: &Functions, n: u16, num: u16) -> f32 {
    let arg: f32 = n as f32 / (num - 1) as f32;

    match func {
        Functions::Sine => (f32::sin(arg * PI * 2.0) + 1.0) / 2.0,
        Functions::Ramp => arg,
        Functions::Impulse => {
            if n == 0 {
                1.0
            } else {
                0.0
            }
        }
        Functions::Square => {
            if n < num / 2 {
                1.0
            } else {
                0.0
            }
        }
        Functions::Triangle => {
            if n < num / 2 {
                if n == num / 2 - 1 {
                    2.0
                } else {
                    arg * 2.0
                }
            } else {
                (1.0 - arg) * 2.0
            }
        }
        Functions::Random => random(),
    }
}

fn to_sample(val: f32, bits: u16, low: f32, high: f32) -> u16 {
    let max: f32 = bits_max(bits) as f32;

    let mut conv = val * max;
    if conv < low {
        conv = low;
    } else if conv > high {
        conv = high;
    }

    conv.round() as u16
}

pub fn gen_points(func: &Functions, num: u16, bits: u16, low: u16, high: u16) -> Vec<u16> {
    let mut points: Vec<u16> = Vec::<u16>::with_capacity(num as usize);

    for n in 0..num {
        let val = func_value(func, n, num);
        points.push(to_sample(val, bits, low as f32, high as f32));
    }

    points
}

#[cfg(test)]
mod data_gen_tests {
    use super::*;

    #[test]
    fn nul_points() {
        let res = gen_points(&Functions::Sine, 0, 1, 0, 0);

        assert_eq!(res.len(), 0);
    }

    #[test]
    fn points_1() {
        let res = gen_points(&Functions::Sine, 1, 1, 0, 1);

        assert_eq!(res.len(), 1);
        assert_eq!(res[0], 0);
    }

    #[test]
    fn sin_100_2bit() {
        const NUM_POINTS: usize = 100;
        const BITS: u16 = 2;
        let max_val: u16 = bits_max(BITS) as u16;

        let res = gen_points(&Functions::Sine, NUM_POINTS as u16, BITS, 0, max_val);

        println!("10 points, 1 bit: {:?}", res);

        assert_eq!(res.len(), NUM_POINTS as usize);
        assert_eq!(res[NUM_POINTS / 2 - 1], max_val / 2 + 1);
        assert_eq!(res[NUM_POINTS - 1], max_val / 2 + 1);
    }
}
