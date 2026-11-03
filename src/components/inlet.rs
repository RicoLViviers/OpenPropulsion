use pyo3::prelude::*;

#[pyclass]
#[derive(Clone)]
pub struct Inlet {
}

#[pymethods]
impl Inlet {
    #[new]
    pub fn new() -> Self {
        Inlet { }
    }

    pub fn calculate_stagnation_states(
        &self,
        mach: f64,
        t_static: f64,
        p_static: f64,
        gamma: f64,
    ) -> PyResult<(f64, f64)> {
        let t_stag: f64 = t_static * (1.0 + ((gamma - 1.0) / 2.0) * mach.powi(2));
        let p_stag: f64 = p_static * (t_stag/t_static).powf(gamma / (gamma - 1.0));

        Ok((t_stag, p_stag))
    }
}
    