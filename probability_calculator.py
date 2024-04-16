import math

def calculate_probability(k, N, m):
    p = (1 - math.exp((-1*k) * (N + 0.5) / (m - 1))) ** k
    return p

# Example usage
k = 1
N = 8
m = 32

probability = calculate_probability(k, N, m)*100
print("Probability:", probability)