import open_propulsion

inlet = open_propulsion.Inlet()

result = inlet.calculate_stagnation_states(1.0, 293.15, 101.3, 1.4)

print("Stagnation Temperature: ", result[0])
print("Stagnation Pressure: ", result[1])