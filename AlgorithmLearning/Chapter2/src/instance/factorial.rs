pub fn factorial(n: i64) -> i64 {
    if n < 0 {
        panic!("factorial is not defined for negative numbers");
    } else if n == 0 || n == 1 {
        1
    } else {
        n * factorial(n - 1)
    }
}
