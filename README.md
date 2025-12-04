# Editor de Archivos GDAT - Dungeon Master

Editor de escritorio para archivos `.dat` de Dungeon Master 1 y Dungeon Master 2, desarrollado en C++/CLI con Windows Forms.

## Descripción

Este proyecto es un editor visual que permite abrir, visualizar, modificar y guardar archivos GDAT (Graphics DAT) utilizados en los juegos Dungeon Master 1 y 2. Los archivos `.dat` contienen recursos del juego como imágenes, sonidos, textos y otros datos.

## Características

### Implementadas

- ✅ Abrir archivos `.dat` de DM1/DM2
- ✅ Visualizar lista de entradas con índices y tamaños
- ✅ Exportar entradas individuales a archivos binarios
- ✅ Importar entradas desde archivos externos
- ✅ Guardar archivos modificados
- ✅ Soporte para Little Endian y Big Endian
- ✅ Interfaz gráfica intuitiva con Windows Forms

### En desarrollo

- 🔄 Decodificación y vista previa de imágenes (formatos C4, C8, FM-Towns, Sega)
- 🔄 Editor de paletas de colores
- 🔄 Reproducción de sonidos
- 🔄 Editor de textos
- 🔄 Análisis automático de tipos de datos

## Estructura del Proyecto

```text
   editor_dungeon/
   ├── EditorDungeon.vcxproj      # Archivo de proyecto de Visual Studio
   ├── Main.cpp                    # Punto de entrada de la aplicación
   ├── FormularioPrincipal.h       # Definición del formulario principal
   ├── FormularioPrincipal.cpp     # Implementación del formulario principal
   ├── FormularioPrincipal.resx    # Recursos del formulario
   ├── GDATReader.h                # Clase para leer/escribir archivos GDAT
├── GDATReader.cpp              # Implementación del lector GDAT
├── Estructuras.h               # Estructuras de datos para GDAT
├── Data/                       # Directorio para archivos de datos de prueba
└── README.md                   # Este archivo
```

## Requisitos

- **Visual Studio 2022** o superior
- **Windows 10/11**
- **.NET Framework 4.8** o superior
- **C++/CLI** habilitado en Visual Studio

## Compilación

### Opción 1: Visual Studio (Recomendado)

1. Abre el archivo `EditorDungeon.vcxproj` en **Visual Studio 2022**
2. Asegúrate de tener instalados los siguientes componentes:
   - **Desarrollo de escritorio con C++**
   - **Compatibilidad con C++/CLI**
   - **Windows 10 SDK**
3. Selecciona la configuración (Debug o Release) y la plataforma (x86 o x64)
4. Compila el proyecto (F7 o Ctrl+Shift+B)
5. Ejecuta la aplicación (F5)

### Opción 2: Línea de comandos con MSBuild

Si prefieres compilar desde la línea de comandos, puedes usar el script `build.bat`:

```batch
build.bat
```

Este script:

- Busca automáticamente MSBuild en tu instalación de Visual Studio 2022
- Compila el proyecto en modo Debug x64
- Muestra el resultado de la compilación

### Requisitos de compilación

- **Visual Studio 2022** (Community, Professional o Enterprise)
- **Platform Toolset v143** (incluido con VS 2022)
- **.NET Framework 4.8**
- **Windows 10 SDK**

## Uso

### Abrir un archivo GDAT

1. Ve al menú **Archivo → Abrir** (Ctrl+O)
2. Selecciona un archivo `.dat` de Dungeon Master
3. El archivo se cargará y mostrará la lista de entradas

### Exportar una entrada

1. Selecciona una entrada de la lista
2. Haz clic en el botón **Exportar** o ve a **Edición → Exportar entrada**
3. Elige la ubicación y nombre del archivo de destino
4. La entrada se guardará como archivo binario

### Importar una entrada

1. Selecciona la entrada que deseas reemplazar
2. Haz clic en el botón **Importar** o ve a **Edición → Importar entrada**
3. Selecciona el archivo binario a importar
4. La entrada se actualizará con los nuevos datos

### Guardar cambios

- **Guardar** (Ctrl+S): Guarda los cambios en el archivo actual
- **Guardar como**: Guarda una copia con un nuevo nombre

## Formato de Archivos GDAT

Los archivos GDAT tienen la siguiente estructura:

```text
[2 bytes] Número de entradas (N)
[2*N bytes] Tabla de tamaños (una palabra de 16 bits por entrada)
[Variable] Datos de cada entrada (secuencialmente)
```

### Tipos de datos soportados

- **Imágenes**: Formatos C4 (4-bit comprimido), C8 (8-bit comprimido), FM-Towns, Sega
- **Sonidos**: SND3, SND5, SND6, SND7, SND9, SNDA
- **Textos**: Codificados en varios idiomas (EN, JP, FR, DE, ES, IT)
- **Datos RAW**: Datos binarios sin formato específico

## Referencia

Este proyecto se basa en el análisis del código fuente de **DM2GDED** (Dungeon Master 2 Graphics Data Editor), respetando las estructuras y formatos originales.

## Historial de Cambios

### Versión 1.2 (2025-12-04)

- **CORRECCIÓN CRÍTICA**: Arreglada la lectura de archivos GDAT DM1 (Big Endian)
  - La Entrada 0 ahora se lee correctamente como 4 bytes (DWORD) en lugar de 2 bytes
  - Esto soluciona el problema de desfase que causaba que todos los datos se leyeran incorrectamente
- Reemplazado ListView por DataGridView para mejor visualización de datos
  - Ahora se muestran columnas para: Índice, Categoría, Clase1, Clase2, Tipo, Tamaño y Descripción
  - Formato similar al programa original DM2GDED
  - Valores mostrados en formato hexadecimal para mejor legibilidad
- Mejorada la organización del código en `GDATReader.h`

### Versión 1.1 (2025-12-03)

- Mejorada la lectura de archivos GDAT con formato DM2
- Agregado soporte para firma 0x8005 (DM2 Little Endian)
- Mejorada la detección automática de endianness
- Agregado mensaje de depuración al abrir archivos
- Verificación de consistencia de datos al cargar archivos
- Corrección en la lectura de la tabla de tamaños (entrada 0 usa 4 bytes, resto 2 bytes)

### Versión 1.0 (2025-12-02)

- Versión inicial del proyecto
- Funcionalidad básica de lectura/escritura de archivos GDAT
- Interfaz gráfica con Windows Forms
- Exportación e importación de entradas individuales

## Licencia

Este proyecto es de código abierto y se proporciona tal cual, sin garantías de ningún tipo.

## Autor

Desarrollado como herramienta para la comunidad de modding de Dungeon Master.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, abre un issue o pull request en el repositorio.
