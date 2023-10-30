#include <stdint.h>

#include "Application.h"
#include "Image.h"

#include "Renderer.h"


class ExampleLayer : public jjf::Layer
{
public:
	virtual void OnAttach() override
	{
		ImGuiIO& io = ImGui::GetIO();
		io.FontGlobalScale = 1.4f;
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.0f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.0f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.1f, 0.1f, 0.1f, 0.6f);
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last render: %.3fms", m_LastFrameTime);
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();
		
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		
		ImGui::Begin("Viewport");
		m_ViewportWidth = static_cast<uint32_t>(ImGui::GetContentRegionAvail().x);
		m_ViewportHeight = static_cast<uint32_t>(ImGui::GetContentRegionAvail().y);

		auto image = m_Renderer.GetFinalImage();
		if(image)
			ImGui::Image((void*)image->GetDescriptorSet(), ImVec2((float)m_ViewportWidth, (float)m_ViewportHeight), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render();
	}

private:
	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	Renderer m_Renderer;

	float m_LastFrameTime = 0.0f;

};

jjf::Application* jjf::CreateApplication(int argc, char** argv)
{
	jjf::ApplicationSpecification spec;
	spec.Name = "Ray Tracing";
	spec.Width = 1920;
	spec.Height = 1080;

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