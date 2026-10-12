from collections import Counter


# 347. Top K Frequent Elements [Medium]
# Bucket sort by frequency: a frequency is at most n, so bucket[f] lists the
# values seen f times, and reading buckets from n down is O(n), no heap.
class Solution:
    def topKFrequent(self, nums: list[int], k: int) -> list[int]:
        n = len(nums)
        bucket = [[] for _ in range(n + 1)]
        for x, f in Counter(nums).items():
            bucket[f].append(x)
        ans = []
        for f in range(n, 0, -1):
            for x in bucket[f]:
                ans.append(x)
                if len(ans) == k: return ans
        return ans
