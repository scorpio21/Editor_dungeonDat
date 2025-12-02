#include "FormularioPrincipal.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	// Habilitar estilos visuales de Windows
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Crear y ejecutar el formulario principal
	EditorDungeon::FormularioPrincipal^ formulario = gcnew EditorDungeon::FormularioPrincipal();
	Application::Run(formulario);

	return 0;
}
