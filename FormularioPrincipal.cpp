#include "FormularioPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace EditorDungeon;

// Implementación de manejadores de eventos del menú

System::Void FormularioPrincipal::MenuAbrir_Click(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog^ dialogo = gcnew OpenFileDialog();
	dialogo->Filter = "Archivos GDAT (*.dat)|*.dat|Todos los archivos (*.*)|*.*";
	dialogo->Title = "Abrir archivo GDAT";

	if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (lector->AbrirArchivo(dialogo->FileName))
		{
			ActualizarInformacion();
			ActualizarListaEntradas();
			etiquetaEstado->Text = "Archivo cargado: " + dialogo->FileName;
		}
		// El error ya se muestra dentro de AbrirArchivo con el mensaje detallado
	}
}

System::Void FormularioPrincipal::MenuGuardar_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!lector->EstaAbierto())
	{
		MessageBox::Show("No hay ningún archivo abierto", "Advertencia", 
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	InformacionGDAT^ info = lector->ObtenerInformacion();
	if (String::IsNullOrEmpty(info->rutaArchivo))
	{
		MenuGuardarComo_Click(sender, e);
		return;
	}

	if (lector->GuardarArchivo(info->rutaArchivo))
	{
		etiquetaEstado->Text = "Archivo guardado correctamente";
		MessageBox::Show("Archivo guardado correctamente", "Éxito", 
			MessageBoxButtons::OK, MessageBoxIcon::Information);
	}
	else
	{
		MessageBox::Show("Error al guardar el archivo", "Error", 
			MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void FormularioPrincipal::MenuGuardarComo_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!lector->EstaAbierto())
	{
		MessageBox::Show("No hay ningún archivo abierto", "Advertencia", 
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	SaveFileDialog^ dialogo = gcnew SaveFileDialog();
	dialogo->Filter = "Archivos GDAT (*.dat)|*.dat|Todos los archivos (*.*)|*.*";
	dialogo->Title = "Guardar archivo GDAT";

	if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (lector->GuardarArchivo(dialogo->FileName))
		{
			etiquetaEstado->Text = "Archivo guardado como: " + dialogo->FileName;
			MessageBox::Show("Archivo guardado correctamente", "Éxito", 
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("Error al guardar el archivo", "Error", 
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void FormularioPrincipal::MenuSalir_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void FormularioPrincipal::MenuExportarEntrada_Click(System::Object^ sender, System::EventArgs^ e)
{
	BotonExportar_Click(sender, e);
}

System::Void FormularioPrincipal::MenuImportarEntrada_Click(System::Object^ sender, System::EventArgs^ e)
{
	BotonImportar_Click(sender, e);
}

System::Void FormularioPrincipal::MenuAcercaDe_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show(
		"Editor de Archivos GDAT - Dungeon Master\n\n" +
		"Versión 1.0\n\n" +
		"Editor para archivos .dat de Dungeon Master 1 y 2\n\n" +
		"Desarrollado con C++/CLI y Windows Forms",
		"Acerca de",
		MessageBoxButtons::OK,
		MessageBoxIcon::Information
	);
}

// Implementación de manejadores de eventos de controles

System::Void FormularioPrincipal::ListaEntradas_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	if (listaEntradas->SelectedItems->Count == 0)
	{
		textoTamanioEntrada->Text = "";
		vistaPrevia->Image = nullptr;
		return;
	}

	int indice = listaEntradas->SelectedItems[0]->Index;
	InformacionGDAT^ info = lector->ObtenerInformacion();
	
	if (indice >= 0 && indice < info->entradas->Count)
	{
		EntradaGDAT^ entrada = info->entradas[indice];
		textoTamanioEntrada->Text = entrada->tamanio.ToString() + " bytes";
	}
}

System::Void FormularioPrincipal::BotonExportar_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (listaEntradas->SelectedItems->Count == 0)
	{
		MessageBox::Show("Seleccione una entrada para exportar", "Advertencia", 
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	int indice = listaEntradas->SelectedItems[0]->Index;

	SaveFileDialog^ dialogo = gcnew SaveFileDialog();
	dialogo->Filter = "Archivos binarios (*.bin)|*.bin|Todos los archivos (*.*)|*.*";
	dialogo->Title = "Exportar entrada";
	dialogo->FileName = "entrada_" + indice.ToString() + ".bin";

	if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (lector->ExportarEntrada(indice, dialogo->FileName))
		{
			etiquetaEstado->Text = "Entrada exportada correctamente";
			MessageBox::Show("Entrada exportada correctamente", "Éxito", 
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("Error al exportar la entrada", "Error", 
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void FormularioPrincipal::BotonImportar_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (listaEntradas->SelectedItems->Count == 0)
	{
		MessageBox::Show("Seleccione una entrada para importar", "Advertencia", 
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	int indice = listaEntradas->SelectedItems[0]->Index;

	OpenFileDialog^ dialogo = gcnew OpenFileDialog();
	dialogo->Filter = "Archivos binarios (*.bin)|*.bin|Todos los archivos (*.*)|*.*";
	dialogo->Title = "Importar entrada";

	if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (lector->ImportarEntrada(indice, dialogo->FileName))
		{
			ActualizarListaEntradas();
			etiquetaEstado->Text = "Entrada importada correctamente";
			MessageBox::Show("Entrada importada correctamente", "Éxito", 
				MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		else
		{
			MessageBox::Show("Error al importar la entrada", "Error", 
				MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void FormularioPrincipal::BotonVistaPrevia_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (listaEntradas->SelectedItems->Count == 0)
	{
		MessageBox::Show("Seleccione una entrada para ver la vista previa", "Advertencia", 
			MessageBoxButtons::OK, MessageBoxIcon::Warning);
		return;
	}

	// TODO: Implementar decodificación de imágenes
	MessageBox::Show("Vista previa de imágenes en desarrollo", "Información", 
		MessageBoxButtons::OK, MessageBoxIcon::Information);
}

// Métodos auxiliares

void FormularioPrincipal::ActualizarListaEntradas()
{
	listaEntradas->Items->Clear();

	if (!lector->EstaAbierto())
	{
		return;
	}

	InformacionGDAT^ info = lector->ObtenerInformacion();

	for (int i = 0; i < info->entradas->Count; i++)
	{
		EntradaGDAT^ entrada = info->entradas[i];
		
		ListViewItem^ item = gcnew ListViewItem(i.ToString());
		item->SubItems->Add(entrada->tamanio.ToString() + " bytes");
		item->SubItems->Add(entrada->ObtenerNombreAmigable());

		listaEntradas->Items->Add(item);
	}
}

void FormularioPrincipal::ActualizarInformacion()
{
	if (!lector->EstaAbierto())
	{
		LimpiarFormulario();
		return;
	}

	InformacionGDAT^ info = lector->ObtenerInformacion();

	textoRutaArchivo->Text = info->rutaArchivo;
	textoNumeroEntradas->Text = info->numeroEntradas.ToString();
	textoEndianness->Text = info->littleEndian ? "Little Endian" : "Big Endian";
}

void FormularioPrincipal::LimpiarFormulario()
{
	textoRutaArchivo->Text = "";
	textoNumeroEntradas->Text = "";
	textoEndianness->Text = "";
	textoTamanioEntrada->Text = "";
	listaEntradas->Items->Clear();
	vistaPrevia->Image = nullptr;
}
