import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
from matplotlib import animation
from matplotlib.patches import Rectangle
import sys

fig = plt.figure()
ax = plt.gca()

ymin= -1
ymax = 1

fileLines = []
if len(sys.argv) > 2:
    filename = sys.argv[1]
else:
    filename = 'malloc_historics.txt'
with open(filename, 'r') as doc:
    fileLines = [line for line in doc.readlines()]

def init():
    return []

def print_page(ax, base):
    return ax.add_patch(Rectangle((0, base), 4096, 100, color='lightgray'))

def print_mmap(ax, base, size):
    base //= 4096
    global ymin, ymax
    if ymin == -1 or ymin > base:
        ymin = 100 * base
    if 100 * (base + size // 4096) > ymax:
        ymax = 100 * (base + size // 4096)
    for i in range(size // 4096):
        yield print_page(ax, (base + i) * 100)
    plt.ylim(ymin - 50, ymax + 50)

def hide_page(ax, base):
    return ax.add_patch(Rectangle((0, base), 4096, 100, color='white'))

def print_munmap(ax, base, size):
    base //= 4096
    for i in range(size // 4096):
        yield hide_page(ax, (base + i) * 100)

def print_malloc(ax, base, size):
    color = list(mcolors.TABLEAU_COLORS.keys())[(base ^ size) % len(mcolors.TABLEAU_COLORS)]
    if (base // 4096 == (base + size) // 4096):
        yield ax.add_patch(Rectangle((base % 4096, 100 * (base // 4096)), size, 100, color=color))
        return
    yield ax.add_patch(Rectangle((base % 4096, 100 * (base // 4096)), 4096 - base % 4096, 100, color=color))
    size -= 4096 - base % 4096
    while (size - 4096) > 0:
        base += 4096
        size -= 4096
        yield ax.add_patch(Rectangle((0, (base // 4096) * 100)), 4096, 100, color=color)
    base += 4096
    yield ax.add_patch(Rectangle((0, 100 * (base // 4096)), size, 100, color=color))

def print_free(ax, base, size):
    color='lightgray'
    if (base // 4096 == (base + size) // 4096):
        yield ax.add_patch(Rectangle((base % 4096, 100 * (base // 4096)), size, 100, color=color))
        return
    yield ax.add_patch(Rectangle((base % 4096, 100 * (base // 4096)), 4096 - base % 4096, 100, color=color))
    size -= 4096 - base % 4096
    while (size - 4096) > 0:
        base += 4096
        size -= 4096
        yield ax.add_patch(Rectangle((0, (base // 4096) * 100)), 4096, 100, color=color)
    base += 4096
    yield ax.add_patch(Rectangle((0, 100 * (base // 4096)), size, 100, color=color))


ACTIONS = {
    "mmap": print_mmap,
    "munmap": print_munmap,
    "malloc": print_malloc,
    "free": print_free
    }

patches = []
def animate(i):
    print("frame:", i, end='\r')
    BASE_COLOR_N = 0
    line = fileLines[i]
    act, base, size = line.split()
    if act in ACTIONS:
        patches.extend(ACTIONS[act](ax, int(base, base=16), int(size)))
    return patches

plt.xlim(-1, 4097)
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               frames=len(fileLines), interval=5, blit=True)

FFwriter = animation.FFMpegWriter(fps=60)
anim.save('animation.mp4', writer=FFwriter)
print('')
