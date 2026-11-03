class Inlet:
    def __init__(self) -> None: ...

    def calculate_stagnation_states(
        self,
        mach: float,
        t_static: float,
        p_static: float,
        gamma: float,
    ) -> tuple[float, float]: ...