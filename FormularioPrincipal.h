#pragma once

#include "GDATReader.h"

namespace EditorDungeon {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Formulario principal del Editor de Dungeon Master
/// </summary>
public
ref class FormularioPrincipal : public System::Windows::Forms::Form {
public:
  FormularioPrincipal(void) {
    InitializeComponent();
    lector = gcnew LectorGDAT();
  }

protected:
  /// <summary>
  /// Limpiar recursos
  /// </summary>
  ~FormularioPrincipal() {
    if (components) {
      delete components;
    }
  }

private:
  LectorGDAT ^ lector;
  System::ComponentModel::Container ^ components;

  // Controles del formulario
  System::Windows::Forms::MenuStrip ^ menuPrincipal;
  System::Windows::Forms::ToolStripMenuItem ^ menuArchivo;
  System::Windows::Forms::ToolStripMenuItem ^ menuAbrir;
  System::Windows::Forms::ToolStripMenuItem ^ menuGuardar;
  System::Windows::Forms::ToolStripMenuItem ^ menuGuardarComo;
  System::Windows::Forms::ToolStripMenuItem ^ menuSalir;
  System::Windows::Forms::ToolStripMenuItem ^ menuEdicion;
  System::Windows::Forms::ToolStripMenuItem ^ menuExportarEntrada;
  System::Windows::Forms::ToolStripMenuItem ^ menuImportarEntrada;
  System::Windows::Forms::ToolStripMenuItem ^ menuAyuda;
  System::Windows::Forms::ToolStripMenuItem ^ menuAcercaDe;

  System::Windows::Forms::StatusStrip ^ barraEstado;
  System::Windows::Forms::ToolStripStatusLabel ^ etiquetaEstado;

  System::Windows::Forms::SplitContainer ^ contenedorPrincipal;
  System::Windows::Forms::DataGridView ^ gridEntradas;

  System::Windows::Forms::Panel ^ panelDetalles;
  System::Windows::Forms::GroupBox ^ grupoInformacion;
  System::Windows::Forms::Label ^ etiquetaNumeroEntradas;
  System::Windows::Forms::Label ^ etiquetaEndianness;
  System::Windows::Forms::Label ^ etiquetaRutaArchivo;
  System::Windows::Forms::TextBox ^ textoNumeroEntradas;
  System::Windows::Forms::TextBox ^ textoEndianness;
  System::Windows::Forms::TextBox ^ textoRutaArchivo;

  System::Windows::Forms::GroupBox ^ grupoEntradaSeleccionada;
  System::Windows::Forms::Label ^ etiquetaTamanioEntrada;
  System::Windows::Forms::TextBox ^ textoTamanioEntrada;
  System::Windows::Forms::Button ^ botonExportar;
  System::Windows::Forms::Button ^ botonImportar;
  System::Windows::Forms::Button ^ botonVistaPrevia;

  System::Windows::Forms::PictureBox ^ vistaPrevia;

#pragma region Windows Form Designer generated code
  /// <summary>
  /// Método requerido para el diseñador
  /// </summary>
  void InitializeComponent(void) {
    this->components = gcnew System::ComponentModel::Container();
    this->Size = System::Drawing::Size(1024, 768);
    this->Text = L"Editor de Archivos GDAT - Dungeon Master";
    this->Padding = System::Windows::Forms::Padding(0);
    this->StartPosition = FormStartPosition::CenterScreen;

    // Menú Principal
    this->menuPrincipal = gcnew System::Windows::Forms::MenuStrip();
    this->menuArchivo = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuAbrir = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuGuardar = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuGuardarComo = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuSalir = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuEdicion = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuExportarEntrada =
        gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuImportarEntrada =
        gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuAyuda = gcnew System::Windows::Forms::ToolStripMenuItem();
    this->menuAcercaDe = gcnew System::Windows::Forms::ToolStripMenuItem();

    // Configurar menú Archivo
    this->menuArchivo->Text = L"&Archivo";
    this->menuAbrir->Text = L"&Abrir...";
    this->menuAbrir->ShortcutKeys =
        (System::Windows::Forms::Keys)(System::Windows::Forms::Keys::Control |
                                       System::Windows::Forms::Keys::O);
    this->menuAbrir->Click +=
        gcnew System::EventHandler(this, &FormularioPrincipal::MenuAbrir_Click);

    this->menuGuardar->Text = L"&Guardar";
    this->menuGuardar->ShortcutKeys =
        (System::Windows::Forms::Keys)(System::Windows::Forms::Keys::Control |
                                       System::Windows::Forms::Keys::S);
    this->menuGuardar->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::MenuGuardar_Click);

    this->menuGuardarComo->Text = L"Guardar &como...";
    this->menuGuardarComo->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::MenuGuardarComo_Click);

