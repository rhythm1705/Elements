#pragma once

#include <vulkan/vulkan.hpp>

namespace Elements {

struct Attachment {
    vk::Format format{ vk::Format::eUndefined };
    vk::SampleCountFlagBits samples{ vk::SampleCountFlagBits::e1 };
    vk::ImageUsageFlags usage{ vk::ImageUsageFlagBits::eSampled };
    vk::ImageLayout initialLayout{ vk::ImageLayout::eUndefined };

    Attachment() = default;
    Attachment(vk::Format format, vk::SampleCountFlagBits samples, vk::ImageUsageFlags usage);
};

class VulkanRenderTarget {};
} // namespace Elements
