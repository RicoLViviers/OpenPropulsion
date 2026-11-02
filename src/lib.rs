use pyo3::prelude::*;

#[pyfunction]
fn hello_world(name: String) -> PyResult<String> {
    println!("Hello from the Rust backend!");
    let greeting = format!("Hello, {}! This message was built in Rust", name);
    Ok(greeting)
}

#[pymodule]
fn open_propulsion(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(hello_world, m)?)?;
    Ok(())
}