import math

def obtener_valores(archivo):
	with open(archivo) as f:
		return [int(linea.split()[0]) for linea in f][:-1]


def media_geometrica(valores):
	producto = math.prod(valores)
	return producto ** (1.0 / len(valores))

valores = obtener_valores('resultado.txt')
print(valores)
ramificacion = [valores[i] / valores[i - 1] for i in range(1, len(valores))]
print("promedio", media_geometrica(ramificacion))
print("total", sum(valores))
