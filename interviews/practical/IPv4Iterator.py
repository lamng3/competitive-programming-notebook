# Iterate IPv4 addresses, forwards or backwards, either over a range of two
# addresses or over a CIDR block such as "192.168.1.0/30".
# An address is a 32-bit number written as four bytes, so: parse to an int,
# count, and format back. The iterator never stores the addresses it walks.


def to_int(ip: str) -> int:
    parts = ip.split(".")
    if len(parts) != 4: raise ValueError("bad address " + ip)
    x = 0
    for p in parts:
        if not p.isdigit() or int(p) > 255: raise ValueError("bad address " + ip)
        x = x << 8 | int(p)
    return x


def to_str(x: int) -> str:
    return ".".join(str(x >> s & 255) for s in (24, 16, 8, 0))


# first and last address of a CIDR block: the top `prefix` bits are fixed
def cidr_range(block: str) -> tuple:
    ip, prefix = block.split("/")
    host = 32 - int(prefix)
    if not 0 <= host <= 32: raise ValueError("bad prefix " + block)
    lo = to_int(ip) >> host << host # clear the host bits
    return lo, lo + (1 << host) - 1


class IPv4Iterator:

    # start .. end inclusive; walks backwards when start > end
    def __init__(self, start: str, end: str):
        self.cur, self.end = to_int(start), to_int(end)
        self.step = 1 if self.cur <= self.end else -1
        self.done = False

    @classmethod
    def from_cidr(cls, block: str, increasing: bool = True):
        lo, hi = cidr_range(block)
        return cls(to_str(lo), to_str(hi)) if increasing else cls(to_str(hi), to_str(lo))

    def hasNext(self) -> bool:
        return not self.done

    def next(self) -> str:
        if self.done: raise StopIteration
        ip = to_str(self.cur)
        if self.cur == self.end: self.done = True
        else: self.cur += self.step
        return ip

    def __iter__(self):
        return self

    def __next__(self) -> str:
        return self.next()
