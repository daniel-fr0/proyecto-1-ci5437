from cuadros import *

cubiesUdiag=[
	'UBL', 'UFR', # U
	'FUR'		  # F
	'BUL',	  	  # B
	'LUB',		  # L
	'RUF',		  # R
]

cubiesDdiag=[
	'DFL', 'DBR', # D
	'FDL'		  # F
	'BDR',	  	  # B
	'LDF',		  # L
	'RDB',		  # R
]

proyecciones = []
for i in range(len(cuadros)):
	if not cuadros[i] in cubiesUdiag and not cuadros[i] in cubiesDdiag:
		proyecciones.append(f'project {i+1}')


with open('esquinasUD.txt', 'w') as f:
	for i in proyecciones:
		f.write(i + '\n')
	