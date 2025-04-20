#pragma once

namespace Help
{
    template<typename EnumType, typename ValueType = uint32_t>
    inline bool IsFlagSet(EnumType Flags, EnumType Flag)
    {
        return (static_cast<ValueType>(Flags) & static_cast<ValueType>(Flag)) != 0;
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void SetFlag(EnumType& Flags, EnumType Flag)
    {
        Flags = static_cast<EnumType>(static_cast<ValueType>(Flags) | static_cast<ValueType>(Flag));
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void ClearFlag(EnumType& Flags, EnumType Flag)
    {
        Flags = static_cast<EnumType>(static_cast<ValueType>(Flags) & ~static_cast<ValueType>(Flag));
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void ToggleFlag(EnumType& Flags, EnumType Flag)
    {
        Flags = static_cast<EnumType>(static_cast<ValueType>(Flags) ^ static_cast<ValueType>(Flag));
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void SetFlagIf(EnumType& Flags, EnumType Flag, bool Condition)
    {
        if (Condition)
            SetFlag<EnumType, ValueType>(Flags, Flag);
        else
            ClearFlag<EnumType, ValueType>(Flags, Flag);
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline bool IsAnyFlagSet(EnumType Flags, EnumType TestFlags)
    {
        return (static_cast<ValueType>(Flags) & static_cast<ValueType>(TestFlags)) != 0;
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline bool AreAllFlagsSet(EnumType Flags, EnumType TestFlags)
    {
        return (static_cast<ValueType>(Flags) & static_cast<ValueType>(TestFlags)) == static_cast<ValueType>(TestFlags);
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void ClearAllFlags(EnumType& Flags)
    {
        Flags = static_cast<EnumType>(0);
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void SetFlags(EnumType& Flags, EnumType FlagsToSet)
    {
        Flags = static_cast<EnumType>(static_cast<ValueType>(Flags) | static_cast<ValueType>(FlagsToSet));
    }

    template<typename EnumType, typename ValueType = uint32_t>
    inline void ClearFlags(EnumType& Flags, EnumType FlagsToClear)
    {
        Flags = static_cast<EnumType>(static_cast<ValueType>(Flags) & ~static_cast<ValueType>(FlagsToClear));
    }

    uint8 DistanceToAlpha(float Distance);
    std::wstring FloatToSingleDec(float Value);
    bool Safety();
}