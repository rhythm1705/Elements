#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanShaderManager {
  public:
    static VulkanShaderManager *getInstance();

    vk::ShaderModule getShaderModule(const std::string &filename);

    void cleanUpShaders();

  private:
    VulkanShaderManager() = default;
    ~VulkanShaderManager(){};

    static std::vector<char> readFile(const std::string &filename);
    vk::ShaderModule createShaderModule(const std::vector<char> &code);

    static VulkanShaderManager *instance;

    std::unordered_map<std::string, vk::ShaderModule> shaders;
};

} // namespace Elements
