use std::f32::consts::PI;

pub enum Functions {
    Square,
    Impulse,
    Ramp,
    Triangle,
    Sine,
}

pub fn func_value(func: &Functions, n: u16, num: u16) -> f32 {
    let arg: f32 = n as f32 / (num - 1) as f32;

    match func {
        Functions::Sine => (f32::sin(arg * PI * 2.0) + 1.0) / 2.0,
        _ => arg,
    }
}

pub fn to_sample(val: f32, bits: u16, low: f32, high: f32) -> u16 {
    let max: f32 = ((1 << bits) - 1) as f32;

    let mut conv = val * max;
    if conv < low {
        conv = low;
    } else if conv > high {
        conv = high;
    }

    conv as u16
}

pub fn gen_points(func: &Functions, num: u16, bits: u16, low: u16, high: u16) -> Vec<u16> {
    let mut points: Vec<u16> = Vec::<u16>::with_capacity(num as usize);

    for n in 0..num {
        let val = func_value(func, n, num);
        points.push(to_sample(val, bits, low as f32, high as f32));
    }

    points
}

fn main() {
    const NUM_POINTS: u16 = 1024;
    const BITS: u16 = 12;
    const LOW: u16 = 0;
    const HIGH: u16 = (1 << BITS) - 1;

    let data = gen_points(&Functions::Sine, NUM_POINTS, BITS, LOW, HIGH);

    println!("POINTS: {NUM_POINTS}, BITS: {BITS}, LOW: {LOW}, HIGH: {HIGH}");

    println!("int waveData[] = {{",);
    for (n, v) in data.iter().enumerate() {
        if n % 8 == 0 {
            print!("  ");
        }
        print!("{:#05x}", v);

        if n != (NUM_POINTS - 1) as usize {
            print!(", ");

            if n % 8 == 7 {
                println!();
            }
        } else {
            println!();
        }
    }
    println!("}};")
}
