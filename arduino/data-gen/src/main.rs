use data_gen::data_gen::{gen_points, Functions};

fn output_points(
    points: Vec<u16>,
    func: &Functions,
    num_points: u16,
    bits: u16,
    low: u16,
    high: u16,
) {
    println!(
        "\n// FUNCTION: {:?}, POINTS: {num_points}, BITS: {bits}, LOW: {low}, HIGH: {high}",
        func
    );

    println!("int waveData[] = {{",);
    for (n, v) in points.iter().enumerate() {
        if n % 8 == 0 {
            print!("  ");
        }
        print!("{:#05x}", v);

        if n != (num_points - 1) as usize {
            print!(", ");

            if n % 8 == 7 {
                println!();
            }
        } else {
            println!();
        }
    }
    println!("}};\n")
}

fn main() {
    const NUM_POINTS: u16 = 1024;
    const BITS: u16 = 12;
    const LOW: u16 = 0;
    const HIGH: u16 = (1 << BITS) - 1;

    let funcs = [
        Functions::Sine,
        Functions::Impulse,
        Functions::Square,
        Functions::Ramp,
        Functions::Triangle,
        Functions::Random,
    ];

    for func in funcs {
        let data = gen_points(&func, NUM_POINTS, BITS, LOW, HIGH);
        output_points(data, &func, NUM_POINTS, BITS, LOW, HIGH);
    }
}
