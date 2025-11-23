// ---------------------------------------------------------------------------------------------------------------------
/// \file app_preferences.hpp
/// \date 23. 11. 2025
/// \author Martin Ubl (ublm@kiv.zcu.cz)
///
/// \brief This file defines a general interface of application preferences.
// ---------------------------------------------------------------------------------------------------------------------

#pragma once

// STL imports (excluded from Doxygen)
/// \cond
#include <string>
/// \endcond

namespace zero_mate::utils::prefs
{
    // -----------------------------------------------------------------------------------------------------------------
    /// \enum NPreference
    /// \brief This enumeration defines different application preferences.
    // -----------------------------------------------------------------------------------------------------------------
    enum class NPreference {
        Kernel_Load_Last_Location,
        Processes_Load_Last_Location,

        count
    };

    // -----------------------------------------------------------------------------------------------------------------
    /// \brief Retrieves a given application preference; always returns a string, which can be converted to the desired
    /// type by the caller.
    /// \param preference The preference to retrieve.
    /// \return The value of the preference as a string.
    // -----------------------------------------------------------------------------------------------------------------
    std::string Get_Preference(NPreference preference);

    // -----------------------------------------------------------------------------------------------------------------
    /// \brief Sets a given application preference.
    /// \param preference The preference to set.
    /// \param value The value to set the preference to.
    /// \return void
    // -----------------------------------------------------------------------------------------------------------------
    void Set_Preference(NPreference preference, const std::string& value);
}
