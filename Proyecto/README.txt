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

## Progreso del Día 2-3

Hoy empecé a implementar las funciones principales del árbol.  
Lo que avancé fue lo siguiente:

- Programé el constructor del árbol, que crea la raíz con el nombre "root".
- Implementé el destructor para liberar correctamente todos los nodos del árbol.
- Agregué la función `buscarRuta()`, que permite encontrar un nodo usando rutas como `/Carpeta/Subcarpeta`.
- Modifiqué el `main.cpp` para hacer algunas pruebas básicas y confirmar que la búsqueda funciona.

## Progreso del Día 3

Hoy implementé las funciones básicas para crear nodos dentro del árbol:

- `crearCarpeta()` permite añadir carpetas dentro de una ruta existente.
- `crearArchivo()` hace lo mismo pero para archivos, incluyendo su contenido.
- Agregué validaciones simples para evitar crear nodos en rutas inexistentes.
- Probé las funciones desde `main.cpp` creando algunas carpetas de ejemplo.

Con esto, el árbol ya puede crecer de forma dinámica.

---

## Progreso del Día 4

En este día implementé la persistencia del proyecto utilizando JSON.  
Ahora el árbol se puede guardar en un archivo `.json` y también cargarlo después.

Las funciones nuevas fueron:

- `guardarJSON()` → convierte el árbol completo a un JSON.
- `cargarJSON()` → reconstruye el árbol desde el archivo.
- Implementé funciones internas para convertir de Nodo a JSON y viceversa.

Probé el guardado y carga desde el `main.cpp` y funciona correctamente.

