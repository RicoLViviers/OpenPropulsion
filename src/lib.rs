use pyo3::prelude::*;

pub mod components;
use components::inlet::Inlet;

#[pymodule]
fn open_propulsion(m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_class::<Inlet>()?;
    Ok(())
}