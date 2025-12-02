# Ejemplos de Uso - API del Editor GDAT

## Uso Básico del LectorGDAT

### Abrir un archivo GDAT

```cpp
using namespace EditorDungeon;

// Crear instancia del lector
LectorGDAT^ lector = gcnew LectorGDAT();

// Abrir archivo
if (lector->AbrirArchivo("C:\\DM2\\GRAPHICS.DAT")) {
    // Archivo abierto correctamente
    InformacionGDAT^ info = lector->ObtenerInformacion();
    
    // Mostrar información
    Console::WriteLine("Número de entradas: " + info->numeroEntradas);
    Console::WriteLine("Endianness: " + (info->littleEndian ? "Little" : "Big"));
}
```

### Iterar sobre todas las entradas

```cpp
InformacionGDAT^ info = lector->ObtenerInformacion();

for (int i = 0; i < info->entradas->Count; i++) {
    EntradaGDAT^ entrada = info->entradas[i];
    
    Console::WriteLine(String::Format(
        "Entrada {0}: {1} bytes - {2}",
        i,
        entrada->tamanio,
        entrada->ObtenerNombreAmigable()
    ));
}
```

### Exportar una entrada específica

```cpp
// Exportar la entrada 5 a un archivo
if (lector->ExportarEntrada(5, "C:\\Temp\\entrada_5.bin")) {
    Console::WriteLine("Entrada exportada correctamente");
}
```

### Importar datos a una entrada

```cpp
// Importar datos desde un archivo a la entrada 5
if (lector->ImportarEntrada(5, "C:\\Temp\\nueva_entrada_5.bin")) {
    Console::WriteLine("Entrada importada correctamente");
    
    // Guardar los cambios
    lector->GuardarArchivo("C:\\DM2\\GRAPHICS_MODIFICADO.DAT");
}
```

### Modificar datos de una entrada manualmente

```cpp
InformacionGDAT^ info = lector->ObtenerInformacion();

// Obtener entrada
EntradaGDAT^ entrada = info->entradas[10];

// Crear nuevos datos
array<unsigned char>^ nuevosDatos = gcnew array<unsigned char>(100);
for (int i = 0; i < 100; i++) {
    nuevosDatos[i] = (unsigned char)i;
}

// Reemplazar datos
entrada->datos = nuevosDatos;
entrada->tamanio = nuevosDatos->Length;

// Guardar cambios
lector->GuardarArchivo("C:\\DM2\\GRAPHICS_MODIFICADO.DAT");
```

## Trabajo con Paletas

### Cargar paleta desde la entrada 0

```cpp
InformacionGDAT^ info = lector->ObtenerInformacion();
PaletaColores^ paleta = info->paleta;

// La paleta se carga automáticamente desde la entrada 0
// Acceder a un color específico
System::Drawing::Color color = paleta->ObtenerColor(15);
Console::WriteLine(String::Format("Color 15: R={0}, G={1}, B={2}", 
    color.R, color.G, color.B));
```

### Modificar la paleta

```cpp
PaletaColores^ paleta = info->paleta;

// Cambiar el color en el índice 10 a rojo puro
paleta->EstablecerColor(10, 255, 0, 0);

// Cambiar el color en el índice 11 a verde puro
paleta->EstablecerColor(11, 0, 255, 0);

// Cambiar el color en el índice 12 a azul puro
paleta->EstablecerColor(12, 0, 0, 255);
```

### Exportar paleta a archivo

```cpp
// Crear datos de paleta en formato GDAT
List<unsigned char>^ datosPaleta = gcnew List<unsigned char>();

for (int i = 0; i < 256; i++) {
    System::Drawing::Color color = paleta->ObtenerColor(i);
    datosPaleta->Add((unsigned char)i);  // Índice
    datosPaleta->Add(color.R);            // Rojo
    datosPaleta->Add(color.G);            // Verde
    datosPaleta->Add(color.B);            // Azul
}

// Guardar a archivo
array<unsigned char>^ arrayPaleta = datosPaleta->ToArray();
System::IO::File::WriteAllBytes("C:\\Temp\\paleta.bin", arrayPaleta);
```

## Análisis de Datos

### Detectar tipo de entrada

```cpp
EntradaGDAT^ entrada = info->entradas[50];

if (entrada->datos != nullptr && entrada->tamanio > 0) {
    // Analizar los primeros bytes
    unsigned char primerByte = entrada->datos[0];
    unsigned char segundoByte = entrada->datos[1];
    
    // Heurística simple para detectar imágenes
    if (entrada->tamanio > 10) {
        // Posible imagen si tiene un header reconocible
        Console::WriteLine("Posible imagen detectada");
    }
}
```

### Buscar entradas por tamaño

```cpp
// Buscar todas las entradas mayores a 10KB
List<int>^ entradasGrandes = gcnew List<int>();

for (int i = 0; i < info->entradas->Count; i++) {
    if (info->entradas[i]->tamanio > 10240) {
        entradasGrandes->Add(i);
    }
}

Console::WriteLine("Entradas mayores a 10KB: " + entradasGrandes->Count);
```

### Calcular estadísticas

