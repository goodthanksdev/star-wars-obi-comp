# Print the disassembly around guest addresses. usage: python show.py cnk.asm ADDR[:before[:after]] ...
import re, sys, bisect

lines = open(sys.argv[1], encoding='utf-8', errors='replace').read().splitlines()
addrs, idx = [], []
for i, l in enumerate(lines):
    m = re.match(r'^\s+([0-9a-f]+):', l)
    if m:
        addrs.append(int(m.group(1), 16))
        idx.append(i)
for spec in sys.argv[2:]:
    parts = spec.split(':')
    a = int(parts[0], 16)
    before = int(parts[1]) if len(parts) > 1 else 12
    after = int(parts[2]) if len(parts) > 2 else 12
    k = bisect.bisect_left(addrs, a)
    k = min(k, len(addrs) - 1)
    print(f'=== {a:#x}')
    for l in lines[idx[max(0, k - before)]: idx[min(len(idx) - 1, k + after)] + 1]:
        print(l.strip()[:100])
