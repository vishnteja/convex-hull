import numpy as np
import collections
from weakref import proxy

# Class for Ordered Set, Needed to preserve order in sets created

class Link(object):
    __slots__ = 'prev', 'next', 'key', '__weakref__'

class OrderedSet(collections.MutableSet):
    'Set the remembers the order elements were added'
    # Big-O running times for all methods are the same as for regular sets.
    # The internal self.__map dictionary maps keys to links in a doubly linked list.
    # The circular doubly linked list starts and ends with a sentinel element.
    # The sentinel element never gets deleted (this simplifies the algorithm).
    # The prev/next links are weakref proxies (to prevent circular references).
    # Individual links are kept alive by the hard reference in self.__map.
    # Those hard references disappear when a key is deleted from an OrderedSet.

    def __init__(self, iterable=None):
        self.__root = root = Link()         # sentinel node for doubly linked list
        root.prev = root.next = root
        self.__map = {}                     # key --> link
        if iterable is not None:
            self |= iterable

    def __len__(self):
        return len(self.__map)

    def __contains__(self, key):
        return key in self.__map

    def add(self, key):
        # Store new key in a new link at the end of the linked list
        if key not in self.__map:
            self.__map[key] = link = Link()            
            root = self.__root
            last = root.prev
            link.prev, link.next, link.key = last, root, key
            last.next = root.prev = proxy(link)

    def discard(self, key):
        # Remove an existing item using self.__map to find the link which is
        # then removed by updating the links in the predecessor and successors.        
        if key in self.__map:        
            link = self.__map.pop(key)
            link.prev.next = link.next
            link.next.prev = link.prev

    def __iter__(self):
        # Traverse the linked list in order.
        root = self.__root
        curr = root.next
        while curr is not root:
            yield curr.key
            curr = curr.next

    def __reversed__(self):
        # Traverse the linked list in reverse order.
        root = self.__root
        curr = root.prev
        while curr is not root:
            yield curr.key
            curr = curr.prev

    def pop(self, last=True):
        if not self:
            raise KeyError('set is empty')
        key = next(reversed(self)) if last else next(iter(self))
        self.discard(key)
        return key

    def __repr__(self):
        if not self:
            return '%s()' % (self.__class__.__name__,)
        return '%s(%r)' % (self.__class__.__name__, list(self))

    def __eq__(self, other):
        if isinstance(other, OrderedSet):
            return len(self) == len(other) and list(self) == list(other)
        return not self.isdisjoint(other)
# def edge(p, q):
#     return ((p[0], p[1]), (q[0], q[1]))

out_points = np.loadtxt(fname="output_jarvis.txt")
unique_out1 = set()
x = []
y = []
for point in out_points:
    unique_out1.add((point[0], point[1]))

def write_(final, file_path):
    with open("./test/"+file_path+"_out.txt", "w") as f:
        for i in range(0, len(final)):
            f.write(("%s %s\n")%(final[i][0],final[i][1]))

def slo(unique_out1):
    slopes = {}
    for p1 in unique_out1:
        for p2 in unique_out1:
            temp = ''
            if p1[0] == p2[0]:
                temp = np.nan
            else:
                temp = float((p2[1]-p1[1])/(p2[0]-p1[0]))
            if temp not in slopes:
                slopes[temp] = []
            prev = slopes[temp]
            prev.append(p1)
            prev.append(p2)
            slopes[temp] = prev
    for key in slopes.keys():
        val = slopes[key]
        final = list(set(tuple(p) for p in val))
        # final = [f for f in final if f[0] != f[1]]
        sel = []
        for f in final:
            if f[0] == f[1]:
                continue
            else:
                sel.append(f)

        slopes[key] = sel
    print(len(slopes))


def orientation(a, b, c):

    res = (b[1] - a[1])*(c[0] - b[0]) - (b[0] - a[0]) * (c[1] - b[1])
    if res == 0:
        return True
    else:
        return False 

def n3(points):
    final = OrderedSet()
    for p1 in points:
        for p2 in points:
            if p1 != p2:
                for p3 in points:
                    if p3 != p1 and p3 != p2:
                        if orientation(p1, p2, p3):
                            final.add(p1)
                            final.add(p2)
                            final.add(p3)
    final = list(final)
    write_(final, "jarvis")
    return final



# print(len(n3(unique_out1)))
print(len(unique_out1))


out_points = np.loadtxt(fname="output_graham.txt")
unique_out2 = set()
x = []
y = []
for point in out_points:
    unique_out2.add((point[0], point[1]))
print(len(unique_out2))

out_points = np.loadtxt(fname="output_kps.txt")
unique_out3 = set()
x = []
y = []
for point in out_points:
    unique_out3.add((point[0], point[1]))
print(len(unique_out3))

if(unique_out1==unique_out2):
    print("J&G Equal")
if(unique_out2==unique_out3):
    print("G&K Equal")
if(unique_out1==unique_out3):
    print("J&K Equal")

