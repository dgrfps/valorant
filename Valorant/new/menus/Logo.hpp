#pragma once

#include <imgui.h>
#include "../render/Graphics.hpp"
#include "../settings/Settings.h"

class Logo
{
	public:
		static void Draw()
		{
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::SetNextWindowPos({ 0, 0 });
			ImGui::SetNextWindowSize(io.DisplaySize);
			ImGui::Begin("##LOGO", 0, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoCollapse 
				| ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize 
				| ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNav);
           
				if(ImGui::BeginTabBar("TAB", ImGuiTabBarFlags_None))
				{
					if(ImGui::BeginTabItem("TRIGGER"))
					{
						ImGui::Text("Scan area");
						
						ImGui::Text("Width"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
						ImGui::SliderFloat("##Width", &Settings::triggerWidth, 0.0, 20.0, "%.f");

						ImGui::Text("Height"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
						ImGui::SliderFloat("##Height", &Settings::triggerHeight, 0.0, 20.0, "%.f");

						ImGui::Text("Delay"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
						ImGui::SliderFloat("##Delay", &Settings::triggerDelay, 0.0, 20.0, "%.f");

						ImGui::Separator();

						ImGui::Text("Outline color");
						const char* items[] = { "PURPLE", "RED", "YELLOW" };
						static const char* current_item = items[0];

						ImGui::SetNextItemWidth(175);
						if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(items); n++)
							{
								bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(items[n], is_selected))
								{
									current_item = items[n];
										if (is_selected)
											ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
								}
							}

							ImGui::EndCombo();
						}

						ImGui::EndTabItem();
					}
					

					if (ImGui::BeginTabItem("RECOIL CONTROL"))
					{
						ImGui::Text("RCS");

						ImGui::Checkbox("Enabled", &Settings::rcsEnabled);
						{
							ImGui::Text("Move amount"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
							ImGui::SliderInt("##rcs", &Settings::rcsAmount, 0, 10, "%d");

							ImGui::Text("RCS tick interval (ms)"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
							ImGui::SliderFloat("##rcsRate", &Settings::rcsRate, 0, 30, "%.2f", .1f);
						}

						ImGui::EndTabItem();
					}
					
					if (ImGui::BeginTabItem("CONFIG"))
					{
						
						if (ImGui::Button("Save", { 125, 25 }))
						{
							Settings::Save();
						}

						if (ImGui::Button("Load", { 125, 25 }))
						{
							Settings::Load();
						}


						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			ImGui::End();
		}
};