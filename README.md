# Laboratorio 02: Contenedor concurrente basado en locks

## Problem 1 - Multithread Max Element in an array
`Description:` An implementation of a multithread max element calculator.

`Route:` ./p1

Compile using the `Makefile` on a UNIX system.
```
    $ make
```

`Question:` ¿Qué enfoque es mejor entre utilizar locks y variables atómicas?

`Answer:` Se pudo observar que al aumentar el número de threads no necesariamente disminuyó el tiempo de ejecución del programa. Además, resultó más conveniente utilizar las variables atómicas, puesto que el programa que las utilizaba tuvo un menor tiempo de ejecución (esto se ve reflejado en el "AVERAGE_TIME" de cada programa). Finalmente, respecto al tamaño del arreglo, se pudo observar que al ser más grande (n > 2000) el incremente en el número de threads tenía un mayor impacto en la disminución del tiempo de ejecución.


### How to use this implementation

Run main_atomic.cpp and main_locks.cpp tests

    $ make run



## Problem 2 - Thread-safe stack

`Description:` A small implementation of a thread-safe stack written in C++.

`Route:` ./p2

Compile using the `Makefile` on a UNIX system.

    $ make

### How to use this implementation

Run a basic program with some threads

    $ make run-basic

**Run all tests**

You may want to run it to check the implementation.

    $ make test all-operations

**Run test by name**

You can test a specific stack operation (unit test)

    $ make test <testname>

Example: Run a unit test for the single pop operation

    $ make test single-pop

**List of test names**

These are all the posible test:

- single-pop
- single-push
- correct-items
- multiple-pop
- multiple-push

**Clean**

Clean executable files

    $ make clean