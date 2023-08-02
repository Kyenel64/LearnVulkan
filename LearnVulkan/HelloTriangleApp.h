#pragma once

#define GLFW_INCLUDE_VULKAN // Will include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>

class HelloTriangleApp
{
public:
    void Run();

private:
    void InitWindow();
    void InitVulkan();

    void MainLoop();
    void Cleanup();

    void CreateInstance();
    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void SetupDebugMessenger();
    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

private:
    GLFWwindow* m_Window;
    VkInstance m_VulkanInstance;

    VkDebugUtilsMessengerEXT m_DebugMessenger;
};