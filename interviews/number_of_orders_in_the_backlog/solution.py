from heapq import heappop, heappush

MOD = 10**9 + 7


# 1801. Number of Orders in the Backlog [Medium]
# An order book: buys in a max-heap (prices negated), sells in a min-heap.
# A new order trades against the best opposite price while prices cross,
# one heap entry at a time; whatever is left joins its own side.
class Solution:
    def getNumberOfBacklogOrders(self, orders: list[list[int]]) -> int:
        buy, sell = [], [] # [-price, amount], [price, amount]
        for price, amount, type in orders:
            if type == 0: # buy: match the cheapest sell <= price
                while amount and sell and sell[0][0] <= price:
                    t = min(amount, sell[0][1])
                    amount -= t
                    sell[0][1] -= t
                    if sell[0][1] == 0: heappop(sell)
                if amount: heappush(buy, [-price, amount])
            else:         # sell: match the highest buy >= price
                while amount and buy and -buy[0][0] >= price:
                    t = min(amount, buy[0][1])
                    amount -= t
                    buy[0][1] -= t
                    if buy[0][1] == 0: heappop(buy)
                if amount: heappush(sell, [price, amount])
        return sum(a for _, a in buy + sell) % MOD
