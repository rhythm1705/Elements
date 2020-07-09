#include "VulkanShaderManager.h"

#include "VulkanDevice.h"

namespace Elements {
VulkanShaderManager *VulkanShaderManager::instance = nullptr;

VulkanShaderManager *VulkanShaderManager::getInstance() {
    if (!instance) {
        instance = new VulkanShaderManager();
    }
    return instance;
}

vk::ShaderModule VulkanShaderManager::getShaderModule(const std::string &filename) {
    if (shaders.find(filename) == shaders.end()) {
        // Shader not found, load it
        shaders[filename] = createShaderModule(readFile(filename));
        ELMT_CORE_TRACE("Shader '" + filename + "' loaded.");
    }
    // Return the shader
    return shaders[filename];
}

void VulkanShaderManager::cleanUpShaders() {
    vk::Device device = VulkanDevice::getInstance()->getVulkanDevice();
    for (const auto &element : shaders) {
        device.destroyShaderModule(element.second);
        ELMT_CORE_TRACE("Destroying Shader: '" + element.first + "'");
    }
    shaders.clear();
}

std::vector<char> VulkanShaderManager::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        ELMT_CORE_ERROR("failed to open file!");
    }
    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();
    return buffer;
}

vk::ShaderModule VulkanShaderManager::createShaderModule(const std::vector<char> &code) {
    vk::ShaderModuleCreateInfo createInfo(
      vk::ShaderModuleCreateFlags(), code.size(), reinterpret_cast<const uint32_t *>(code.data()));
    vk::ShaderModule shaderModule;
    if (VulkanDevice::getInstance()->getVulkanDevice().createShaderModule(&createInfo, nullptr, &shaderModule)
        != vk::Result::eSuccess) {
        ELMT_CORE_ERROR("Failed to create shader module!");
    }
    return shaderModule;
}

} // namespace Elements