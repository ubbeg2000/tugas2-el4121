# motor parameters
K = 1
TS = 0.01
TC = 1.2
A1 = K * TS / (2 * TC + TS)
A2 = (TS - 2 * TC) / (2 * TC + TS)


def motor(input, prev_input, prev_output):
    return ((input + prev_input) * A1 - prev_output * A2)
