MOD = 10**9 + 7


# the loop behind pow(a, b, MOD)
def binpow(a: int, b: int) -> int:
    a %= MOD
    res = 1
    while b:
        if b & 1: res = res * a % MOD
        a = a * a % MOD
        b >>= 1
    return res


# Fermat's little theorem: a^(p-1) = 1 mod p for p prime and gcd(a, p) = 1,
# so a^(p-2) = a^(-1). In one call: pow(a, -1, MOD)
def modInverse(a: int) -> int:
    return binpow(a, MOD - 2)
