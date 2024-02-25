import math, sys

def obtener_valores(archivo):
	with open(archivo) as f:
		valores = []
		# match line pattern "<int> states at distance <int>"
		for linea in f:
			if "states at distance" in linea:
				valores.append(int(linea.split()[0]))
	return valores

def media_geometrica(valores):
	producto = math.prod(valores)
	return producto ** (1.0 / len(valores))

if len(sys.argv) != 2:
	print("Uso: python analisis.py <archivo>")
	sys.exit(1)

valores = obtener_valores(sys.argv[1])
ramificacion = [valores[i] / valores[i - 1] for i in range(1, len(valores))]
print("ramificacion", ramificacion)
print("promedio", media_geometrica(ramificacion))
print("total", sum(valores))