    this->menuSalir->Text = L"&Salir";
    this->menuSalir->Click +=
        gcnew System::EventHandler(this, &FormularioPrincipal::MenuSalir_Click);

    this->menuArchivo->DropDownItems->Add(this->menuAbrir);
    this->menuArchivo->DropDownItems->Add(this->menuGuardar);
    this->menuArchivo->DropDownItems->Add(this->menuGuardarComo);
    this->menuArchivo->DropDownItems->Add(
        gcnew System::Windows::Forms::ToolStripSeparator());
    this->menuArchivo->DropDownItems->Add(this->menuSalir);

    // Configurar menú Edición
    this->menuEdicion->Text = L"&Edición";
    this->menuExportarEntrada->Text = L"&Exportar entrada...";
    this->menuExportarEntrada->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::MenuExportarEntrada_Click);

    this->menuImportarEntrada->Text = L"&Importar entrada...";
    this->menuImportarEntrada->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::MenuImportarEntrada_Click);

    this->menuEdicion->DropDownItems->Add(this->menuExportarEntrada);
    this->menuEdicion->DropDownItems->Add(this->menuImportarEntrada);

    // Configurar menú Ayuda
    this->menuAyuda->Text = L"&Ayuda";
    this->menuAcercaDe->Text = L"&Acerca de...";
    this->menuAcercaDe->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::MenuAcercaDe_Click);
    this->menuAyuda->DropDownItems->Add(this->menuAcercaDe);

    this->menuPrincipal->Items->Add(this->menuArchivo);
    this->menuPrincipal->Items->Add(this->menuEdicion);
    this->menuPrincipal->Items->Add(this->menuAyuda);

    // Barra de estado
    this->barraEstado = gcnew System::Windows::Forms::StatusStrip();
    this->etiquetaEstado = gcnew System::Windows::Forms::ToolStripStatusLabel();
    this->etiquetaEstado->Text = L"Listo";
    this->barraEstado->Items->Add(this->etiquetaEstado);

    // Contenedor principal
    this->contenedorPrincipal = gcnew System::Windows::Forms::SplitContainer();
    this->contenedorPrincipal->Dock = DockStyle::Fill;
    this->contenedorPrincipal->SplitterDistance = 400;
    this->contenedorPrincipal->Orientation = Orientation::Vertical;

    // DataGridView de entradas
    this->gridEntradas = gcnew System::Windows::Forms::DataGridView();
    this->gridEntradas->Dock = DockStyle::Fill;
    this->gridEntradas->AllowUserToAddRows = false;
    this->gridEntradas->AllowUserToDeleteRows = false;
    this->gridEntradas->ReadOnly = true;
    this->gridEntradas->SelectionMode =
        DataGridViewSelectionMode::FullRowSelect;
    this->gridEntradas->MultiSelect = false;
    this->gridEntradas->RowHeadersVisible = false;
    this->gridEntradas->AutoSizeColumnsMode =
        DataGridViewAutoSizeColumnsMode::Fill;
    this->gridEntradas->SelectionChanged += gcnew System::EventHandler(
        this, &FormularioPrincipal::GridEntradas_SelectionChanged);

    // Configurar columnas
    DataGridViewTextBoxColumn ^ colIndice = gcnew DataGridViewTextBoxColumn();
    colIndice->Name = "Indice";
    colIndice->HeaderText = "Índice";
    colIndice->Width = 60;
    colIndice->FillWeight = 10;
    this->gridEntradas->Columns->Add(colIndice);

    DataGridViewTextBoxColumn ^ colCategoria =
        gcnew DataGridViewTextBoxColumn();
    colCategoria->Name = "Categoria";
    colCategoria->HeaderText = "Cat";
    colCategoria->Width = 50;
    colCategoria->FillWeight = 8;
    this->gridEntradas->Columns->Add(colCategoria);

    DataGridViewTextBoxColumn ^ colClase1 = gcnew DataGridViewTextBoxColumn();
    colClase1->Name = "Clase1";
    colClase1->HeaderText = "C1";
    colClase1->Width = 50;
    colClase1->FillWeight = 8;
    this->gridEntradas->Columns->Add(colClase1);

    DataGridViewTextBoxColumn ^ colClase2 = gcnew DataGridViewTextBoxColumn();
    colClase2->Name = "Clase2";
    colClase2->HeaderText = "C2";
    colClase2->Width = 50;
    colClase2->FillWeight = 8;
    this->gridEntradas->Columns->Add(colClase2);

    DataGridViewTextBoxColumn ^ colTipo = gcnew DataGridViewTextBoxColumn();
    colTipo->Name = "Tipo";
    colTipo->HeaderText = "Tipo";
    colTipo->Width = 50;
    colTipo->FillWeight = 8;
    this->gridEntradas->Columns->Add(colTipo);

    DataGridViewTextBoxColumn ^ colTamanio = gcnew DataGridViewTextBoxColumn();
    colTamanio->Name = "Tamanio";
    colTamanio->HeaderText = "Tamaño";
    colTamanio->Width = 80;
    colTamanio->FillWeight = 12;
    this->gridEntradas->Columns->Add(colTamanio);

    DataGridViewTextBoxColumn ^ colDescripcion =
        gcnew DataGridViewTextBoxColumn();
    colDescripcion->Name = "Descripcion";
    colDescripcion->HeaderText = "Descripción";
    colDescripcion->Width = 200;
    colDescripcion->FillWeight = 46;
    this->gridEntradas->Columns->Add(colDescripcion);

    // Panel de detalles
    this->panelDetalles = gcnew System::Windows::Forms::Panel();
    this->panelDetalles->Dock = DockStyle::Fill;
    this->panelDetalles->AutoScroll = true;

    // Grupo de información general
    this->grupoInformacion = gcnew System::Windows::Forms::GroupBox();
    this->grupoInformacion->Text = L"Información del Archivo";
    this->grupoInformacion->Location = System::Drawing::Point(10, 10);
    this->grupoInformacion->Size = System::Drawing::Size(560, 120);

    this->etiquetaRutaArchivo = gcnew System::Windows::Forms::Label();
    this->etiquetaRutaArchivo->Text = L"Ruta:";
    this->etiquetaRutaArchivo->Location = System::Drawing::Point(10, 25);
    this->etiquetaRutaArchivo->AutoSize = true;

    this->textoRutaArchivo = gcnew System::Windows::Forms::TextBox();
    this->textoRutaArchivo->Location = System::Drawing::Point(120, 22);
    this->textoRutaArchivo->Size = System::Drawing::Size(420, 20);
    this->textoRutaArchivo->ReadOnly = true;

    this->etiquetaNumeroEntradas = gcnew System::Windows::Forms::Label();
    this->etiquetaNumeroEntradas->Text = L"Número de entradas:";
    this->etiquetaNumeroEntradas->Location = System::Drawing::Point(10, 55);
    this->etiquetaNumeroEntradas->AutoSize = true;

    this->textoNumeroEntradas = gcnew System::Windows::Forms::TextBox();
    this->textoNumeroEntradas->Location = System::Drawing::Point(120, 52);
    this->textoNumeroEntradas->Size = System::Drawing::Size(100, 20);
    this->textoNumeroEntradas->ReadOnly = true;

    this->etiquetaEndianness = gcnew System::Windows::Forms::Label();
    this->etiquetaEndianness->Text = L"Endianness:";
    this->etiquetaEndianness->Location = System::Drawing::Point(10, 85);
    this->etiquetaEndianness->AutoSize = true;

    this->textoEndianness = gcnew System::Windows::Forms::TextBox();
    this->textoEndianness->Location = System::Drawing::Point(120, 82);
    this->textoEndianness->Size = System::Drawing::Size(100, 20);
    this->textoEndianness->ReadOnly = true;

    this->grupoInformacion->Controls->Add(this->etiquetaRutaArchivo);
    this->grupoInformacion->Controls->Add(this->textoRutaArchivo);
    this->grupoInformacion->Controls->Add(this->etiquetaNumeroEntradas);
    this->grupoInformacion->Controls->Add(this->textoNumeroEntradas);
    this->grupoInformacion->Controls->Add(this->etiquetaEndianness);
    this->grupoInformacion->Controls->Add(this->textoEndianness);

    // Grupo de entrada seleccionada
    this->grupoEntradaSeleccionada = gcnew System::Windows::Forms::GroupBox();
    this->grupoEntradaSeleccionada->Text = L"Entrada Seleccionada";
    this->grupoEntradaSeleccionada->Location = System::Drawing::Point(10, 140);
    this->grupoEntradaSeleccionada->Size = System::Drawing::Size(560, 120);

    this->etiquetaTamanioEntrada = gcnew System::Windows::Forms::Label();
    this->etiquetaTamanioEntrada->Text = L"Tamaño:";
    this->etiquetaTamanioEntrada->Location = System::Drawing::Point(10, 25);
    this->etiquetaTamanioEntrada->AutoSize = true;

    this->textoTamanioEntrada = gcnew System::Windows::Forms::TextBox();
    this->textoTamanioEntrada->Location = System::Drawing::Point(120, 22);
    this->textoTamanioEntrada->Size = System::Drawing::Size(100, 20);
    this->textoTamanioEntrada->ReadOnly = true;

    this->botonExportar = gcnew System::Windows::Forms::Button();
    this->botonExportar->Text = L"Exportar";
    this->botonExportar->Location = System::Drawing::Point(10, 60);
    this->botonExportar->Size = System::Drawing::Size(100, 30);
    this->botonExportar->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::BotonExportar_Click);

    this->botonImportar = gcnew System::Windows::Forms::Button();
    this->botonImportar->Text = L"Importar";
    this->botonImportar->Location = System::Drawing::Point(120, 60);
    this->botonImportar->Size = System::Drawing::Size(100, 30);
    this->botonImportar->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::BotonImportar_Click);

    this->botonVistaPrevia = gcnew System::Windows::Forms::Button();
    this->botonVistaPrevia->Text = L"Vista Previa";
    this->botonVistaPrevia->Location = System::Drawing::Point(230, 60);
    this->botonVistaPrevia->Size = System::Drawing::Size(100, 30);
    this->botonVistaPrevia->Click += gcnew System::EventHandler(
        this, &FormularioPrincipal::BotonVistaPrevia_Click);

    this->grupoEntradaSeleccionada->Controls->Add(this->etiquetaTamanioEntrada);
    this->grupoEntradaSeleccionada->Controls->Add(this->textoTamanioEntrada);
    this->grupoEntradaSeleccionada->Controls->Add(this->botonExportar);
    this->grupoEntradaSeleccionada->Controls->Add(this->botonImportar);
    this->grupoEntradaSeleccionada->Controls->Add(this->botonVistaPrevia);

    // Vista previa
    this->vistaPrevia = gcnew System::Windows::Forms::PictureBox();
    this->vistaPrevia->Location = System::Drawing::Point(10, 270);
    this->vistaPrevia->Size = System::Drawing::Size(560, 400);
    this->vistaPrevia->BorderStyle = BorderStyle::FixedSingle;
    this->vistaPrevia->SizeMode = PictureBoxSizeMode::Zoom;

    this->panelDetalles->Controls->Add(this->grupoInformacion);
    this->panelDetalles->Controls->Add(this->grupoEntradaSeleccionada);
    this->panelDetalles->Controls->Add(this->vistaPrevia);

    // Agregar controles al contenedor
    this->contenedorPrincipal->Panel1->Controls->Add(this->gridEntradas);
    this->contenedorPrincipal->Panel2->Controls->Add(this->panelDetalles);

    // Agregar controles al formulario
    this->Controls->Add(this->contenedorPrincipal);
    this->Controls->Add(this->barraEstado);
    this->Controls->Add(this->menuPrincipal);
    this->MainMenuStrip = this->menuPrincipal;
  }
