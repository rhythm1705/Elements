#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

class VulkanShaderModule {
  public:
    VulkanShaderModule(std::string filename, vk::ShaderStageFlagBits stage, std::string entryPoint);
    ~VulkanShaderModule();

    const std::string &getFilename() const;
    const std::vector<uint8_t> &getData() const;
    vk::ShaderStageFlagBits getStage() const;
    const std::string &getEentryPoint() const;

  private:
    std::vector<uint8_t> readFile(const std::string &filename);

    std::string filename;
    std::vector<uint8_t> data;
    vk::ShaderStageFlagBits stage;
    std::string entryPoint;
};

} // namespace Elements
