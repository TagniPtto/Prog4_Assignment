#include "ImGuiComponent.h"
#include <iostream>


#include <SDL.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#include "extensions/imgui_plot.h"


#include <chrono>
#include <vector>



struct Transform
{
    float matrix[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1 };
};

class GameObject3D
{
public:
    Transform transform;
    int ID;
};
class GameObject3D_Alt
{
public:
    GameObject3D_Alt() :ID{}, transform(new Transform()) {}
    Transform* transform;
    int ID;
};

void Exercise1(int sampleSize, float*& xValueList, float*& yValueList, int& valueCount) {

    std::vector<int> data(10000000);

    constexpr int stepAmounts = 11;



    float* averageTime = new float[stepAmounts](0);
    float* stepSizes = new float[stepAmounts](0);


    for (int s{}; s < sampleSize; s++) {

        for (int i{}; i < stepAmounts; i++) {
            stepSizes[i] = std::powf(2.f, (float)i);
            auto startTime = std::chrono::high_resolution_clock::now();
            for (int j{}; j < (int)data.size(); j += (int)stepSizes[i]) {
                data[j] *= 2;
            }
            auto endTime = std::chrono::high_resolution_clock::now();

            averageTime[i] += std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(endTime - startTime).count();

        }
    }
    for (int i{}; i < stepAmounts; i++) {
        averageTime[i] /= sampleSize;
    }
    xValueList = stepSizes;
    yValueList = averageTime;
    valueCount = stepAmounts;
}


void Exercis2(int sampleSize, float*& xValueList, float*& yValueList, int& valueCount) {

    std::vector<GameObject3D> data(10000000);

    constexpr int stepAmounts = 11;



    float* averageTime = new float[stepAmounts](0);
    float* stepSizes = new float[stepAmounts](0);


    for (int s{}; s < sampleSize; s++) {

        for (int i{}; i < stepAmounts; i++) {
            stepSizes[i] = std::powf(2.f, (float)i);
            auto startTime = std::chrono::high_resolution_clock::now();
            for (int j{}; j < (int)data.size(); j += (int)stepSizes[i]) {
                data[j].ID *= 2;
            }
            auto endTime = std::chrono::high_resolution_clock::now();

            averageTime[i] += std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(endTime - startTime).count();

        }
    }
    for (int i{}; i < stepAmounts; i++) {
        averageTime[i] /= sampleSize;
    }
    xValueList = stepSizes;
    yValueList = averageTime;
    valueCount = stepAmounts;
}
void Exercis2Alt(int sampleSize, float*& xValueList, float*& yValueList, int& valueCount) {

    std::vector<GameObject3D_Alt> data(1000000000);

    constexpr int stepAmounts = 11;



    float* averageTime = new float[stepAmounts](0);
    float* stepSizes = new float[stepAmounts](0);


    for (int s{}; s < sampleSize; s++) {

        for (int i{}; i < stepAmounts; i++) {
            stepSizes[i] = std::powf(2.f, (float)i);
            auto startTime = std::chrono::high_resolution_clock::now();
            for (int j{}; j < (int)data.size(); j += (int)stepSizes[i]) {
                data[j].ID *= 2;
            }
            auto endTime = std::chrono::high_resolution_clock::now();

            averageTime[i] += std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(endTime - startTime).count();

        }
    }
    for (int i{}; i < stepAmounts; i++) {
        averageTime[i] /= sampleSize;
    }
    xValueList = stepSizes;
    yValueList = averageTime;
    valueCount = stepAmounts;
}
ImGuiComponent::ImGuiComponent(dae::GameObject& owner, int , int , int , int ): ObjectComponent(owner)
{
    
  
}



