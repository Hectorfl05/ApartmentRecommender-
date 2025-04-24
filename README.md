# Sistema de Recomendación de Apartamentos 🏢➡️🛒

Un programa en C++ que analiza un archivo **JSON Line** con datos de apartamentos y negocios cercanos, para recomendar el apartamento óptimo basado en la proximidad a los negocios deseados.

## 📌 Descripción

El sistema procesa un archivo de entrada en formato **JSON Line** que contiene:
- Un listado de apartamentos (`input1`), donde cada uno tiene asociados ciertos negocios (ej: "supermercado", "farmacia", etc.).
- Un listado de negocios requeridos (`input2`). 

El algoritmo calcula:
1. **Distancia mínima** desde cada apartamento hasta cada negocio deseado.
2. **Apartamento recomendado**: El que minimiza la suma total de pasos y, en caso de empate, el que reduce la máxima distancia individual.

## 🛠️ Dependencias

- **Librería JSON para C++**: 
  - Se utiliza [`jsoncpp`](https://github.com/open-source-parsers/jsoncpp) para parsear archivos JSON Line.
  - ⚠️ **Requisito**: Instalar la librería externamente antes de ejecutar el programa. Si no está instalada, el código fallará.
    ```bash
    # Ejemplo de instalación en Linux (Ubuntu)
    sudo apt-get install libjsoncpp-dev
    ```

## 📦 Archivos Incluidos

1. **Ejecutable**: 
   - Se proporciona un binario compilado (`RecomendadorApartamentos`) para pruebas rápidas (en releases).
2. **Código Fuente**:
   - `main.cpp`: Contiene la lógica de recomendación y manejo de archivos.
   - `Apartment.h`: Clase que define la estructura de un apartamento y sus negocios asociados.
3. **Ejemplo de JSON Line**:
   ```json
   {"input1": [{"farmacia": true, "supermercado": false}, ...], "input2": ["farmacia", ...]}
