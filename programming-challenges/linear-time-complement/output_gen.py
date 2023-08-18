import random

with open('input.txt', 'w') as f:
    for i in range(100):
        f.write(str(random.randint(0, 100)) + '\n')