void ImGuiComponent::OnGuiRender()
{

    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_Appearing);
    
    ImGui::Begin("Excersise 2 ", &m_tool_active, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
            if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
            if (ImGui::MenuItem("Close", "Ctrl+W")) { m_tool_active = false; }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    static int sampleCount_1 = 100; // Default number of samples
    static bool clicked_Excersise1 = false;

    // Im making this COde at 2:20 am Yeah this is shit
    static float* ys_1;
    static float* xs_1;
    static int valueCount_1;
    ImGui::SliderInt("Samples", &sampleCount_1, 1, 20);
    if (ImGui::Button("Thrasg the cash ")) {

        Exercise1(sampleCount_1, xs_1, ys_1, valueCount_1);
        clicked_Excersise1 = true;
    }
    if (clicked_Excersise1) {
        ImGui::PlotConfig plotConfiguration{};

        plotConfiguration.scale.max = 100;
        plotConfiguration.scale.min = 1;
        plotConfiguration.values.xs = xs_1;
        plotConfiguration.values.ys = ys_1;
        plotConfiguration.values.count = valueCount_1;
        plotConfiguration.values.offset = 0;
        plotConfiguration.tooltip.show = true;
        plotConfiguration.tooltip.format = "x=%10.f, y=%10.f";
        plotConfiguration.grid_x.show = true;
        plotConfiguration.grid_x.size = 1024;
        plotConfiguration.grid_y.show = true;
        plotConfiguration.grid_y.size = 1000;
        plotConfiguration.frame_size = ImVec2(400, 200);
        plotConfiguration.line_thickness = 2.f;
        ImGui::Plot("exercise 1 ", plotConfiguration);
    }

    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x - 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_Appearing);

    static int sampleCount_2 = 0;
    ImGui::Begin("Excersise 3", &m_tool_active, ImGuiWindowFlags_MenuBar);
    ImGui::SliderInt("Samples", &sampleCount_2, 1, 20);

    static float* ys_2;
    static float* xs_2;
    static int valueCount_2;
    static bool clicked_Excersise2_1 = false;
    if (ImGui::Button("Thrasg the cash ")) {
        Exercis2(sampleCount_2, xs_2, ys_2, valueCount_2);
        clicked_Excersise2_1 = true;
    }
    static float* ys_3;
    static float* xs_3;
    static int valueCount_3;
    static bool clicked_Excersise2_2 = false;
    if (ImGui::Button("Thrasg the cash ALt")) {
        Exercis2(sampleCount_2, xs_3, ys_3, valueCount_3);
        clicked_Excersise2_2 = true;
    }
    if (clicked_Excersise2_1) {
        ImGui::PlotConfig plotConfiguration{};

        plotConfiguration.scale.max = 100;
        plotConfiguration.scale.min = 1;
        plotConfiguration.values.xs = xs_2;
        plotConfiguration.values.ys = ys_2;
        plotConfiguration.values.count = valueCount_2;
        plotConfiguration.values.offset = 0;
        plotConfiguration.tooltip.show = true;
        plotConfiguration.tooltip.format = "x=%10.f, y=%10.f";
        plotConfiguration.grid_x.show = true;
        plotConfiguration.grid_x.size = 1024;
        plotConfiguration.grid_y.show = true;
        plotConfiguration.grid_y.size = 1000;
        plotConfiguration.frame_size = ImVec2(400, 200);
        plotConfiguration.line_thickness = 2.f;
        ImGui::Plot("exercise 2 ", plotConfiguration);
    }
    if (clicked_Excersise2_2) {
        ImGui::PlotConfig plotConfiguration{};

        plotConfiguration.scale.max = 100;
        plotConfiguration.scale.min = 1;
        plotConfiguration.values.xs = xs_3;
        plotConfiguration.values.ys = ys_3;
        plotConfiguration.values.count = valueCount_3;
        plotConfiguration.values.offset = 0;
        plotConfiguration.tooltip.show = true;
        plotConfiguration.tooltip.format = "x=%10.f, y=%10.f";
        plotConfiguration.grid_x.show = true;
        plotConfiguration.grid_x.size = 1024;
        plotConfiguration.grid_y.show = true;
        plotConfiguration.grid_y.size = 10000;
        plotConfiguration.frame_size = ImVec2(400, 200);
        plotConfiguration.line_thickness = 2.f;
        ImGui::Plot("exercise 2 ALT ", plotConfiguration);
    }
    //if (clicked_Excersise2_1 && clicked_Excersise2_2) {
    //    ImGui::PlotConfig plotConfiguration{};

    //    plotConfiguration.scale.max = 1024;
    //    plotConfiguration.scale.min = 1;
    //    plotConfiguration.values.xs = xs_3;
    //    plotConfiguration.values.ys = ys_3;
    //    plotConfiguration.values.count = valueCount_3;
    //    plotConfiguration.values.offset = 0;
    //    plotConfiguration.tooltip.show = true;
    //    plotConfiguration.tooltip.format = "x=%10.f, y=%10.f";
    //    plotConfiguration.grid_x.show = true;
    //    plotConfiguration.grid_x.size = 1024;
    //    plotConfiguration.grid_y.show = true;
    //    plotConfiguration.grid_y.size = 100000;
    //    plotConfiguration.frame_size = ImVec2(400, 200);
    //    plotConfiguration.line_thickness = 2.f;
    //    ImGui::Plot("exercise 2 ", plotConfiguration);
    //    plotConfiguration.values.ys = ys_2;
    //    plotConfiguration.values.count = valueCount_2;

    //    ImGui::Plot("exercise 2 ALT ", plotConfiguration);
    //}

    ImGui::End();
    //ImGui::ShowDemoWindow((bool*)1);
}


