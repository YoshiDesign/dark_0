#pragma once
#include <dark_core.h>
#include <iostream>
#include "MainGui.h"

namespace dark {

    MainGui::MainGui() : counter(0), f(0.0f) {}

    void MainGui::InitImGui(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

        Gui_RegisterTests();
    }

    MainGui::~MainGui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        delete currentTest;
        if (currentTest != testMenu)
            delete testMenu;

    }

    void MainGui::Gui_RegisterTests()
    {
        currentTest = testMenu;
        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        //testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
    }

    void MainGui::Gui_NewFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void MainGui::Gui_Present()
    {

        if (currentTest)
        {

            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Tests!");

            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            for (auto& db : debug_data)
            {
                ImGui::Text(
                    "%s : %f", db.first, db.second);
            }

            // Render the current test's implementation
            currentTest->OnImguiRender();
            ImGui::End();
        }

    }

    void MainGui::Gui_Render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

}