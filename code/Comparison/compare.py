# For runtime measuring
import datetime
import os

# For memory measuring
import psutil

# string for test
string = 'AAAAABBBBCCCDDE'


class NodeTree(object):

    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right

    def children(self):
        return self.left, self.right

    def nodes(self):
        return self.left, self.right


def huffman_code_tree(passed_node, bin_string=''):
    if type(passed_node) is str:
        return {passed_node: bin_string}
    (l, r) = passed_node.children()
    d = dict()
    d.update(huffman_code_tree(l, bin_string + '0'))
    d.update(huffman_code_tree(r, bin_string + '1'))
    return d


def algo():
    freq = {}
    for c in string:
        if c in freq:
            freq[c] += 1
        else:
            freq[c] = 1

    freq = sorted(freq.items(), key=lambda x: x[1], reverse=True)

    nodes = freq

    while len(nodes) > 1:
        (key1, c1) = nodes[-1]
        (key2, c2) = nodes[-2]
        nodes = nodes[:-2]
        node = NodeTree(key1, key2)
        nodes.append((node, c1 + c2))

        nodes = sorted(nodes, key=lambda x: x[1], reverse=True)

    res = huffman_code_tree(nodes[0][0])


def test():
    a = datetime.datetime.now()
    for _ in range(1000):
        algo()
    process = psutil.Process(os.getpid())
    b = datetime.datetime.now()
    delta = b - a

    return delta, process


def main(cases=100):
    dt = 0
    mm = 0
    for _ in range(cases):
        dtf, mmf = test()
        dt += dtf.microseconds
        mm += mmf.memory_info().rss
    dt /= cases
    mm /= cases
    print('Program runtime is about ', dt / 1000, 'microseconds')

    print('Total process memory usage in bytes: ', mm)
    print('In KiloBytes: ', mm / 1024)
    print('In MegaBytes: ', mm / (1024 * 1024))


if __name__ == '__main__':
    main()

os.system("pause")
