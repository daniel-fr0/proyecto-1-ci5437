from cuadros import *

cuadrosU = list(filter(lambda x: x[0] == 'U', esquinas))
cuadrosD = list(filter(lambda x: x[0] == 'D', esquinas))

print(cuadrosU)
print(cuadrosD)

proyecciones = []
for i in range(len(cuadros)):
	if not cuadros[i] in cuadrosU and not cuadros[i] in cuadrosD:
		proyecciones.append(f'project {i+1}')


with open('esquinasUD.txt', 'w') as f:
	for i in proyecciones:
		f.write(i + '\n')
	