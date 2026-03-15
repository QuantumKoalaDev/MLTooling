fn main() {
    println!("cargo:rustc-link-lib=MLToolingCwrapper");
    println!("cargo:rustc-link-search=native=../../../build/cwrapper");
}
