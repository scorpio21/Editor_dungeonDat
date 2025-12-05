#pragma once

// Definiciones de estructuras para archivos GDAT de Dungeon Master

namespace EditorDungeon {

// Tipos de formato de imagen
enum class FormatoImagen {
  C4 = 0,     // 4 bits por pixel comprimido
  C8 = 1,     // 8 bits por pixel comprimido
  SEGA = 2,   // Formato Sega
  FMTOWNS = 3 // Formato FM-Towns
};

// Tipos de datos en GDAT
enum class TipoDato { IMAGEN = 0, RAW = 1, ESCENA = 2 };

// Tipos de sonido
enum class TipoSonido {
  NINGUNO = 0,
  SND5SND6 = 1,
  SND3 = 2,
  SND7 = 3,
  SNDA = 4,
  SND9 = 5
};

// Estructura de entrada GDAT
public
ref struct EntradaGDAT {
  unsigned char categoria;
  unsigned char clase1;
  unsigned char clase2;
  unsigned char tipo;
  unsigned char indice1;
  unsigned char indice2;

  int tamanio;
  array<unsigned char> ^ datos;

  EntradaGDAT() {
    categoria = 0;
    clase1 = 0;
    clase2 = 0;
    tipo = 0;
    indice1 = 0;
    indice2 = 0;
    tamanio = 0;
    datos = nullptr;
  }

  System::String ^ ObtenerNombreAmigable() {
    return System::String::Format("Cat:{0:X2} C1:{1:X2} C2:{2:X2} Tipo:{3:X2}",
                                  categoria, clase1, clase2, tipo);
  }

  System::String ^ ObtenerNombreTipo() {
    switch (tipo) {
    case 0x00:
      return "Name";
    case 0x01:
      return "Image";
    case 0x02:
      return "Text";
    case 0x05:
      return "Description";
    case 0x08:
      return "Sound";
    case 0x0B:
      return "Metadata";
    default:
      return System::String::Format("Type {0:X2}", tipo);
    }
  }

  System::String ^ ObtenerNombreCategoria() {
    switch (categoria) {
    case 0x00:
      return "Technical Data";
    case 0x01:
      return "Interface - Main Screen";
    case 0x02:
      return "Creatures";
    case 0x03:
      return "Messages";
    case 0x04:
      return "Music (HMP format)";
    case 0x05:
      return "Main Menu and Credits";
    case 0x06:
      return "Credits";
    case 0x07:
      return "Interface - Character Sheet";
    case 0x08:
      return "Dungeon Graphics";
    case 0x09:
      return "Wall Ornates";
    case 0x0A:
      return "Floor Ornates";
    case 0x0B:
      return "Door Ornates";
    case 0x0C:
      return "Door Buttons";
    case 0x0D:
      return "Missiles";
    case 0x0E:
      return "Doors";
    case 0x0F:
      return "Creatures";
    case 0x10:
      return "Weapons";
    case 0x11:
      return "Clothes";
    case 0x12:
      return "Scrolls";
    case 0x13:
      return "Potions";
    case 0x14:
      return "Chests";
    case 0x15:
      return "Miscellaneous";
    case 0x16:
      return "Champions";
    case 0x17:
      return "Skullkeep and Weather";
    case 0x18:
      return "Teleporter";
    case 0x1A:
      return "Dialog boxes";
    default:
      return System::String::Format("Category {0:X2}", categoria);
    }
  }
};

// Estructura de paleta de colores
public
ref struct PaletaColores {
  array<System::Drawing::Color> ^ colores;

  PaletaColores() {
    colores = gcnew array<System::Drawing::Color>(256);
    // Inicializar con colores por defecto
    for (int i = 0; i < 256; i++) {
      colores[i] = System::Drawing::Color::FromArgb(i, i, i);
    }
  }

  void EstablecerColor(int indice, unsigned char r, unsigned char g,
                       unsigned char b) {
    if (indice >= 0 && indice < 256) {
      colores[indice] = System::Drawing::Color::FromArgb(r, g, b);
    }
  }

  System::Drawing::Color ObtenerColor(int indice) {
    if (indice >= 0 && indice < 256) {
      return colores[indice];
    }
    return System::Drawing::Color::Black;
  }
};

// Información del archivo GDAT
public
ref struct InformacionGDAT {
  System::String ^ rutaArchivo;
  int numeroEntradas;
  bool littleEndian;
  FormatoImagen formatoImagen;
  TipoDato tipoDato;
  TipoSonido tipoSonido;

  System::Collections::Generic::List<EntradaGDAT ^> ^ entradas;
  PaletaColores ^ paleta;

  InformacionGDAT() {
    rutaArchivo = "";
    numeroEntradas = 0;
    littleEndian = true;
    formatoImagen = FormatoImagen::C4;
    tipoDato = TipoDato::IMAGEN;
    tipoSonido = TipoSonido::NINGUNO;
    entradas = gcnew System::Collections::Generic::List<EntradaGDAT ^>();
    paleta = gcnew PaletaColores();
  }
};
} // namespace EditorDungeon
