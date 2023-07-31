#define GLFW_INCLUDE_VULKAN // Will include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApp
{
public:
    void Run()
    {
        InitWindow();
        InitVulkan();
        MainLoop();
        Cleanup();
    }

private:
    void InitWindow()
    {
        glfwInit();

        // Need to tell glfw not to create an OpenGL context (OpenGL is default for GLFW)
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // temp

        m_Window = glfwCreateWindow(WIDTH, HEIGHT, "Learn Vulkan", nullptr, nullptr);
    }

    void InitVulkan()
    {
        CreateInstance();
    }

    void MainLoop()
    {
        while (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
        }
    }

    void Cleanup()
    {
        vkDestroyInstance(m_VulkanInstance, nullptr);
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void CreateInstance()
    {
        // Vulkan object creation function parameters pattern:
        // 1. Pointer to struct with creation info
        // 2. Pointer to custom allocator callbacks, always nullptr in this tutorial
        // 3. Pointer to the variable that stores the handle to the new object

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Learn Vulkan";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        // Create instance
        VkResult result = vkCreateInstance(&createInfo, nullptr, &m_VulkanInstance);
        if (result != VK_SUCCESS)
            throw std::runtime_error("failed to create instance!");

        // Check extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        
        std::cout << "Available extensions: \n";
        for (const auto& extension : extensions)
        {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

private:
    GLFWwindow* m_Window;

    VkInstance m_VulkanInstance;
};

int main() {
    
    HelloTriangleApp app;

    try
    {
        app.Run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}