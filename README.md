![alt text](http://dinopianito.com.ar/assets/img/top-logo.png)

## Documentación
Se encuentra en el archivo `Informe TLA.pdf`

## Para ejecutar el proyecto

```bash
git clone https://github.com/fedemamone/TLA.git && cd TLA
chmod 777 ./install.sh
./install.sh
chmod 777 ./compile.sh
./compile.sh source.dino destination.c
```

Finalmente, podrá ejecutar su código compilándolo con gcc o clang de manera habitual:

```bash
gcc destination.c -o destination
```

## Programas de ejemplo

Se encuentran bajo la carpeta `tests`

## Para generar los .c, compilar y ejecutar automáticamente los tests

```bash
chmod 777 ./generateAndRunTests.sh
./generateAndRunTests.sh
```
La salida de los 5 tests se verá en la consola.

## Requerimientos

Tener instalado gcc, touch, yacc y lex


## Autores
* Clozza, Nicolás
* Mamone, Federico
* Tay, Lucía
* Varela Ballesteros, Catalina
