Informe Proyecto 1

1) Representaciones:
N-puzzle:
Las representaciones de ambos problemas, funcionan usando las reglas básicas para la representación de problemas en psvn. En las reglas, se trabaja con la casilla “b” que representa la casilla vacia, y dependiendo de su posición, la regla correspondiente intercambia dicha casilla con una de sus casillas adyacentes dependiendo del caso. Para las esquinas solo tenemos 2 posibles movimientos, para los bordes 3 posibles movimientos y para el resto 4. Por ejemplo para la casilla de la esquina superior izquierda, tenemos dos posibles movimientos: derecha y abajo, las cuales se representan como (para el 15-puzzle):
b X - - - - - - - - - - - - - - => X b - - - - - - - - - - - - - -              (derecha)
b - - - X - - - - - - - - - - - => X - - - b - - - - - - - - - - -              (abajo)

Cubo de Rubik:
Se usa la representación dada en el material de apoyo, la cual trabaja con un arreglo de 48 posiciones, que representa la posición actual del cubo usando las caras del mismo. En dicha representación se encuentra una explicación mas detalla de dicha implementnacion.

Top spin:
Se usa el generador dado en el material de apoyo, llamado “genTopSpinBasic.cpp”, el cual dado dos números N y K como parámetros, nos da una representación del problema con N tokens y tamaño K del rotador. Esta representación se centra en solo tomar en cuenta el rotador dependiendo de la “zona” del arreglo en la cual se va a rotar, con lo cual tendremos N posibles estados objetivo puesto que cualquier configuración del arreglo que tenga los números en orden tal que una vez se llegue a la posición N-1, el siguiente token sea el que represente al 0, es un estado objetivo válido.

Torre de Hanoi con 4 astas:
Se usa el generador dado en el material de apoyo, llamado “genHanoi.cpp” el cual dado dos números  P y D como parámetros nos da una representación del problema con P astas y D discos, usando una representación del estado de cada disco con una codificación en binario para saber si esta o no en una asta.

2) Arboles de búsqueda:

Usando los archivos distSummary.cpp (buscar sin poda) y distSummaryPP.cpp (buscar con poda), se corrieron las diferentes representaciones de cada problema, obteniendo los siguientes resultados en la tabla:
https://docs.google.com/spreadsheets/d/1KhgxJZJG3csaIUZU_vmI8zaUU5XLx48pKe7m43dvi6U/edit#gid=0
