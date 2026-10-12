"""Tests for interviews/ipv4_iterator

Run from anywhere:
    cpunit ipv4_iterator --py
or from this folder:
    python3 -m unittest -v test_ipv4_iterator
"""
import os
import sys
import unittest

sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
from solution import IPv4Iterator, cidr_range, to_int, to_str


class TestIPv4(unittest.TestCase):

    def test_parse_format(self):
        for ip in ["0.0.0.0", "255.255.255.255", "10.0.1.254"]:
            self.assertEqual(to_str(to_int(ip)), ip)
        for bad in ["1.2.3", "1.2.3.256", "a.b.c.d", "1.2.3.4.5", "1..2.3"]:
            with self.assertRaises(ValueError): to_int(bad)

    def test_ranges(self):
        self.assertEqual(list(IPv4Iterator("255.255.14.254", "255.255.15.1")),
                         ["255.255.14.254", "255.255.14.255", "255.255.15.0", "255.255.15.1"])
        self.assertEqual(list(IPv4Iterator("0.0.1.1", "0.0.0.255")), ["0.0.1.1", "0.0.1.0", "0.0.0.255"])
        self.assertEqual(list(IPv4Iterator("1.1.1.1", "1.1.1.1")), ["1.1.1.1"])
        self.assertEqual(list(IPv4Iterator("255.255.255.254", "255.255.255.255")), ["255.255.255.254", "255.255.255.255"])
        it = IPv4Iterator("1.1.1.1", "1.1.1.2")
        out = []
        while it.hasNext(): out.append(it.next())
        self.assertEqual(out, ["1.1.1.1", "1.1.1.2"])
        with self.assertRaises(StopIteration): it.next()

    def test_cidr(self):
        self.assertEqual(list(IPv4Iterator.from_cidr("192.168.1.0/30")), ["192.168.1.0", "192.168.1.1", "192.168.1.2", "192.168.1.3"])
        self.assertEqual(list(IPv4Iterator.from_cidr("192.168.1.2/31", False)), ["192.168.1.3", "192.168.1.2"])
        self.assertEqual(list(IPv4Iterator.from_cidr("10.1.2.3/32")), ["10.1.2.3"])
        self.assertEqual(cidr_range("1.2.3.4/0"), (0, 2**32 - 1)) # never walk this one
        self.assertEqual(cidr_range("10.1.2.3/16"), (to_int("10.1.0.0"), to_int("10.1.255.255")))


if __name__ == "__main__":
    unittest.main()
