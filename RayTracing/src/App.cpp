#include <stdint.h>

#include "Application.h"
#include "Image.h"


class ExampleLayer : public jjf::Layer
{
public:
	virtual void OnAttach() override
	{
		ImGuiIO& io = ImGui::GetIO();
		io.FontGlobalScale = 1.4;
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
		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		if (m_Image)
		{
			ImGui::Image(m_Image->GetDescriptorSet(), { (float)m_ViewportWidth, (float)m_ViewportHeight });
		}

		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		if (!m_Image || m_ViewportWidth != m_Image->GetWidth() || m_ViewportHeight != m_Image->GetHeight())
		{
			m_Image = std::make_shared<jjf::Image>(m_ViewportWidth, m_ViewportHeight, jjf::ImageFormat::RGBA);
			delete[] m_ImageData;
			m_ImageData = new uint32_t[m_ViewportWidth * m_ViewportHeight];

			for (uint32_t i = 0; i < m_ViewportWidth * m_ViewportHeight; i++)
			{
				m_ImageData[i] = 0xff99dd00;
			}

			m_Image->SetData(m_ImageData);
		}
	}

private:
	uint32_t m_ViewportWidth = 0;
	uint32_t m_ViewportHeight = 0;

	std::shared_ptr<jjf::Image> m_Image;
	uint32_t* m_ImageData = nullptr;

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