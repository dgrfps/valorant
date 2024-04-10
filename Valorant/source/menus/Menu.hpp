#pragma once

#ifndef MENU_HPP
#define MENU_HPP

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include <imgui.h>
#include "../render/Graphics.hpp"
#include "../settings/Settings.h"
#include "../utils/Keys.hpp"
#include "../utils/Keybind.hpp"

class Menu
{
	public:
		HotKey key_trigger;
		HotKey key_fire;

		Menu() {
			key_trigger = HotKey{};
			key_fire = HotKey{};
		};

		void Draw()
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
							ImGui::SliderInt("##Delay", &Settings::triggerDelay, 0, 1000, "%d");
						}
						ImGui::EndChild();

						ImGui::NextColumn();
						ImGui::BeginChild("right", { 0, 145}, false, ImGuiWindowFlags_NoResize);
						{
							ImGui::Text("Saturation"); ImGui::SameLine(); ImGui::SetNextItemWidth(175);
							ImGui::SliderInt2("##Saturation", Settings::triggerTension, 1, 100, "%d");

							ImGui::Text("Outline color");
							const char* items[] = { "NONE", "PURPLE", "RED", "YELLOW" };
							static const char* current_item = "-1";

							if (current_item == "-1") {
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
							ImGui::EndChild();	
						}
						ImGui::EndTabItem();
					}
					ImGui::Columns(1);
										
					if (ImGui::BeginTabItem("CONFIG"))
					{
						if (ImGui::BeginTable("sstable", 2))
						{
							ImGui::TableNextRow(); //NEXT LINE
							ImGui::TableSetColumnIndex(0);

							ImGui::Text("Keybind"); ImGui::SameLine();
							key_trigger.Bind(&Settings::triggerBind, { 125, 25 });

							ImGui::TableSetColumnIndex(1);
							if (ImGui::Button("Save", { 125, 25 }))
							{
								Settings::Save();
							}

							ImGui::TableNextRow(); //NEXT LINE
							ImGui::TableSetColumnIndex(0);
							ImGui::Text("Fire alias"); ImGui::SameLine();
							key_fire.Bind(&Settings::triggerFireKey, { 125, 25 });

							ImGui::TableSetColumnIndex(1);
							if (ImGui::Button("Load", { 125, 25 }))
							{
								Settings::Load();
							}
							ImGui::EndTable();
						}

						ImGui::EndTabItem();
					}

					ImGui::EndTabBar();
				}
			ImGui::End();
		}
};
#endif