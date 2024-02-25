# Informe

A continuacion se detallan detalles sobre la implementacion de los problemas, las decisiones tomadas y los resultados obtenidos.

## Representaciones de los problemas
   
### N-puzzle
Las representaciones de ambos problemas, funcionan usando las reglas básicas para la representación de problemas en psvn. En las reglas, se trabaja con la casilla “b” que representa la casilla vacia, y dependiendo de su posición, la regla correspondiente intercambia dicha casilla con una de sus casillas adyacentes dependiendo del caso. Para las esquinas solo tenemos 2 posibles movimientos, para los bordes 3 posibles movimientos y para el resto 4. Por ejemplo para la casilla de la esquina superior izquierda, tenemos dos posibles movimientos: derecha y abajo, las cuales se representan como (para el 15-puzzle):

b X - - - - - - - - - - - - - - => X b - - - - - - - - - - - - - -              (derecha)

b - - - X - - - - - - - - - - - => X - - - b - - - - - - - - - - -              (abajo)

### Cubo de Rubik

Se usa la representación dada en el material de apoyo, la cual trabaja con un arreglo de 48 posiciones, que representa la posición actual del cubo usando las caras del mismo. En dicha representación se encuentra una explicación mas detalla de dicha implementnacion.

### Top spin

Se usa el generador dado en el material de apoyo, llamado “genTopSpinBasic.cpp”, el cual dado dos números N y K como parámetros, nos da una representación del problema con N tokens y tamaño K del rotador. Esta representación se centra en solo tomar en cuenta el rotador dependiendo de la “zona” del arreglo en la cual se va a rotar, con lo cual tendremos N posibles estados objetivo puesto que cualquier configuración del arreglo que tenga los números en orden tal que una vez se llegue a la posición N-1, el siguiente token sea el que represente al 0, es un estado objetivo válido.

### Torre de Hanoi con 4 astas

Se usa el generador dado en el material de apoyo, llamado “genHanoi.cpp” el cual dado dos números  P y D como parámetros nos da una representación del problema con P astas y D discos, usando una representación del estado de cada disco con una codificación en binario para saber si esta o no en una asta.

## Arboles de búsqueda

### Resultados

Usando los archivos `distSummary.cpp` (buscar **sin poda**) y `distSummaryPP.cpp` (buscar **con poda de padres**), se corrieron las diferentes representaciones de cada problema.
Cada problema se dejo correr hasta que la memoria se llenara y el programa se cerrara, o hasta que se llegara a un estado objetivo. En todos los problemas tomó menos de 3 minutos llegar a un estado objetifo o llenar la memoria. Los resultados obtenidos se pueden encontrar en el archivo:

https://docs.google.com/spreadsheets/d/1KhgxJZJG3csaIUZU_vmI8zaUU5XLx48pKe7m43dvi6U/edit#gid=0

Aqui se puede ver un apartado para graficas de **factor de ramificacion**, **numero de estados totales** y **profundidad alcanzada** de los problemas.

El archivo `analisis.py` ayuda a sacar el numero de estados totales y el factor de ramificacion. Este mismo archivo recibe como entrada un archivo donde se haya registrado el resultado de una busqueda, y devuelve el numero de estados totales y el factor de ramificacion.

### Análisis

#### Factor de ramificación

En cada problema se pudo observar el mismo patron, cada problema tiene un factor de ramificación que se mantiene constante en caso de no usar poda, y en caso de usar poda, el factor de ramificación disminuye considerablemente. Esto se debe a que en el caso de no usar poda, se generan muchos estados que son iguales a otros ya generados, lo que aumenta el factor de ramificación. En el caso de usar poda, se evita generar estados que ya se han generado, lo que disminuye el factor de ramificación.

#### Número de estados y profundidad alcanzada

En este caso, como varia mucho el tiempo que se pudo correr cada problema, no se puede hacer una comparación directa entre cada ejecución para estas variables de forma individual. Sin embargo, teniendo en cuenta las dos variables en conjunto, se puede tener una idea del tamaño de los problemas. 

Particularmente en el caso de **las torres de hanoi** podemos ver que este problema (*con poda de padres*) logra alcanzar una profundidad mucho mayor que los demás problemas con cualquier tipo de busqueda, y al mismo tiempo se ve que el número de estados alcanzados no es muy diferente al de los demás problemas. Esto, junto al hecho de que este problema es el que tiene el factor de ramificación más bajo, nos da una idea de que el arból de búsqueda de este problema es muy profundo. Pero como el arbol no es muy ancho, el número de estados totales no es muy grande y es manejable para la memoria.

Cabe destacar que el problema de **hanoi con 4 astas y 12 discos** fue el único que completó la busqueda, con poda de padres, por lo que logró alcanzar todos los estados posibles. Esto quiere decir que podria ser util construir un **PDB** para este problema con **todos** los estados posibles.