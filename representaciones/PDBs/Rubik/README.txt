el cubo viene representado como un arreglo de cuadros,
como hay 6 caras con 9 cuadros
cada cara tiene 9 cuadros, 
el total seria de 54 cuadros

Pero no se cuentan los 6 del medio, ya que no se mueven
entonces el total seria de 48 cuadros

- UBR - UFR - UFL - UBL 
- FUR - FDR - FDL - FUL 
- RUB - RDB - RDF - RUF 
- BUL - BDL - BDR - BUR 
- LUF - LDF - LDB - LUB 
- DFR - DBR - DBL - DFL

Los PDBS seran divididos como se plantea en el paper de Richard Korf,
este tiene en cuenta los "cubies" que son los cubos pequeños que forman el cubo,
en este caso hay 27 cubies, restando los 6 del medio y el que esta en el nucleo,
quedan 20 cubies:

Se dividen en 2 grupos: 8 de las esquinas y 12 de los bordes

Para reducir el problema mas todavia, estos grupos se subdividen en 2 grupos mas:
Uno resuelve la mitad de los colores del cubo, y el otro la otra mitad