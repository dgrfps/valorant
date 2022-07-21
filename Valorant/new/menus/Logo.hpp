#pragma once
#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include <imgui.h>
#include "../render/Graphics.hpp"
#include "../settings/Settings.h"
#include "../utils/Keys.hpp"

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
						ImGui::Columns(2);
						ImGui::BeginChild("left", {0, 145}, false, ImGuiWindowFlags_NoResize);
						{
							ImGui::Text("Scan area");

							ImGui::Text("Width"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
							ImGui::SliderInt("##Width", &Settings::triggerWidth, 0, 20, "%d");

							ImGui::Text("Height"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
							ImGui::SliderInt("##Height", &Settings::triggerHeight, 0, 20, "%d");

							ImGui::Text("Delay"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
							ImGui::SliderInt("##Delay", &Settings::triggerDelay, 0, 20, "%d");
						}
						ImGui::EndChild();

						ImGui::NextColumn();
						ImGui::BeginChild("right", { 0, 145}, false, ImGuiWindowFlags_NoResize);
						{
							ImGui::Text("Keybind"); ImGui::SameLine();
							ImGui::Hotkey(1, &Settings::triggerBind, { 125, 25 });

							ImGui::Text("Fire alias"); ImGui::SameLine();
							ImGui::Hotkey(2, &Settings::triggerFireKey, { 125, 25 });
						}

						ImGui::EndChild();

						ImGui::Columns(1);

						ImGui::Separator(); 
						
						ImGui::Text("Saturation"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
						ImGui::SliderInt2("##Saturation", Settings::triggerTension, 1, 100, "%d");

						ImGui::Text("Outline color");
						const char* items[] = { "NONE", "PURPLE", "RED", "YELLOW" };
						static const char* current_item = "-1";
						
						if(current_item == "-1") {
							for (int n = 0; n < IM_ARRAYSIZE(items); n++)
							{
								if (items[n] == Color::toString(Settings::triggerColor))
									current_item = items[n];
							}
						}

						ImGui::SetNextItemWidth(175);
						if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
						{
							for (int n = 0; n < IM_ARRAYSIZE(items); n++)
							{
								bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
								if (ImGui::Selectable(items[n], is_selected))
								{
									current_item = items[n];
									if (current_item == "PURPLE" || current_item == "NONE")
										Settings::triggerColor = Color::ColorName::Magenta;
									if (current_item == "RED")
										Settings::triggerColor = Color::ColorName::Vermelho;
									if (current_item == "YELLOW")
										Settings::triggerColor = Color::ColorName::Amarelo;

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
						ImGui::Text("RCS (Require Arduino)");

						ImGui::Checkbox("Enabled", &Settings::rcsEnabled);
						
						ImGui::Columns(2);
						ImGui::BeginChild("rcsleft", { 0, 130 }, false, ImGuiWindowFlags_NoResize);
						{
							ImGui::Text("Move amount"); ImGui::SameLine(); ImGui::SetNextItemWidth(105);
							ImGui::SliderInt("##rcs", &Settings::rcsAmount, 0, 10, "%d");

							ImGui::Text("RCS tick interval (ms)"); ImGui::SameLine(); ImGui::SetNextItemWidth(105);
							ImGui::SliderFloat("##rcsRate", &Settings::rcsRate, 0, 30, "%.2f", .1f);
						}
						ImGui::EndChild();
						ImGui::NextColumn();
						ImGui::BeginChild("rrcsight", { 0, 145 }, false, ImGuiWindowFlags_NoResize);
						{
							ImGui::Text("Toggle Keybind"); ImGui::SameLine();
							ImGui::Hotkey(3, &Settings::rcsBind, { 125, 25 });

							ImGui::Text("Arduino COM Port"); ImGui::SameLine(); ImGui::SetNextItemWidth(105);
							ImGui::InputInt("##COMPort", &Settings::COMPORT, 1, 5);
						}
						ImGui::EndChild();
						ImGui::Columns(1);

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