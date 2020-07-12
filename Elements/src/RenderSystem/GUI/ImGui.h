#pragma once

#include <imgui.h>

#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_vulkan.h"

namespace Elements {

class GUI {
    public:
      GUI();
      ~GUI();

    private:
      void init();
};

} // namespace Elements
