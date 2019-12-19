#ifndef SRC_VULKAN_WINDOW_HPP_
#define SRC_VULKAN_WINDOW_HPP_

#include "vulkan/Vulkan.hpp"

#include <atomic>
#include <memory>
#include <vector>

namespace scin { namespace vk {

class CommandPool;
class Device;
class Instance;
class Swapchain;
class Uniform;

// While technically more a GLFW object than a Vulkan one, Window also maintains
// a VkSurfaceKHR handle, so lives with the rest of the Vulkan objects.
class Window {
public:
    Window(std::shared_ptr<Instance> instance);
    ~Window();

    bool Create(int width, int height);
    bool CreateSyncObjects(Device* device);
    void Run(Device* device, Swapchain* swapchain, CommandPool* command_pool, Uniform* uniform);
    void DestroySyncObjects(Device* device);
    void Destroy();

    // Typically called on another thread, will exit the run() loop on next iteration.
    void stop() { m_stop = true; }

    GLFWwindow* get() { return window_; }
    VkSurfaceKHR get_surface() { return surface_; }
    int width() const { return width_; }
    int height() const { return height_; }

private:
    std::shared_ptr<Instance> instance_;
    int width_;
    int height_;
    GLFWwindow* window_;
    VkSurfaceKHR surface_;
    std::vector<VkSemaphore> image_available_semaphores_;
    std::vector<VkSemaphore> render_finished_semaphores_;
    std::vector<VkFence> in_flight_fences_;
    std::atomic<bool> m_stop;
};

} // namespace vk

} // namespace scin

#endif // SRC_VULKAN_WINDOW_HPP_