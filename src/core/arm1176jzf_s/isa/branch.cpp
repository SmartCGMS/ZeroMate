// ---------------------------------------------------------------------------------------------------------------------
/// \file branch.cpp
/// \date 25. 05. 2023
/// \author Jakub Silhavy (jakub.silhavy.cz@gmail.com)
///
/// \brief This file implements a branch instruction (B, BL) as defined in branch.hpp.
///
/// To find more information about this instruction, please visit
/// https://developer.arm.com/documentation/dui0068/b/CIHFDDAF
// ---------------------------------------------------------------------------------------------------------------------

#include "branch.hpp"
#include "zero_mate/utils/math.hpp"

namespace zero_mate::arm1176jzf_s::isa
{
    CBranch::CBranch(CInstruction instruction) noexcept
    : CInstruction{ instruction.Get_Value() }
    {
    }

    bool CBranch::Is_L_Bit_Set() const noexcept
    {
        return static_cast<bool>((m_value >> 24U) & 0b1U);
    }

    std::int32_t CBranch::Get_Offset() const noexcept
    {
        static constexpr std::uint32_t Mask_28_Bits = 0xFFFFFFFU;
        static constexpr std::uint32_t Mask_24_Bits = 0xFFFFFFU;

        // Check if the offset is negative.
        if (utils::math::Is_Bit_Set(m_value, 23U))
        {
            const std::uint32_t twos_compliment = ((~(m_value & Mask_28_Bits) + 1) & Mask_24_Bits);
            return -static_cast<std::int32_t>(twos_compliment << 2U);
        }

        return static_cast<std::int32_t>((m_value & Mask_24_Bits) << 2U);
    }

} // namespace zero_mate::arm1176jzf_s::isa