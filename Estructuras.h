#pragma once

// Definiciones de estructuras para archivos GDAT de Dungeon Master

namespace EditorDungeon {

	// Tipos de formato de imagen
	enum class FormatoImagen {
		C4 = 0,          // 4 bits por pixel comprimido
		C8 = 1,          // 8 bits por pixel comprimido
		SEGA = 2,        // Formato Sega
		FMTOWNS = 3      // Formato FM-Towns
	};

	// Tipos de datos en GDAT
	enum class TipoDato {
		IMAGEN = 0,
		RAW = 1,
		ESCENA = 2
	};

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
	public ref struct EntradaGDAT {
		unsigned char categoria;
		unsigned char clase1;
		unsigned char clase2;
		unsigned char tipo;
		unsigned char indice1;
		unsigned char indice2;
		
		int tamanio;
		array<unsigned char>^ datos;

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

		System::String^ ObtenerNombreAmigable() {
			return System::String::Format("Cat:{0:X2} C1:{1:X2} C2:{2:X2} Tipo:{3:X2}", 
				categoria, clase1, clase2, tipo);
		}
	};

	// Estructura de paleta de colores
	public ref struct PaletaColores {
		array<System::Drawing::Color>^ colores;

		PaletaColores() {
			colores = gcnew array<System::Drawing::Color>(256);
			// Inicializar con colores por defecto
			for (int i = 0; i < 256; i++) {
				colores[i] = System::Drawing::Color::FromArgb(i, i, i);
			}
		}

		void EstablecerColor(int indice, unsigned char r, unsigned char g, unsigned char b) {
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
	public ref struct InformacionGDAT {
		System::String^ rutaArchivo;
		int numeroEntradas;
		bool littleEndian;
		FormatoImagen formatoImagen;
		TipoDato tipoDato;
		TipoSonido tipoSonido;
		
		System::Collections::Generic::List<EntradaGDAT^>^ entradas;
		PaletaColores^ paleta;

		InformacionGDAT() {
			rutaArchivo = "";
			numeroEntradas = 0;
			littleEndian = true;
			formatoImagen = FormatoImagen::C4;
			tipoDato = TipoDato::IMAGEN;
			tipoSonido = TipoSonido::NINGUNO;
			entradas = gcnew System::Collections::Generic::List<EntradaGDAT^>();
			paleta = gcnew PaletaColores();
		}
	};
}
