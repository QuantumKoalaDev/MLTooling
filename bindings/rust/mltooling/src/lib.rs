pub mod ffi;
pub mod matrix;

#[cfg(test)]
mod tests {
    use super::matrix::MatrixF;

    #[test]
    fn test_matrix_creation() {
        let m = MatrixF::new(3, 3).expect("Matrix creation failed");
        let value =  m.get(1, 2).expect("Konnte wert nicht lesen");
        assert_eq!(value, 0.0);
        assert_eq!(value, 0.0);
    }

    #[test]
    fn test_matrix_creation_from_buff() {
        let vec = vec![0.0f32; 9];
        let _m = MatrixF::new_from_slice(3, 3, &vec).expect("Matrix creation failed");
    }
}
