from utils.hash import djb2, fnv1a

class BloomFilter:
    def __init__(self, bit_size: int, hash_functions=None) -> None:
        self.bit_size_ = bit_size
        self.bit_vector_ = [False] * self.bit_size_
        self.hash_functions_ = hash_functions if hash_functions is not None else [djb2, fnv1a]

    def clear(self) -> None:
        self.bit_vector_ = [False] * self.bit_size_

    def contains(self, key: str) -> bool:
        for hash in self.hash_functions_:
            if not self.bit_vector_[hash(key) % self.bit_size_]:
                return False
        return True

    def add(self, key: str) -> None:
        for hash in self.hash_functions_:
            self.bit_vector_[hash(key) % self.bit_size_] = True