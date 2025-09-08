mod instance;
fn main() {
    println!("{}", instance::factorial::factorial(5));
    let arr = [0, 1, 2, 4, 5, 6, 7, 8, 9];
    println!("{}", instance::divide::binary_search(&arr, 5));
}
