# Guía de Desarrollo - Editor GDAT

## Próximos Pasos de Desarrollo

### 1. Decodificación de Imágenes

Para implementar la vista previa de imágenes, necesitarás:

#### Formato C4 (4-bit comprimido)

- Cada pixel usa 4 bits
- Requiere paleta de 16 colores
- Algoritmo de descompresión basado en RLE (Run-Length Encoding)
- Referencia: `DM2ImageComp.cpp` líneas 258-329 en DM2GDED

#### Formato C8 (8-bit comprimido)

- Cada pixel usa 8 bits
- Requiere paleta de 256 colores
- Algoritmo de descompresión similar a C4
- Referencia: `DM2ImageComp.cpp` líneas 330-383 en DM2GDED

#### Pasos para implementar

1. Crear clase `DecodificadorImagenes` en nuevo archivo `DecodificadorImagenes.h`
2. Implementar método `DecodificarC4(array<unsigned char>^ datos, int ancho, int alto, PaletaColores^ paleta)`
3. Implementar método `DecodificarC8(array<unsigned char>^ datos, int ancho, int alto, PaletaColores^ paleta)`
4. Retornar `System::Drawing::Bitmap^` para mostrar en `vistaPrevia`

### 2. Editor de Paletas

Crear un formulario secundario `EditorPaleta.h`:

- Grid de 16x16 para mostrar los 256 colores
- Selector de color para modificar cada entrada
- Botones para importar/exportar paletas
- Vista previa en tiempo real de cómo afecta a las imágenes

### 3. Análisis Automático de Tipos

Implementar en `GDATReader.h`:

```cpp
TipoDato DetectarTipoDato(array<unsigned char>^ datos) {
    // Analizar los primeros bytes para determinar el tipo
    // Referencia: CGDATFDH::DecideImageFormat en GDAT.cpp línea 558
}
```

### 4. Soporte para Sonidos

- Investigar formatos SND3, SND5, SND6, SND7, SND9, SNDA
- Implementar reproductor básico con `System::Media::SoundPlayer`
- Permitir exportar a formatos estándar (WAV, MP3)

### 5. Editor de Textos

- Decodificar textos según el idioma (EN, JP, FR, DE, ES, IT)
- Implementar codificación especial de DM2 (referencia: `DM2TextEncoder.cpp`)
- Crear editor de texto enriquecido con vista previa

## Estructura de Clases Recomendada

```
EditorDungeon/
├── Core/
│   ├── GDATReader.h              # Lectura/escritura de archivos
│   ├── Estructuras.h             # Estructuras de datos
│   └── Utilidades.h              # Funciones auxiliares
├── Decodificadores/
│   ├── DecodificadorImagenes.h   # Decodificación de imágenes
│   ├── DecodificadorSonidos.h    # Decodificación de sonidos
│   └── DecodificadorTextos.h     # Decodificación de textos
├── Formularios/
│   ├── FormularioPrincipal.h     # Ventana principal
│   ├── EditorPaleta.h            # Editor de paletas
│   ├── EditorImagen.h            # Editor de imágenes
│   └── EditorTexto.h             # Editor de textos
└── Main.cpp                       # Punto de entrada
```

## Algoritmos Clave de DM2GDED

### Lectura de archivo GDAT (loadFrom)

```
1. Abrir archivo en modo binario
2. Leer número de entradas (2 bytes)
3. Leer tabla de tamaños (2 bytes × número de entradas)
4. Leer datos de cada entrada secuencialmente
5. Detectar formato automáticamente si está habilitado
```

### Descompresión de imágenes C4

```
1. Leer header de imagen (ancho, alto)
2. Inicializar buffer de salida
3. Leer 4 bits a la vez
4. Si es valor literal: escribir pixel
5. Si es código de repetición: repetir último pixel N veces
6. Continuar hasta completar ancho × alto pixels
```

### Carga de paleta

```
1. La entrada 0 suele contener la paleta
2. Formato: [índice][R][G][B] (4 bytes por color)
3. Cargar hasta 256 colores
4. Valores RGB en rango 0-255
```

## Consejos de Depuración

### Verificar archivos GDAT

- Los archivos válidos tienen número de entradas entre 1 y 65535
- La suma de tamaños no debe exceder el tamaño del archivo
- La primera entrada suele ser la paleta (tamaño múltiplo de 4)

### Problemas comunes

1. **Endianness incorrecto**: Las imágenes se ven distorsionadas
   - Solución: Verificar si es Little o Big Endian

2. **Paleta incorrecta**: Los colores no coinciden
   - Solución: Verificar que la entrada 0 sea la paleta correcta

3. **Tamaño de imagen incorrecto**: Imagen cortada o con basura
   - Solución: Verificar ancho y alto en el header de la imagen

## Referencias del Código Original

### Archivos clave en DM2GDED

- `GDAT.cpp`: Clase principal para manejo de archivos
- `DM2ImageComp.cpp`: Compresión/descompresión de imágenes
- `DM2Palo.h`: Definición de paletas
- `GDATDef.h`: Constantes y definiciones
- `DMGHLci.h`: Estructuras de datos de bajo nivel

### Constantes importantes

```cpp
#define GDFF_PICFMT_C4      0x0000  // Formato 4-bit
#define GDFF_PICFMT_C8      0x1000  // Formato 8-bit
#define GDFF_PICFMT_FMTOWNS 0x2000  // Formato FM-Towns
#define GDFF_PICFMT_SEGA    0x3000  // Formato Sega
#define GDFF_LITTLE_ENDIAN  0x0100  // Little Endian
```

## Testing

### Archivos de prueba recomendados

1. `GRAPHICS.DAT` - Contiene la mayoría de gráficos del juego
2. `GTEXT.DAT` - Contiene textos del juego
3. `GSOUND.DAT` - Contiene efectos de sonido

### Casos de prueba

- [ ] Abrir archivo válido
- [ ] Abrir archivo corrupto (debe mostrar error)
- [ ] Exportar entrada
- [ ] Importar entrada
- [ ] Guardar archivo modificado
- [ ] Verificar integridad después de guardar

## Notas Adicionales

- Mantener compatibilidad con archivos originales de DM1 y DM2
- No modificar el formato de archivo original
- Hacer backups antes de guardar cambios
- Validar datos antes de escribir al archivo
- Usar nombres de variables en español según las reglas del proyecto
