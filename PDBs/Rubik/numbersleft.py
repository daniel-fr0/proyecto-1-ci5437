n = list(range(1, 49, 2))
n = list(map(lambda x: f'project {x}', n))
project = set()
print(n)

with open('BORDES.txt', 'r') as f:
	for line in f:
		if line.strip() in n:
			n.remove(line.strip())
for i in n:
	print(i)

project.update(n)
print(project)

n = list(range(1, 49, 2))
n = list(map(lambda x: f'project {x}', n))
with open('BORDES2.txt', 'r') as f:
	for line in f:
		if line.strip() in n:
			n.remove(line.strip())

project.update(n)

for i in sorted(project, key=lambda x: int(x.split()[1])):
	print(i)


mantener = [
	1, 3, 17, 25, 19, 23, 11, 31, 41, 43, 13, 21
]

quitar = filter(lambda x: x not in mantener, range(1, 49, 2))


print("QUITAR")
for i in quitar:
	print(f'project {i}')