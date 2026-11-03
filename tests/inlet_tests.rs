#[cfg(test)]
mod tests {
    use open_propulsion::components::inlet::Inlet;

    // T0 = T = 293.15
    // P0 = P = 101.3
    #[test]
    fn calculate_stagnation_states_at_zero_mach() {
        let inlet = Inlet::new();
        let (stagnation_temperature, stagnation_pressure) = inlet
            .calculate_stagnation_states(0.0, 293.15, 101.3, 1.4)
            .unwrap();

        assert_eq!(stagnation_temperature, 293.15);
        assert_eq!(stagnation_pressure, 101.3);
    }

    // T0 = 307.8075
    // P0 = +- 120.16
    #[test]
    fn calculate_stagnation_states_at_zero_point_five_mach() {
        let inlet = Inlet::new();
        let (stagnation_temperature, stagnation_pressure) = inlet
            .calculate_stagnation_states(0.5, 293.15, 101.3, 1.4)
            .unwrap();

        assert!((stagnation_temperature - 307.8075).abs() < 0.0001);
        assert!((stagnation_pressure - 120.163340234).abs() < 0.0001);
    }

    // T0 = 351.78
    // P0 = +- 191.75
    #[test]
    fn calculate_stagnation_states_at_one_mach() {
        let inlet = Inlet::new();
        let (stagnation_temperature, stagnation_pressure) = inlet
            .calculate_stagnation_states(1.0, 293.15, 101.3, 1.4)
            .unwrap();

        assert!((stagnation_temperature - 351.78).abs() < 0.0001);
        assert!((stagnation_pressure - 120.163340234).abs() < 0.0001);
    }
}