# Proyecto 1 – Árboles y Trie

Este proyecto es parte de la materia de Estructura de Datos.  
La idea principal es construir un sistema de carpetas y archivos usando un árbol general.  
Más adelante se agregarán funciones como mover nodos, renombrar, eliminar, buscar con Trie y guardar la información en un archivo JSON.

## Progreso del Día 1

Hoy organicé la estructura base del proyecto y preparé los archivos principales que voy a usar más adelante.

Lo que avancé fue:

- Creé las clases `Nodo`, `Arbol` y `Trie` con sus estructuras básicas.
- Preparé el archivo `main.cpp` para comprobar que el proyecto compila correctamente.
- Agregué la librería `json.hpp`, ya que será necesaria cuando implemente la persistencia en JSON.
- Dejé todo listo para comenzar a programar las funciones del árbol en el Día 2.

Este día fue principalmente de preparación y organización del proyecto.

## Progreso del Día 2

Hoy empecé a implementar las funciones principales del árbol.  
Lo que avancé fue lo siguiente:

- Programé el constructor del árbol, que crea la raíz con el nombre "root".
- Implementé el destructor para liberar correctamente todos los nodos del árbol.
- Agregué la función `buscarRuta()`, que permite encontrar un nodo usando rutas como `/Carpeta/Subcarpeta`.
- Modifiqué el `main.cpp` para hacer algunas pruebas básicas y confirmar que la búsqueda funciona.

Con esto ya tengo lo necesario para continuar con las operaciones de creación y movimiento en el Día 3.
