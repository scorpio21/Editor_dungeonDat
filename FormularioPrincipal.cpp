#include "FormularioPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace EditorDungeon;

// Implementación de manejadores de eventos del menú

System::Void FormularioPrincipal::MenuAbrir_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  OpenFileDialog ^ dialogo = gcnew OpenFileDialog();
  dialogo->Filter = "Archivos GDAT (*.dat)|*.dat|Todos los archivos (*.*)|*.*";
  dialogo->Title = "Abrir archivo GDAT";

  if (dialogo->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
    if (lector->AbrirArchivo(dialogo->FileName)) {
      ActualizarInformacion();
      ActualizarListaEntradas();

      InformacionGDAT ^ info = lector->ObtenerInformacion();
      String ^ mensaje =
          String::Format("Archivo cargado: {0}\nEntradas: {1}\nEndianness: {2}",
                         dialogo->FileName, info->numeroEntradas,
                         info->littleEndian ? "Little Endian" : "Big Endian");

      etiquetaEstado->Text = "Archivo cargado: " + dialogo->FileName;
      MessageBox::Show(mensaje, "Información del archivo",
                       MessageBoxButtons::OK, MessageBoxIcon::Information);
    }
  }
}

System::Void FormularioPrincipal::MenuGuardar_Click(System::Object ^ sender,
                                                    System::EventArgs ^ e) {
  MessageBox::Show("Guardar no implementado aún", "Información",
                   MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void FormularioPrincipal::MenuGuardarComo_Click(System::Object ^ sender,
                                                        System::EventArgs ^ e) {
  MessageBox::Show("Guardar como no implementado aún", "Información",
                   MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void FormularioPrincipal::MenuSalir_Click(System::Object ^ sender,
                                                  System::EventArgs ^ e) {
  Application::Exit();
}

System::Void
FormularioPrincipal::MenuExportarEntrada_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  BotonExportar_Click(sender, e);
}

System::Void
FormularioPrincipal::MenuImportarEntrada_Click(System::Object ^ sender,
                                               System::EventArgs ^ e) {
  BotonImportar_Click(sender, e);
}

System::Void FormularioPrincipal::MenuAcercaDe_Click(System::Object ^ sender,
                                                     System::EventArgs ^ e) {
  MessageBox::Show(
      "Editor de Archivos GDAT - Dungeon Master\n\n" + "Versión 2.0\n\n" +
          "Editor para archivos .dat de Dungeon Master 1 y 2\n\n" +
          "Desarrollado con C++/CLI y Windows Forms",
      "Acerca de", MessageBoxButtons::OK, MessageBoxIcon::Information);
}

// Implementación de manejadores de eventos de controles

System::Void FormularioPrincipal::ArbolCategorias_AfterSelect(
    System::Object ^ sender, System::Windows::Forms::TreeViewEventArgs ^ e) {
  gridDetalles->Rows->Clear();

  if (e->Node == nullptr || e->Node->Tag == nullptr) {
    return;
  }

  // El Tag contiene un array con [categoría, clase1]
  array<unsigned char> ^ tag = (array<unsigned char> ^) e->Node->Tag;
  unsigned char categoria = tag[0];
  unsigned char clase1 = tag[1];

  InformacionGDAT ^ info = lector->ObtenerInformacion();

  // Mostrar todas las entradas de esta categoría/clase1
  for (int i = 0; i < info->entradas->Count; i++) {
    EntradaGDAT ^ entrada = info->entradas[i];

    bool mostrar = false;
    if (clase1 == 255) {
      // Nodo de categoría: mostrar todas las entradas de esta categoría
      mostrar = (entrada->categoria == categoria);
    } else {
      // Nodo de clase: mostrar solo las entradas de esta categoría y clase1
      mostrar = (entrada->categoria == categoria && entrada->clase1 == clase1);
    }

    if (mostrar) {
      String ^ name = String::Format("{0:X2} {1:X2} {2:X2}", entrada->clase1,
                                     entrada->clase2, entrada->tipo);
      String ^ type = entrada->ObtenerNombreTipo();
      String ^ description = "";
      String ^ value = String::Format("{0} bytes", entrada->tamanio);

      gridDetalles->Rows->Add(name, type, description, value);
    }
  }
}

System::Void FormularioPrincipal::BotonExportar_Click(System::Object ^ sender,
                                                      System::EventArgs ^ e) {
  MessageBox::Show("Exportar no implementado aún", "Información",
                   MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void FormularioPrincipal::BotonImportar_Click(System::Object ^ sender,
                                                      System::EventArgs ^ e) {
  MessageBox::Show("Importar no implementado aún", "Información",
                   MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void
FormularioPrincipal::BotonVistaPrevia_Click(System::Object ^ sender,
                                            System::EventArgs ^ e) {
  MessageBox::Show("Vista previa de imágenes en desarrollo", "Información",
                   MessageBoxButtons::OK, MessageBoxIcon::Information);
}

System::Void FormularioPrincipal::ContenedorPrincipal_SplitterMoved(
    System::Object ^ sender, System::Windows::Forms::SplitterEventArgs ^ e) {
  // Mostrar el tamaño actual del panel izquierdo en la barra de estado
  etiquetaEstado->Text = String::Format("Tamaño panel: {0} px",
                                        contenedorPrincipal->SplitterDistance);
}

// Métodos auxiliares

void FormularioPrincipal::ActualizarListaEntradas() {
  arbolCategorias->Nodes->Clear();
  gridDetalles->Rows->Clear();

  if (!lector->EstaAbierto()) {
    return;
  }

  InformacionGDAT ^ info = lector->ObtenerInformacion();

  // Agrupar entradas por categoría y clase1
  Dictionary<unsigned char,
             Dictionary<unsigned char, List<EntradaGDAT ^> ^> ^> ^
      jerarquia =
      gcnew Dictionary<unsigned char,
                       Dictionary<unsigned char, List<EntradaGDAT ^> ^> ^>();

  for (int i = 0; i < info->entradas->Count; i++) {
    EntradaGDAT ^ entrada = info->entradas[i];

    if (!jerarquia->ContainsKey(entrada->categoria)) {
      jerarquia[entrada->categoria] =
          gcnew Dictionary<unsigned char, List<EntradaGDAT ^> ^>();
    }

    if (!jerarquia[entrada->categoria]->ContainsKey(entrada->clase1)) {
      jerarquia[entrada->categoria][entrada->clase1] =
          gcnew List<EntradaGDAT ^>();
    }

    jerarquia[entrada->categoria][entrada->clase1]->Add(entrada);
  }

  // Crear nodos del árbol
  for each (KeyValuePair<unsigned char,
                        Dictionary<unsigned char, List<EntradaGDAT ^> ^> ^> ^
           parCat in jerarquia) {
    unsigned char cat = parCat->Key;

    // Crear entrada temporal para obtener el nombre de la categoría
    EntradaGDAT ^ tempCat = gcnew EntradaGDAT();
    tempCat->categoria = cat;

    TreeNode ^ nodoCat = gcnew TreeNode(
        String::Format("{0:X2} {1}", cat, tempCat->ObtenerNombreCategoria()));
    nodoCat->Tag =
        gcnew array<unsigned char>{cat, 255}; // 255 = todas las clases

    // Agregar subnodos por clase1
    for each (KeyValuePair<unsigned char, List<EntradaGDAT ^> ^> ^
             parClase in parCat->Value) {
      unsigned char clase1 = parClase->Key;

      TreeNode ^ nodoClase = gcnew TreeNode(String::Format("{0:X2}", clase1));
      nodoClase->Tag = gcnew array<unsigned char>{cat, clase1};

      nodoCat->Nodes->Add(nodoClase);
    }

    arbolCategorias->Nodes->Add(nodoCat);
  }
}

void FormularioPrincipal::ActualizarInformacion() {
  if (!lector->EstaAbierto()) {
    LimpiarFormulario();
    return;
  }

  InformacionGDAT ^ info = lector->ObtenerInformacion();

  textoRutaArchivo->Text = info->rutaArchivo;
  textoNumeroEntradas->Text = info->numeroEntradas.ToString();
  textoEndianness->Text = info->littleEndian ? "Little Endian" : "Big Endian";
}

void FormularioPrincipal::LimpiarFormulario() {
  textoRutaArchivo->Text = "";
  textoNumeroEntradas->Text = "";
  textoEndianness->Text = "";
  textoTamanioEntrada->Text = "";
  arbolCategorias->Nodes->Clear();
  gridDetalles->Rows->Clear();
  vistaPrevia->Image = nullptr;
}
