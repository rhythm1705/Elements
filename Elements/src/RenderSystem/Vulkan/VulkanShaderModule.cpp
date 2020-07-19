#include "VulkanShaderModule.h"

#include "VulkanDevice.h"

namespace Elements {

VulkanShaderModule::VulkanShaderModule(std::string filename, vk::ShaderStageFlagBits stage, std::string entryPoint) :
filename{ filename }, stage{ stage }, entryPoint{ entryPoint } {
    data = readFile(filename);
}

VulkanShaderModule::~VulkanShaderModule() {
}

const std::string &VulkanShaderModule::getFilename() const {
    return filename;
}

const std::vector<uint8_t> &VulkanShaderModule::getData() const {
    return data;
}

vk::ShaderStageFlagBits VulkanShaderModule::getStage() const {
    return stage;
}

const std::string &VulkanShaderModule::getEentryPoint() const {
    return entryPoint;
}

std::vector<uint8_t> VulkanShaderModule::readFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        ELMT_CORE_ERROR("failed to open file!");
    }
    size_t fileSize = (size_t)file.tellg();
    std::vector<uint8_t> buffer(fileSize);
    file.seekg(0);
    file.read(reinterpret_cast<char *>(buffer.data()), fileSize);
    file.close();
    return buffer;
}

} // namespace Elements