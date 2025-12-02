#pragma once

#include "Estructuras.h"
#include <fstream>

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

namespace EditorDungeon {

	// Clase para leer archivos GDAT de Dungeon Master 1 y 2
	public ref class LectorGDAT {
	private:
		InformacionGDAT^ informacion;
		bool archivoAbierto;

		// Leer palabra de 16 bits
		unsigned short LeerPalabra(array<unsigned char>^ buffer, int% posicion, bool littleEndian) {
			unsigned short valor;
			if (littleEndian) {
				valor = buffer[posicion] | (buffer[posicion + 1] << 8);
			}
			else {
				valor = (buffer[posicion] << 8) | buffer[posicion + 1];
			}
			posicion += 2;
			return valor;
		}

		// Leer palabra doble de 32 bits
		unsigned int LeerPalabraDoble(array<unsigned char>^ buffer, int% posicion, bool littleEndian) {
			unsigned int valor;
			if (littleEndian) {
				valor = buffer[posicion] | 
					   (buffer[posicion + 1] << 8) | 
					   (buffer[posicion + 2] << 16) | 
					   (buffer[posicion + 3] << 24);
			}
			else {
				valor = (buffer[posicion] << 24) | 
					   (buffer[posicion + 1] << 16) | 
					   (buffer[posicion + 2] << 8) | 
					   buffer[posicion + 3];
			}
			posicion += 4;
			return valor;
		}

		// Detectar si el archivo es Little Endian
		bool DetectarEndianness(array<unsigned char>^ encabezado) {
			// Por defecto, DM2 usa Little Endian
			// Podemos detectarlo analizando el número de entradas
			return true;
		}

		// Cargar la paleta de colores desde la entrada 0
		void CargarPaleta(array<unsigned char>^ datosPaleta) {
			if (datosPaleta == nullptr || datosPaleta->Length < 4) {
				return;
			}

			int numColores = datosPaleta->Length / 4;
			if (numColores > 256) numColores = 256;

			for (int i = 0; i < numColores; i++) {
				int offset = i * 4;
				unsigned char indice = datosPaleta[offset];
				unsigned char r = datosPaleta[offset + 1];
				unsigned char g = datosPaleta[offset + 2];
				unsigned char b = datosPaleta[offset + 3];
				
				informacion->paleta->EstablecerColor(indice, r, g, b);
			}
		}

	public:
		LectorGDAT() {
			informacion = gcnew InformacionGDAT();
			archivoAbierto = false;
		}

		// Abrir y cargar un archivo GDAT
		bool AbrirArchivo(String^ rutaArchivo) {
			try {
				if (!File::Exists(rutaArchivo)) {
					return false;
				}

				informacion->rutaArchivo = rutaArchivo;
				
				// Leer todo el archivo en memoria
				array<unsigned char>^ datosArchivo = File::ReadAllBytes(rutaArchivo);
				
				if (datosArchivo->Length < 4) {
					return false;
				}

				// Detectar endianness
				informacion->littleEndian = DetectarEndianness(datosArchivo);

				// Leer número de entradas (primeros 2 bytes)
				int posicion = 0;
				informacion->numeroEntradas = LeerPalabra(datosArchivo, posicion, informacion->littleEndian);

				if (informacion->numeroEntradas <= 0 || informacion->numeroEntradas > 65535) {
					return false;
				}

				// Leer tabla de tamaños
				List<int>^ tamanios = gcnew List<int>();
				for (int i = 0; i < informacion->numeroEntradas; i++) {
					if (posicion + 2 > datosArchivo->Length) {
						return false;
					}
					int tamanio = LeerPalabra(datosArchivo, posicion, informacion->littleEndian);
					tamanios->Add(tamanio);
				}

				// Leer las entradas de datos
				informacion->entradas->Clear();
				for (int i = 0; i < informacion->numeroEntradas; i++) {
					EntradaGDAT^ entrada = gcnew EntradaGDAT();
					entrada->tamanio = tamanios[i];

					if (entrada->tamanio > 0) {
						if (posicion + entrada->tamanio > datosArchivo->Length) {
							return false;
						}

						entrada->datos = gcnew array<unsigned char>(entrada->tamanio);
						Array::Copy(datosArchivo, posicion, entrada->datos, 0, entrada->tamanio);
						posicion += entrada->tamanio;

						// Si es la primera entrada (índice 0), puede contener la paleta
						if (i == 0 && entrada->tamanio >= 4) {
							CargarPaleta(entrada->datos);
						}
					}

					informacion->entradas->Add(entrada);
				}

				archivoAbierto = true;
				return true;
			}
			catch (Exception^ ex) {
				System::Windows::Forms::MessageBox::Show(
					"Error al abrir archivo: " + ex->Message,
					"Error",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Error
				);
				return false;
			}
		}

		// Guardar archivo GDAT
		bool GuardarArchivo(String^ rutaArchivo) {
			try {
				if (informacion->entradas->Count == 0) {
					return false;
				}

				List<unsigned char>^ buffer = gcnew List<unsigned char>();

				// Escribir número de entradas
				unsigned short numEntradas = (unsigned short)informacion->entradas->Count;
				if (informacion->littleEndian) {
					buffer->Add((unsigned char)(numEntradas & 0xFF));
					buffer->Add((unsigned char)((numEntradas >> 8) & 0xFF));
				}
				else {
					buffer->Add((unsigned char)((numEntradas >> 8) & 0xFF));
					buffer->Add((unsigned char)(numEntradas & 0xFF));
				}

				// Escribir tabla de tamaños
				for each (EntradaGDAT^ entrada in informacion->entradas) {
					unsigned short tamanio = (unsigned short)entrada->tamanio;
					if (informacion->littleEndian) {
						buffer->Add((unsigned char)(tamanio & 0xFF));
						buffer->Add((unsigned char)((tamanio >> 8) & 0xFF));
					}
					else {
						buffer->Add((unsigned char)((tamanio >> 8) & 0xFF));
						buffer->Add((unsigned char)(tamanio & 0xFF));
					}
				}

				// Escribir datos de cada entrada
				for each (EntradaGDAT^ entrada in informacion->entradas) {
					if (entrada->datos != nullptr && entrada->tamanio > 0) {
						buffer->AddRange(entrada->datos);
					}
				}

				// Guardar a archivo
				array<unsigned char>^ datosFinales = buffer->ToArray();
				File::WriteAllBytes(rutaArchivo, datosFinales);

				return true;
			}
			catch (Exception^ ex) {
				System::Windows::Forms::MessageBox::Show(
					"Error al guardar archivo: " + ex->Message,
					"Error",
					System::Windows::Forms::MessageBoxButtons::OK,
					System::Windows::Forms::MessageBoxIcon::Error
				);
				return false;
			}
		}

		// Obtener información del archivo
		InformacionGDAT^ ObtenerInformacion() {
			return informacion;
		}

		// Verificar si hay un archivo abierto
		bool EstaAbierto() {
			return archivoAbierto;
		}

		// Cerrar archivo
		void Cerrar() {
			informacion = gcnew InformacionGDAT();
			archivoAbierto = false;
		}

		// Exportar entrada individual
		bool ExportarEntrada(int indice, String^ rutaDestino) {
			try {
				if (indice < 0 || indice >= informacion->entradas->Count) {
					return false;
				}

				EntradaGDAT^ entrada = informacion->entradas[indice];
				if (entrada->datos != nullptr && entrada->tamanio > 0) {
					File::WriteAllBytes(rutaDestino, entrada->datos);
					return true;
				}
				return false;
			}
			catch (Exception^) {
				return false;
			}
		}

		// Importar entrada individual
		bool ImportarEntrada(int indice, String^ rutaOrigen) {
			try {
				if (indice < 0 || indice >= informacion->entradas->Count) {
					return false;
				}

				if (!File::Exists(rutaOrigen)) {
					return false;
				}

				array<unsigned char>^ nuevosDatos = File::ReadAllBytes(rutaOrigen);
				EntradaGDAT^ entrada = informacion->entradas[indice];
				entrada->datos = nuevosDatos;
				entrada->tamanio = nuevosDatos->Length;

				return true;
			}
			catch (Exception^) {
				return false;
			}
		}
	};
}
