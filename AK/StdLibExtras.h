/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#define UNUSED_PARAM(x) (void)x

inline constexpr unsigned round_up_to_power_of_two(unsigned value, unsigned power_of_two)
{
    return ((value - 1) & ~(power_of_two - 1)) + power_of_two;
}

namespace AK {

template<typename T>
inline constexpr T min(const T& a, const T& b)
{
    return a < b ? a : b;
}

template<typename T>
inline constexpr T max(const T& a, const T& b)
{
    return a < b ? b : a;
}

template<typename T>
inline constexpr T clamp(const T& value, const T& min, const T& max)
{
    ASSERT(max >= min);
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}

template<typename T, typename U>
inline constexpr T ceil_div(T a, U b)
{
    static_assert(sizeof(T) == sizeof(U));
    T result = a / b;
    if ((a % b) != 0)
        ++result;
    return result;
}

#ifdef __clang__
#    pragma clang diagnostic push
#    pragma clang diagnostic ignored "-Wconsumed"
#endif
template<typename T>
inline T&& move(T& arg)
{
    return static_cast<T&&>(arg);
}
#ifdef __clang__
#    pragma clang diagnostic pop
#endif

template<typename T, typename U>
inline void swap(T& a, U& b)
{
    U tmp = move((U&)a);
    a = (T &&) move(b);
    b = move(tmp);
}

template<bool B, class T = void>
struct EnableIf {
};

template<class T>
struct EnableIf<true, T> {
    typedef T Type;
};

template<class T>
struct RemoveConst {
    typedef T Type;
};
template<class T>
struct RemoveConst<const T> {
    typedef T Type;
};
template<class T>
struct RemoveVolatile {
    typedef T Type;
};
template<class T>
struct RemoveVolatile<volatile T> {
    typedef T Type;
};
template<class T>
struct RemoveCV {
    typedef typename RemoveVolatile<typename RemoveConst<T>::Type>::Type Type;
};

template<class T, T v>
struct IntegralConstant {
    static constexpr T value = v;
    typedef T ValueType;
    typedef IntegralConstant Type;
    constexpr operator ValueType() const { return value; }
    constexpr ValueType operator()() const { return value; }
};

typedef IntegralConstant<bool, false> FalseType;
typedef IntegralConstant<bool, true> TrueType;

template<class T>
struct IsLvalueReference : FalseType {
};

template<class T>
struct IsLvalueReference<T&> : TrueType {
};

template<class T>
struct __IsPointerHelper : FalseType {
};

template<class T>
struct __IsPointerHelper<T*> : TrueType {
};

template<class T>
struct IsPointer : __IsPointerHelper<typename RemoveCV<T>::Type> {
};

template<class>
struct IsFunction : FalseType {
};

template<class Ret, class... Args>
struct IsFunction<Ret(Args...)> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...)> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) const> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) const> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) volatile> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) volatile> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) const volatile> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) const volatile> : TrueType {
};

template<class Ret, class... Args>
struct IsFunction<Ret(Args...)&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...)&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) const&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) const&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) volatile&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) volatile&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) const volatile&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) const volatile&> : TrueType {
};

template<class Ret, class... Args>
struct IsFunction<Ret(Args...) &&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) &&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) const&&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) const&&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) volatile&&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) volatile&&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args...) const volatile&&> : TrueType {
};
template<class Ret, class... Args>
struct IsFunction<Ret(Args..., ...) const volatile&&> : TrueType {
};

template<class T>
struct IsRvalueReference : FalseType {
};
template<class T>
struct IsRvalueReference<T&&> : TrueType {
};

template<class T>
struct RemovePointer {
    typedef T Type;
};
template<class T>
struct RemovePointer<T*> {
    typedef T Type;
};
template<class T>
struct RemovePointer<T* const> {
    typedef T Type;
};
template<class T>
struct RemovePointer<T* volatile> {
    typedef T Type;
};
template<class T>
struct RemovePointer<T* const volatile> {
    typedef T Type;
};

template<typename T, typename U>
struct IsSame {
    enum {
        value = 0
    };
};

template<typename T>
struct IsSame<T, T> {
    enum {
        value = 1
    };
};

template<bool condition, class TrueType, class FalseType>
struct Conditional {
    typedef TrueType Type;
};

template<class TrueType, class FalseType>
struct Conditional<false, TrueType, FalseType> {
    typedef FalseType Type;
};

template<typename T>
struct RemoveReference {
    typedef T Type;
};
template<class T>
struct RemoveReference<T&> {
    typedef T Type;
};
template<class T>
struct RemoveReference<T&&> {
    typedef T Type;
};

template<class T>
inline constexpr T&& forward(typename RemoveReference<T>::Type& param)
{
    return static_cast<T&&>(param);
}

template<class T>
inline constexpr T&& forward(typename RemoveReference<T>::Type&& param) noexcept
{
    static_assert(!IsLvalueReference<T>::value, "Can't forward an rvalue as an lvalue.");
    return static_cast<T&&>(param);
}

template<typename T>
struct MakeUnsigned {
};

template<>
struct MakeUnsigned<signed char> {
    typedef unsigned char type;
};

template<>
struct MakeUnsigned<short> {
    typedef unsigned short type;
};

template<>
struct MakeUnsigned<int> {
    typedef unsigned type;
};

template<>
struct MakeUnsigned<long> {
    typedef unsigned long type;
};

template<>
struct MakeUnsigned<long long> {
    typedef unsigned long long type;
};

template<>
struct MakeUnsigned<unsigned char> {
    typedef unsigned char type;
};

template<>
struct MakeUnsigned<unsigned short> {
    typedef unsigned short type;
};

template<>
struct MakeUnsigned<unsigned int> {
    typedef unsigned type;
};

template<>
struct MakeUnsigned<unsigned long> {
    typedef unsigned long type;
};

template<>
struct MakeUnsigned<unsigned long long> {
    typedef unsigned long long type;
};

template<typename T>
struct MakeSigned {
};

template<>
struct MakeSigned<signed char> {
    typedef signed char type;
};

template<>
struct MakeSigned<short> {
    typedef short type;
};

template<>
struct MakeSigned<int> {
    typedef int type;
};

template<>
struct MakeSigned<long> {
    typedef long type;
};

template<>
struct MakeSigned<long long> {
    typedef long long type;
};

template<>
struct MakeSigned<unsigned char> {
    typedef char type;
};

template<>
struct MakeSigned<unsigned short> {
    typedef short type;
};

template<>
struct MakeSigned<unsigned int> {
    typedef int type;
};

template<>
struct MakeSigned<unsigned long> {
    typedef long type;
};

template<>
struct MakeSigned<unsigned long long> {
    typedef long long type;
};

template<typename T, typename U = T>
inline constexpr T exchange(T& slot, U&& value)
{
    T old_value = move(slot);
    slot = forward<U>(value);
    return old_value;
}

}

using AK::ceil_div;
using AK::clamp;
using AK::Conditional;
using AK::exchange;
using AK::forward;
using AK::IsSame;
using AK::MakeSigned;
using AK::MakeUnsigned;
using AK::max;
using AK::min;
using AK::move;
using AK::RemoveConst;
using AK::swap;
