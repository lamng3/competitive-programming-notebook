MOD = 10**9 + 7


# pow(a, b, MOD) is binpow; pow(a, -1, MOD) is the inverse (Python 3.8+)
def modInverse(a: int) -> int:
    return pow(a, MOD - 2, MOD) # Fermat: a^(p-2) = a^(-1) mod p


class ModFact:
    def __init__(self, n: int):
        self.n = n
        self.fac = [1] * (n + 1)
        for i in range(1, n + 1): self.fac[i] = self.fac[i - 1] * i % MOD
        # inv[n] = (n!)^(-1), then inv[i-1] = inv[i] * i
        self.inv = [1] * (n + 1)
        self.inv[n] = modInverse(self.fac[n])
        for i in range(n, 0, -1): self.inv[i - 1] = self.inv[i] * i % MOD

    def nCk(self, n: int, k: int) -> int:
        if n < k or n < 0 or k < 0: return 0
        return self.fac[n] * self.inv[k] % MOD * self.inv[n - k] % MOD
