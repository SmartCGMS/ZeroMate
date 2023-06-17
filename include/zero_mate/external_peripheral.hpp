// ---------------------------------------------------------------------------------------------------------------------
/// \file external_peripheral.hpp
/// \date 15. 06. 2023
/// \author Jakub Silhavy (jakub.silhavy.cz@gmail.com)
///
/// \brief This file defines an interface for external peripherals that can be attached to the
/// system via GPIO pins at runtime as shared libraries.
// ---------------------------------------------------------------------------------------------------------------------

#pragma once

// STL imports (excluded from Doxygen)
/// \cond
#include <string>
#include <cstdint>
#include <memory>
#include <functional>
#include <unordered_set>
/// \endcond

#include "zero_mate/utils/logger.hpp"

namespace zero_mate
{
    // -----------------------------------------------------------------------------------------------------------------
    /// \class IExternal_Peripheral
    /// \brief This class defines an interface that must be implemented by an external peripheral.
    // -----------------------------------------------------------------------------------------------------------------
    class IExternal_Peripheral
    {
    public:
        /// Alias for a function that sets the value of a GPIO pin
        using Set_GPIO_Pin_t = std::function<int(std::uint32_t, bool)>;

        /// Alias for a function that reads the value of a GPIO pin
        using Read_GPIO_Pin_t = std::function<bool(std::uint32_t)>;

    public:
        // -------------------------------------------------------------------------------------------------------------
        /// \brief Creates an instance of the class
        // -------------------------------------------------------------------------------------------------------------
        IExternal_Peripheral() = default;

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Destroys (deletes) the object from the memory.
        // -------------------------------------------------------------------------------------------------------------
        virtual ~IExternal_Peripheral() = default;

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Deleted copy constructor (rule of five).
        // -------------------------------------------------------------------------------------------------------------
        IExternal_Peripheral(const IExternal_Peripheral&) = delete;

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Deleted assignment operator (rule of five).
        /// \return Instance of this class
        // -------------------------------------------------------------------------------------------------------------
        IExternal_Peripheral& operator=(const IExternal_Peripheral&) = delete;

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Deleted move constructor (rule of five).
        // -------------------------------------------------------------------------------------------------------------
        IExternal_Peripheral(IExternal_Peripheral&&) = delete;

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Deleted assignment operator with an r-value reference (rule of five).
        /// \return Instance of this class
        // -------------------------------------------------------------------------------------------------------------
        IExternal_Peripheral& operator=(IExternal_Peripheral&&) = delete;

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Returns a collection of GPIO pins the peripheral subscribes to.
        ///
        /// The peripheral gets notified whenever the state of any of the listed pins changes.
        ///
        /// \return Collection of GPIO pins the peripheral subscribes to
        // -------------------------------------------------------------------------------------------------------------
        [[nodiscard]] const std::unordered_set<std::uint32_t>& Get_GPIO_Subscription() const
        {
            return m_gpio_subscription;
        }

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Notifies the peripheral that the state of one of the pins it subscribes to has changed.
        /// \note The peripheral may choose not to subscribe to any GPIO pins (e.g. when it is an input peripheral)
        /// \param pin_idx Index of the GPIO pin whose state has been changed
        // -------------------------------------------------------------------------------------------------------------
        [[maybe_unused]] virtual void GPIO_Subscription_Callback([[maybe_unused]] std::uint32_t pin_idx)
        {
        }

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Renders the peripheral (GUI)
        /// \note To be able to render itself as a GUI is not a requirement. The peripheral can be implemented,
        /// for example, as a console application.
        // -------------------------------------------------------------------------------------------------------------
        [[maybe_unused]] virtual void Render()
        {
        }

        // -------------------------------------------------------------------------------------------------------------
        /// \brief Sets ImGuiContext which is used when the peripheral decides to render itself
        ///
        /// The current ImGuiContext needs to be set before the peripheral's GUI is rendered.
        ///
        /// \note The ImGuiContext is passed as a void pointer to avoid compile-time dependency on the ImGUI library
        /// which is used as a GUI library in the main executable (emulator).
        /// \param context Pointer to an ImGuiContext
        // -------------------------------------------------------------------------------------------------------------
        [[maybe_unused]] virtual void Set_ImGui_Context([[maybe_unused]] void* context)
        {
        }

    protected:
        std::unordered_set<std::uint32_t> m_gpio_subscription{}; ///< Collection of GPIO the peripheral subscribes to
    };

} // namespace zero_mate

extern "C"
{
    // -----------------------------------------------------------------------------------------------------------------
    /// \brief Creates an instance of an external peripheral.
    ///
    /// This function is called outside the shared library. It is called by the emulator when it attempts to attach
    /// the peripheral to the GPIO pins.
    ///
    /// \param peripheral
    /// \param name Unique name of the peripheral (e.g. "My button")
    /// \param gpio_pins Collection of GPIO pins the peripherals is hooked up to
    /// \param set_pin Reference to a function the peripheral can use to set GPIO pins
    /// \param read_pin Reference to a function the peripheral can use to read values of GPIO pins
    /// \param logging_system Reference to the logging system that is used throughout the project
    /// \return 0, if all goes well and the peripheral is created successfully. 1, otherwise.
    // -----------------------------------------------------------------------------------------------------------------
    int Create_Peripheral(zero_mate::IExternal_Peripheral** peripheral,
                          const std::string& name,
                          const std::vector<std::uint32_t>& gpio_pins,
                          [[maybe_unused]] zero_mate::IExternal_Peripheral::Set_GPIO_Pin_t set_pin,
                          [[maybe_unused]] zero_mate::IExternal_Peripheral::Read_GPIO_Pin_t read_pin,
                          [[maybe_unused]] zero_mate::utils::CLogging_System& logging_system);
}