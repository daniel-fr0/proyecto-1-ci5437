# Informe
- [Como ejecutar](#como-ejecutar)
  - [Generar PDB](#generar-pdb)
  - [Generar programa de busqueda](#generar-programa-de-busqueda)
	- [Para cualquier problema](#para-cualquier-problema)
	- [Para el N-puzzle](#para-el-n-puzzle)
  - [Ejecutar busqueda](#ejecutar-busqueda)
- [Representaciones de los problemas](#representaciones-de-los-problemas)
- [Arboles de búsqueda](#arboles-de-búsqueda)
- [Heuristicas](#heuristicas)
  - [Manhattan](#manhattan)
  - [PDBs aditivas](#pdbs-aditivas)
  - [Maximo de PDBs](#maximo-de-pdbs)
- [PDBs](#pdbs)
  - [N-puzzle](#n-puzzle)
  - [Hanoi](#hanoi)
  - [Topspin](#topspin)
  - [Cubo de Rubik](#cubo-de-rubik)
- [Resultados de busquedas](#resultados-de-busquedas)


## Como ejecutar
Para cada problema se deben correr los comandos en el directorio correspondiente, dentro de la carpeta `problemas`.

### Generar PDB
Para generar los PDB de un problema se debe correr en la terminal lo siguiente en el directorio del problema:
```bash
	make pdb
```
Para limpiar los pdbs se puede usar el comando:
```bash
	make clean_pdb
```

### Generar programa de busqueda

#### Para cualquier problema
Para compilar un programa de busqueda se debe correr en la terminal lo siguiente:
```bash
	make <problema>.<busqueda>
```
Donde `<problema>` corresponde al nombre del archivo `.psvn` que representa al problema, y `<busqueda>` es la terminacion correspondiente al tipo de busqueda que se quiere hacer, ya sea `A` o `IDA` para *A\** o *IDA\** respectivamente.

#### Para el N-puzzle
En este caso se debe especificar la heuristica que se quiere usar.
```bash
	make <problema>.<heuristica>.<busqueda>
```
Donde `<heuristica>` corresponde a la heuristica que se quiere usar, ya sea `man` para la heuristica de Manhattan o `sum` para la heuristica aditiva con PDBs.


### Ejecutar busqueda
Para ejecutar un programa de busqueda se debe correr en la terminal lo siguiente:
```bash
	./programa <instancia>
```
Donde `programa` corresponde al nombre del archivo ejecutable que se genero en el paso anterior, y `<instancia>` es el nombre del archivo `.txt` que contiene la instancia del problema que se quiere resolver. El formato del archivo corresponde a la representacion de un estado del problema que se tomara como estado inicial.

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

Nota: mas tarde se pudo ver que la representacion compacta de **top spin**, resultaba en un factor de ramificacion mas bajo, y el problema de **top spin 12-4** fue el unico que logro alcanzar todos los estados posibles, con poda de padres. A pesar de esto, el problema de **hanoi 4-12** sigue siendo el que alcanza una profundidad mayor y el que tiene el factor de ramificacion mas bajo.

## Heuristicas

### Manhattan
Para los problemas del **15-puzzle** y **24-puzzle** se implemento la heuristica de Manhatan en el archivo `heuristicaManhattan.cpp`. 
Esta fue implementada con el algoritmo que utiliza una tabla con las distancias de cada casilla a su posición final, y suma todas estas distancias para obtener el valor de la heurística.
Las tablas son inicializadas antes de la busqueda que se vaya a realizar.

### PDBs aditivas
Para los problemas del **15-puzzle** y **24-puzzle** se implementaron heurísticas aditivas usando PDBs.
Donde se toma la suma de las distancias dadas por cada PDB.
Estas heurísticas se implementaron en los archivos `heuristicaSum3.cpp` y `heuristicaSum6.cpp` para el **15-puzzle** y **24-puzzle** respectivamente.

### Maximo de PDBs
Para los problemas de **hanoi**, **topspin** y **cubo de rubik** se implementaron heurísticas que toman el máximo de varias PDBs.

## PDBs

### N-puzzle
Para el **15-puzzle** se abstrajo el problema a 3 pdbs donde en cada uno se mapean 10 valores de variables hacia 0, simulando un problema reducido donde se cuentan con solamente 5 fichas.
La heuristica implementada para esto se encuentra en el archivo `heuristicaSum3.cpp`.

Para el **24-puzzle** se abstrajo el problema a 6 pdbs donde en cada uno se mapean 20 valores de variables hacia 0, simulando un problema reducido donde se cuentan con solamente 4 fichas.
La heuristica implementada para esto se encuentra en el archivo `heuristicaSum6.cpp`.

### Hanoi
Para cada sub-problema de la torre de hanoi se abstrajo el problema a 2 pdbs donde en cada uno se proyectan la mitad de las variables, simulando un problema reducido donde se cuentan con solamente la mitad de los discos.
La heuristica implementada para esto se encuentra en el archivo `heuristicaHanoi.cpp`.

En el caso del problema de **hanoi con 4 astas y 12 discos**, como el tamaño del problema es manejable, se puede generar un PDB con todos los estados posibles. Para esto se debe crear el pdb con:
```bash
	make completo.pdb
```
Y luego el programa de busqueda con:
```bash
	make hanoi12-4.completo.<busqueda>
```

### Topspin
Para los problemas con **12** y **14** tokens se abstrajo el problema a 2 pdbs donde en cada uno se mapean la mitad de los valores de variables hacia 0, simulando un problema reducido donde se cuentan con la mitad de los tokens indistinguibles uno de otro.
La heuristica implementada para esto se encuentra en el archivo `heuristicaTopSpin.cpp`.

Para el problema con **17** tokens se abstrajo el problema a 3 pdbs dado que con 2 pdbs no se lograba reducir el tamaño del problema a un tamaño manejable para la memoria. En cada uno se mapean 10, 10 y 11 valores de variables hacia 0, simulando un problema reducido donde se cuentan con solamente 6, 6 y 5 tokens indistinguibles uno de otro respectivamente.
La heuristica implementada para esto se encuentra en el archivo `heuristicaTopSpin17-4.cpp`.

### Cubo de Rubik
Para el problema del **cubo de rubik** se dividieron los pdbs en dos grupos, los cubies que conforman las *esquinas* del cubo, y los cubies que conforman los *bordes* del cubo, inspirados en el paper "Additive Pattern Databases" de Felner et al. que se incluye en el material de apoyo. 

En el caso de los bordes, se proyectaron todas las variables que corresponden a los cubies de las esquinas, pero como el tamaño del pdb seguia siendo muy grande, se dividio en 2 pdbs mas pequeños, uno donde se mapean 3 de los colores hacia blanco, y otro donde se mapean los otros 3 colores hacia amarillo, teniendo dos subproblemas con solo 3 colores indistinguibles uno de otro.

En el caso de las esquinas se pudo crear un solo pdb para todas las esquinas, aunque el tamaño del pdb resultante es muy grande, por lo que primero se trabajo con dos pdbs mas pequeños, aplicando la misma idea que con los bordes.

La heuristica implementada para esto se encuentra en el archivo `heuristicaRubik.cpp`. Y utiliza los pdbs `ESQUINAS.pdb`, `bordesW.pdb` y `bordesY.pdb`. Los cuales son generados con el comando:
```bash
	make pdb
```

Los pdbs `esquinasW.pdb` y `esquinasY.pdb` ya no son considerados en la heuristica final, pero se pueden generar con:
```bash
	make esquinasW.pdb &&
	make esquinasY.pdb
```

## Algoritmos informados
Se implementaron los algoritmos de busqueda informada **A\*** y **IDA\*** en los archivos `A-estrella.cpp` e `IDA-estrella.cpp` respectivamente. En ambos casos se utilizan las heuristicas implementadas en los archivos correspondientes a cada problema. Y la ejecución de estos programas requiere como entrada la direccion de un archivo de instancia del problema que se quiere resolver. 

En el caso de *IDA\**, como el algoritmo explora estados duplicados, en el caso de problemas con muchos duplicados, se podria quedar explorando todo el arbol y nunca terminar. Incluso, como usa mucha menos memoria que *A\**, no va a ocurrir que el programa se cierre por falta de memoria. Por lo que en la implementacion de *IDA\** se incluye un tiempo limite para la busqueda. Se puede especificar un tiempo limite en segundos para la busqueda, si no se especifica se toma un tiempo limite de 5 minutos por defecto.

Para ejecutar un programa de *A\**:
```bash
	./programa.A <instancia>
```
Para ejecutar un programa de *IDA\**:
```bash
	./programa.IDA [tiempo limite en segundos] <instancia>
```


Para registrar los resultados, en ambos algoritmos se lleva una cuenta de los nodos visitados por distancia y totales, cada vez que se explora una nueva distancia a partir del estado inicial, se imprime en pantalla la cantidad de estados visitados hasta esa distancia. Luego de imprimir se reinicia la cuenta de visitados por esa distancia, para empezar la cuenta para la siguiente distancia.

Esto hace que la informacion registrada por estos algoritmos sea distinta a la registrada anteriormente con los algoritmos no informados, dado que en estos algoritmos la prioridad es por *f-valor* y *cota de f-valor* para *A\** e *IDA\** respectivamente, y no por la profundidad del arbol de busqueda. 

Por lo tanto hay que notar que en los resultados no se tiene cuantos nodos hay en cada profundidad, sino cuantos nodos se visitaron desde que se alcanzó una profundidad hasta que se alcanza la siguiente.

## Resultados de busquedas
Para cada problema se corrieron las busquedas con las diferentes heuristicas y se registraron los resultados en las subcarpetas de cada problema. Para ello se utilizaron los casos de pruebas en la carpeta `benchmarks`.

## Casos de prueba
Se generaron casos de prueba para cada problema, los cuales se encuentran en la carpeta `casosDePrueba`.

## Conclusiones
**IDA\*** y **A\*** son algoritmos muy utiles para resolver problemas de busqueda en espacios de estados grandes, y con heuristicas bien diseñadas, se pueden resolver problemas que de otra forma serian imposibles de resolver. Ambos algoritmos tienen ventajas y desventajas, y se pueden complementar entre si. **IDA\*** es mas eficiente en memoria, pero puede quedarse explorando un arbol de busqueda muy grande si hay muchos estados duplicados. **A\*** es mas eficiente en tiempo, pero puede quedarse sin memoria si el arbol de busqueda es muy ancho.

En el caso de problemas donde la busqueda con **A\*** no termina por falta de memoria, se puede usar **IDA\*** con un tiempo limite para la busqueda, y si el tiempo limite se alcanza, se puede aumentar el tiempo limite y volver a correr la busqueda. De esta forma se puede ir explorando el arbol de busqueda de forma incremental, y se puede ir registrando el progreso de la busqueda en cada corrida.

En casos donde la memoria no era un problema, se pudo ver que **A\*** conseguia llegar a la misma solucion que **IDA\*** explorando muchos menos nodos. En general, para todas las pruebas que se realizaron se pudo ver que **A\*** exploraba muchos menos nodos que **IDA\***, y que en general, el tiempo que se tardaba en llegar a la solucion era mucho menor con **A\*** que con **IDA\***.

Notamos lo importante que es tener una buena heuristica para resolver problemas de busqueda, y que en general, las heuristicas aditivas con PDBs son muy utiles para resolver problemas de busqueda en espacios de estados grandes. En general, se obtuvieron mejores resultados con las heuristicas aditivas con PDBs que con la heuristica de Manhattan, y se pudo ver que en general, mientras mas grande es el PDB que se usa, mejor es la heuristica que se obtiene. Esto es claro, porque es mas informacion la que se tiene para estimar el costo de llegar a la solucion. El caso trivial es donde se tiene un PDB que contiene todos los estados posibles, en este caso se tiene la mejor heuristica posible, que es la distancia real al estado objetivo. Esto se puede ver con las pruebas en **hanoi 4-12** con el pdb `completo.pdb`, donde se obtiene siempre la solucion directa, visitando siempre el minimo numero de nodos para la solucion.