# 68. Text Justification [Hard]
# Greedy: take words while they fit with one space between them. Then spread
# the leftover spaces: every gap gets the same base, the leftmost gaps one more.
# The last line, and a line with one word, are left-justified instead.
class Solution:
    def fullJustify(self, words: list[str], maxWidth: int) -> list[str]:
        ans = []
        i, n = 0, len(words)
        while i < n:
            j, width = i + 1, len(words[i]) # line is words[i..j), width counts single spaces
            while j < n and width + 1 + len(words[j]) <= maxWidth:
                width += 1 + len(words[j])
                j += 1
            gaps = j - i - 1
            if j == n or gaps == 0:
                line = " ".join(words[i:j])
                ans.append(line + " " * (maxWidth - len(line)))
            else:
                spaces = maxWidth - (width - gaps) # every space on the line
                base, extra = divmod(spaces, gaps)
                line = ""
                for k in range(i, j - 1):
                    line += words[k] + " " * (base + (k - i < extra))
                ans.append(line + words[j - 1])
            i = j
        return ans
