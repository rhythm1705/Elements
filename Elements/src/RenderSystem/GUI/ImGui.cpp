#include "ImGui.h"

#include "Core/Application.h"
#include "RenderSystem/Vulkan/VulkanAPI.h"

namespace Elements {

GUI::GUI() { init(); }

GUI::~GUI() {}

void GUI::init() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    //ImGui_ImplGlfw_InitForVulkan(Application::get().getWindow().getWindowPtr(), true);
    //ImGui_ImplVulkan_InitInfo init_info = {};
    //init_info.Instance = VulkanInstance::getInstance()->getVulkanInstance();
    //init_info.PhysicalDevice = VulkanDevice::getInstance()->getVulkanPhysicalDevice();
    //init_info.Device = VulkanDevice::getInstance()->getVulkanDevice();
    //init_info.QueueFamily = 0;
    //init_info.Queue = VulkanGraphicsQueue::getInstance()->getQueue();
    //init_info.PipelineCache = VK_NULL_HANDLE;
    //// init_info.DescriptorPool = g_DescriptorPool;
    //init_info.Allocator = nullptr;
    //init_info.MinImageCount = 2;
    //init_info.ImageCount = 2;
    //// init_info.CheckVkResultFn = check_vk_result;
    //ImGui_ImplVulkan_Init(&init_info, VulkanGUIRenderPass::getInstance()->getRenderPass());


    //ImGui_ImplVulkan_CreateFontsTexture(command_buffer);
}

} // namespace Elements
