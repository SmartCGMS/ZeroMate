// ---------------------------------------------------------------------------------------------------------------------
/// \file app_preferences.hpp
/// \date 23. 11. 2025
/// \author Martin Ubl (ublm@kiv.zcu.cz)
///
/// \brief This file implements application preferences handling.
// ---------------------------------------------------------------------------------------------------------------------

// STL imports (excluded from Doxygen)
/// \cond
#include <fstream>
#include <string>
#include <unordered_map>
#include <mutex>
/// \endcond

// Project file imports
#include "app_preferences.hpp"

namespace zero_mate::utils::prefs
{
    namespace
    {
        const std::string Preferences_Filename = ".prefs";

        std::mutex g_preferences_mutex;

        std::unordered_map<std::string, NPreference> g_preference_name_to_enum = {
            { "Kernel_Load_Last_Location", NPreference::Kernel_Load_Last_Location },
            { "Processes_Load_Last_Location", NPreference::Processes_Load_Last_Location },
        };

        std::unordered_map<NPreference, std::string> g_preferences;

        void Load_Preferences_From_Disk()
        {
            std::ifstream prefs_file(Preferences_Filename);
            if (!prefs_file)
            {
                // Handle file not found or inaccessible
                return;
            }

            std::string line;
            while (std::getline(prefs_file, line))
            {
                size_t delimiter_pos = line.find('=');
                if (delimiter_pos != std::string::npos)
                {
                    std::string key = line.substr(0, delimiter_pos);
                    std::string value = line.substr(delimiter_pos + 1);
                    auto it = g_preference_name_to_enum.find(key);
                    if (it != g_preference_name_to_enum.end())
                    {
                        g_preferences[it->second] = value;
                    }
                }
            }
        }

        void Save_Preferences_To_Disk()
        {
            std::ofstream prefs_file(Preferences_Filename);
            for (const auto& [key, value] : g_preferences)
            {
                for (const auto& [name, enum_val] : g_preference_name_to_enum)
                {
                    if (enum_val == key)
                    {
                        prefs_file << name << "=" << value << "\n";
                        break;
                    }
                }
            }
        }
    }

    std::string Get_Preference(NPreference preference)
    {
        std::lock_guard<std::mutex> lock(g_preferences_mutex);
        if (g_preferences.empty())
        {
            Load_Preferences_From_Disk();
        }
        auto it = g_preferences.find(preference);
        if (it != g_preferences.end())
        {
            return it->second;
        }
        return "";
    }

    void Set_Preference(NPreference preference, const std::string& value)
    {
        std::lock_guard<std::mutex> lock(g_preferences_mutex);
        g_preferences[preference] = value;
        Save_Preferences_To_Disk();
    }
}
