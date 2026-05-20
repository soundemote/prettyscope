//////////////////////////////////////////////////////////////////////////
/// @file
/// Various handy utilities
/// @author Lorcan Mc Donagh @copyright 2008-2017 lmdsp
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef HGUARD_LMDSP_UTILS
#define HGUARD_LMDSP_UTILS

#ifdef __cplusplus

namespace lmd {

/// Avoid unused parameter / function warnings
template <typename... Ts>
void ignore_unused(Ts const& ...) {}

template <typename... Ts>
void ignore_unused() {}

}

#endif // __cplusplus

#endif // HGUARD_LMDSP_UTILS
