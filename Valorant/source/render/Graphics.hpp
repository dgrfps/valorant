#pragma once

#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <stdio.h>
#include <GLFW/glfw3.h>

#include "../utils/Screen.hpp"
#include "../menus/fonts/ostrich.cpp"
#include "../menus/fonts/walkaway.cpp"

#include "../menus/Menu.hpp"
#include "./Style.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>


class Render 
{
	private:

		static void glfw_error_callback(int error, const char* description)
		{
			fprintf(stderr, "Glfw Error %d: %s\n", error, description);
            std::string message{ "Error code: " + error};
            message += " \nMessage: ";
            message += std::string{ description };

            MessageBoxW(NULL, std::wstring{ message.begin(), message.end() }.c_str(), L"GLFW ERROR", MB_OK);
		}
        inline static GLFWwindow* _window = nullptr;

	public:
		static void Create()
		{
            glfwSetErrorCallback(glfw_error_callback);

            if (!glfwInit()) return;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
            glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

            _window = glfwCreateWindow(600, 350, "VOID", NULL, NULL);
            if (_window == NULL) return;

            auto s = Screen::getSize();

            glfwSetWindowPos(_window, (s.x - 600)/2, (s.y - 350)/2);

            //glfwSetWindowAttrib(_window, GLFW_DECORATED, GLFW_FALSE);
            glfwSetWindowAttrib(_window, GLFW_RESIZABLE, GLFW_FALSE);

            glfwMakeContextCurrent(_window);
            glfwSwapInterval(1); // Enable vsync

            // Setup Dear ImGui context
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            ImGuiIO& io = ImGui::GetIO(); (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

            ImGui::StyleColorsDark();

            ImGui_ImplGlfw_InitForOpenGL(_window, true);
            ImGui_ImplOpenGL3_Init("#version 330"); //DO NOT CHANGE

            glfwShowWindow(_window);

            auto Ostrich = io.Fonts->AddFontFromMemoryCompressedTTF(Ostrich_compressed_data, Ostrich_compressed_size, 18);
            auto WalkAway = io.Fonts->AddFontFromMemoryCompressedTTF(Walkaway_compressed_data, Walkaway_compressed_size, 18);

            io.FontDefault = WalkAway;
            io.WantSaveIniSettings = false;
            io.IniFilename = NULL;

            Style::loadStyle();

            Menu menu;

            // Main loop
            while (Settings::running)
            {
                if (glfwWindowShouldClose(_window))
                {
                    Settings::running = false;
                }

                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                menu.Draw();

                if (GetAsyncKeyState(VK_DELETE) && KEYPRESS)
                    Settings::running = false;

                // Rendering
                ImGui::Render();
                int display_w, display_h;

                glfwGetFramebufferSize(_window, &display_w, &display_h);
                glViewport(0, 0, display_w, display_h);

                glClearColor(32/255, 33 / 255, 36 / 255, 255);

                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                glfwSwapBuffers(_window);
            }

            // Cleanup
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            glfwDestroyWindow(_window);
            glfwTerminate();

            return;
		}
};
#endif