#pragma endregion

private:
  // Manejadores de eventos del menú
  System::Void MenuAbrir_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void MenuGuardar_Click(System::Object ^ sender,
                                 System::EventArgs ^ e);
  System::Void MenuGuardarComo_Click(System::Object ^ sender,
                                     System::EventArgs ^ e);
  System::Void MenuSalir_Click(System::Object ^ sender, System::EventArgs ^ e);
  System::Void MenuExportarEntrada_Click(System::Object ^ sender,
                                         System::EventArgs ^ e);
  System::Void MenuImportarEntrada_Click(System::Object ^ sender,
                                         System::EventArgs ^ e);
  System::Void MenuAcercaDe_Click(System::Object ^ sender,
                                  System::EventArgs ^ e);

  // Manejadores de eventos de controles
  System::Void GridEntradas_SelectionChanged(System::Object ^ sender,
                                             System::EventArgs ^ e);
  System::Void BotonExportar_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void BotonImportar_Click(System::Object ^ sender,
                                   System::EventArgs ^ e);
  System::Void BotonVistaPrevia_Click(System::Object ^ sender,
                                      System::EventArgs ^ e);

  // Métodos auxiliares
  void ActualizarListaEntradas();
  void ActualizarInformacion();
  void LimpiarFormulario();
};
} // namespace EditorDungeon
