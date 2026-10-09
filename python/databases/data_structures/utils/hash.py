import random

MASK = (1 << 64) - 1  # Python ints never overflow, so cut every step to 64 bits


# polynomial rolling hash
def polynomial(key, base=31):
    h = 0
    for c in key:
        h = (h * base + ord(c)) & MASK
    return h


# DJB2 with a custom seed
def djb2(key, seed=5381):
    h = seed
    for c in key:
        h = (h * 33 + ord(c)) & MASK
    return h


# FNV-1a (64-bit) with a custom seed
def fnv1a(key, seed=0):
    h = 14695981039346656037 ^ seed
    for c in key:
        h ^= ord(c)
        h = (h * 1099511628211) & MASK
    return h


# 64-bit avalanche mixer
def splitmix64(x):
    x = (x + 0x9e3779b97f4a7c15) & MASK
    x = ((x ^ (x >> 30)) * 0xbf58476d1ce4e5b9) & MASK
    x = ((x ^ (x >> 27)) * 0x94d049bb133111eb) & MASK
    return x ^ (x >> 31)


# hash of a str or int under a seed, every seed gives an independent hash
# use hash_with_seed(key, seed) % width as the column of a row
def hash_with_seed(key, seed):
    return splitmix64(djb2(str(key)) ^ ((seed + 0x9e3779b97f4a7c15) & MASK))


# one random 64-bit seed per row
def random_seeds(k):
    return [random.getrandbits(64) for _ in range(k)]


# k hashes via Kirsch-Mitzenmacher: h1 + i*h2
def generate_hashes(k):
    return [lambda key, i=i: (djb2(key) + i * fnv1a(key)) & MASK for i in range(k)]
