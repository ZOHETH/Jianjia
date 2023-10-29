#include "Application.h"


class ExampleLayer : public jjf::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

jjf::Application* jjf::CreateApplication(int argc, char** argv)
{
	jjf::ApplicationSpecification spec;
	spec.Name = "jjf Example";

	jjf::Application* app = new jjf::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}