```cpp
int tamanioTotal = 0;
int tamanioMinimo = Int32::MaxValue;
int tamanioMaximo = 0;

for each (EntradaGDAT^ entrada in info->entradas) {
    tamanioTotal += entrada->tamanio;
    if (entrada->tamanio < tamanioMinimo) tamanioMinimo = entrada->tamanio;
    if (entrada->tamanio > tamanioMaximo) tamanioMaximo = entrada->tamanio;
}

int tamanioPromedio = tamanioTotal / info->entradas->Count;

Console::WriteLine("Tamaño total: " + tamanioTotal + " bytes");
Console::WriteLine("Tamaño promedio: " + tamanioPromedio + " bytes");
Console::WriteLine("Tamaño mínimo: " + tamanioMinimo + " bytes");
Console::WriteLine("Tamaño máximo: " + tamanioMaximo + " bytes");
```

## Operaciones Avanzadas

### Clonar una entrada

```cpp
// Clonar la entrada 5 a la entrada 6
EntradaGDAT^ origen = info->entradas[5];
EntradaGDAT^ destino = info->entradas[6];

// Copiar datos
destino->datos = gcnew array<unsigned char>(origen->tamanio);
Array::Copy(origen->datos, destino->datos, origen->tamanio);
destino->tamanio = origen->tamanio;

// Copiar metadatos
destino->categoria = origen->categoria;
destino->clase1 = origen->clase1;
destino->clase2 = origen->clase2;
destino->tipo = origen->tipo;
```

### Insertar nueva entrada

```cpp
// Crear nueva entrada
EntradaGDAT^ nuevaEntrada = gcnew EntradaGDAT();
nuevaEntrada->datos = gcnew array<unsigned char>(256);
nuevaEntrada->tamanio = 256;

// Llenar con datos de ejemplo
for (int i = 0; i < 256; i++) {
    nuevaEntrada->datos[i] = (unsigned char)i;
}

// Agregar al final
info->entradas->Add(nuevaEntrada);
info->numeroEntradas = info->entradas->Count;
```

### Eliminar entrada (vaciarla)

```cpp
// Vaciar la entrada 10
EntradaGDAT^ entrada = info->entradas[10];
entrada->datos = gcnew array<unsigned char>(0);
entrada->tamanio = 0;
```

### Intercambiar dos entradas

```cpp
// Intercambiar entradas 5 y 10
EntradaGDAT^ temp = info->entradas[5];
info->entradas[5] = info->entradas[10];
info->entradas[10] = temp;
```

## Validación y Verificación

### Verificar integridad del archivo

```cpp
bool VerificarIntegridad(LectorGDAT^ lector) {
    InformacionGDAT^ info = lector->ObtenerInformacion();
    
    // Verificar número de entradas
    if (info->numeroEntradas <= 0 || info->numeroEntradas > 65535) {
        return false;
    }
    
    // Verificar que todas las entradas tengan datos válidos
    for each (EntradaGDAT^ entrada in info->entradas) {
        if (entrada->tamanio < 0) {
            return false;
        }
        
        if (entrada->tamanio > 0 && entrada->datos == nullptr) {
            return false;
        }
        
        if (entrada->datos != nullptr && entrada->datos->Length != entrada->tamanio) {
            return false;
        }
    }
    
    return true;
}
```

### Comparar dos archivos GDAT

```cpp
bool CompararArchivos(String^ archivo1, String^ archivo2) {
    LectorGDAT^ lector1 = gcnew LectorGDAT();
    LectorGDAT^ lector2 = gcnew LectorGDAT();
    
    if (!lector1->AbrirArchivo(archivo1) || !lector2->AbrirArchivo(archivo2)) {
        return false;
    }
    
    InformacionGDAT^ info1 = lector1->ObtenerInformacion();
    InformacionGDAT^ info2 = lector2->ObtenerInformacion();
    
    // Comparar número de entradas
    if (info1->numeroEntradas != info2->numeroEntradas) {
        return false;
    }
    
    // Comparar cada entrada
    for (int i = 0; i < info1->entradas->Count; i++) {
        EntradaGDAT^ e1 = info1->entradas[i];
        EntradaGDAT^ e2 = info2->entradas[i];
        
        if (e1->tamanio != e2->tamanio) {
            return false;
        }
        
        // Comparar datos byte por byte
        for (int j = 0; j < e1->tamanio; j++) {
            if (e1->datos[j] != e2->datos[j]) {
                return false;
            }
        }
    }
    
    return true;
}
```

## Manejo de Errores

### Ejemplo completo con manejo de errores

```cpp
try {
    LectorGDAT^ lector = gcnew LectorGDAT();
    
    // Intentar abrir archivo
    if (!lector->AbrirArchivo("C:\\DM2\\GRAPHICS.DAT")) {
        throw gcnew Exception("No se pudo abrir el archivo");
    }
    
    // Verificar integridad
    if (!VerificarIntegridad(lector)) {
        throw gcnew Exception("El archivo está corrupto");
    }
    
    // Realizar operaciones
    InformacionGDAT^ info = lector->ObtenerInformacion();
    
    // Exportar entrada
    if (!lector->ExportarEntrada(5, "C:\\Temp\\entrada_5.bin")) {
        throw gcnew Exception("No se pudo exportar la entrada");
    }
    
    Console::WriteLine("Operación completada con éxito");
}
catch (Exception^ ex) {
    Console::WriteLine("Error: " + ex->Message);
    MessageBox::Show("Error: " + ex->Message, "Error", 
        MessageBoxButtons::OK, MessageBoxIcon::Error);
}
```
