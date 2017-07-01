import lxml.html
import sys
import os

root = lxml.html.fromstring(sys.stdin.read())

if len(sys.argv) != 2:
    print('Usage: {} path'.format(sys.argv[0]))
    exit(1)

inputs = []
outputs = []

for node in root.xpath('//pre'):
    if node.getprevious().text.startswith('入力例'):
        inputs.append(node.text)
    elif node.getprevious().text.startswith('出力例'):
        outputs.append(node.text)

if len(inputs) == 0 or len(inputs) != len(outputs):
    print('Invalid number of inputs and outputs: {} {}'.format(len(inputs), len(outputs)))
    exit(1)


path = sys.argv[1]


def make_dirs(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

make_dirs(os.path.join(path, 'input'))
make_dirs(os.path.join(path, 'output'))

for i, (ip, op) in enumerate(zip(inputs, outputs)):
    with open(os.path.join(path, 'input', str(i)), 'w') as f:
        f.write(ip.lstrip())
    with open(os.path.join(path, 'output', str(i)), 'w') as f:
        f.write(op.lstrip())
