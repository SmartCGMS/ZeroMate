// ---------------------------------------------------------------------------------------------------------------------
/// \file c7.cpp
/// \date 27. 06. 2023
/// \author Jakub Silhavy (jakub.silhavy.cz@gmail.com)
///
/// \brief This file implements the primary register C7 of coprocessor CP15.
///
/// List of all registers of CP15 can be found over at
/// https://developer.arm.com/documentation/ddi0301/h/system-control-coprocessor/system-control-processor-registers/
/// register-allocation?lang=en
// ---------------------------------------------------------------------------------------------------------------------

// Project file imports

#include "c7.hpp"

namespace zero_mate::coprocessor::cp15
{
    CC7::CC7()
    {
        Init_CRm_R5();
        Init_CRm_R6();
        Init_CRm_R7();
        Init_CRm_R10();
    }

    void CC7::Init_CRm_R5()
    {
        // Index of the C5 secondary register.
        const auto crm_c5_idx = static_cast<std::uint32_t>(NCRm::C5);

        // Initialize all registers of the C5 secondary register (indexed by op2).
        m_regs[crm_c5_idx][static_cast<std::uint32_t>(NCRm_C5_Register::Flush_Prefetch_Buffer)] = 1;
    }

    void CC7::Init_CRm_R6()
    {
        // Index of the C6 secondary register.
        const auto crm_c6_idx = static_cast<std::uint32_t>(NCRm::C6);

        // Initialize all registers of the C6 secondary register (indexed by op2).
        m_regs[crm_c6_idx][static_cast<std::uint32_t>(NCRm_C6_Register::Invalidate_Entire_Data_Cache)] = 1;
    }

    void CC7::Init_CRm_R7()
    {
        // Index of the C7 secondary register.
        const auto crm_c7_idx = static_cast<std::uint32_t>(NCRm::C7);

        // Initialize all registers of the C7 secondary register (indexed by op2).
        m_regs[crm_c7_idx][static_cast<std::uint32_t>(NCRm_C7_Register::Invalidate_Both_Caches)] = 1;
    }

    void CC7::Init_CRm_R10()
    {
        // Index of the C10 secondary register.
        const auto crm_c10_idx = static_cast<std::uint32_t>(NCRm::C10);

        // Initialize all registers of the C10 secondary register (indexed by op2).
        m_regs[crm_c10_idx][static_cast<std::uint32_t>(NCRm_C10_Register::Data_Synchronization_Barrier)] = 1;
    }

    bool CC7::Is_Flush_Prefetch_Buffer_Set() const
    {
        const auto crm_c5_idx = static_cast<std::uint32_t>(NCRm::C5);
        const auto crm_c5_4_idx = static_cast<std::uint32_t>(NCRm_C5_Register::Flush_Prefetch_Buffer);

        // Check if the register is NOT set to 0.
        return m_regs.at(crm_c5_idx).at(crm_c5_4_idx) == 0;
    }

    bool CC7::Is_Invalidate_Entire_Data_Cache_Set() const
    {
        const auto crm_c6_idx = static_cast<std::uint32_t>(NCRm::C6);
        const auto crm_c6_0_idx = static_cast<std::uint32_t>(NCRm_C6_Register::Invalidate_Entire_Data_Cache);

        // Check if the register is NOT set to 0.
        return m_regs.at(crm_c6_idx).at(crm_c6_0_idx) == 0;
    }

    bool CC7::Is_Invalidate_Both_Caches_Set() const
    {
        const auto crm_c7_idx = static_cast<std::uint32_t>(NCRm::C7);
        const auto crm_c7_0_idx = static_cast<std::uint32_t>(NCRm_C7_Register::Invalidate_Both_Caches);

        // Check if the register is NOT set to 0.
        return m_regs.at(crm_c7_idx).at(crm_c7_0_idx) == 0;
    }

    bool CC7::Is_Data_Synchronization_Barrier_Set() const
    {
        const auto crm_c10_idx = static_cast<std::uint32_t>(NCRm::C10);
        const auto crm_c10_4_idx = static_cast<std::uint32_t>(NCRm_C10_Register::Data_Synchronization_Barrier);

        // Check if the register is NOT set to 0.
        return m_regs.at(crm_c10_idx).at(crm_c10_4_idx) == 0;
    }

} // namespace zero_mate::coprocessor::cp15