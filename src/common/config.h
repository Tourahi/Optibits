/**********************************************************************************************
*
*   optibits configuration flags
*
*   This file defines all the configuration flags for the different optibits modules
*
*   LICENSE: TO-DO
*
*   Copyright (c) 2025 tourahi
*
**********************************************************************************************/

#ifndef OPTI_CONFIG_H
#define OPTI_CONFIG_H


#if defined(WIN32) || defined(_WIN32)
#   define OPTI_WINDOWS 1
#   if defined(_MSC_VER) && (_MSC_VER >= 1700) && !_USING_V110_SDK71_
#      include <winapifamily.h>
#      if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP) && !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#         define OPTI_WINDOWS_UWP 1
#         define OPTI_NO_MODPLUG 1
#         define OPTI_NOMPG123 1
#       endif
#   endif
#endif

#if defined(linux) || defined(__linux) || defined(__linux__)
#	define OPTI_LINUX 1
#endif
#if defined(__ANDROID__)
#	define OPTI_ANDROID 1
#endif
#if defined(__APPLE__)
#	include <TargetConditionals.h>
#	if TARGET_OS_IPHONE
#		define OPTI_IOS 1
#	elif TARGET_OS_MAC
#		define OPTI_MACOSX 1
#	endif
#endif

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#	define OPTI_LINUX 1
#endif

// Endianness.
#if defined(__ppc__) || defined(__ppc) || defined(__powerpc__) || defined(__powerpc)
#	define OPTI_BIG_ENDIAN 1
#else
#	define OPTI_LITTLE_ENDIAN 1
#endif

// SSE instructions.
#if defined(__SSE__)
#	define OPTI_SIMD_SSE
#elif defined(_MSC_VER)
#	if defined(_M_AMD64) || defined(_M_X64)
#		define OPTI_SIMD_SSE
#	elif _M_IX86_FP
#		define OPTI_SIMD_SSE
#	endif
#endif

// NEON instructions.
#if defined(__ARM_NEON)
#	define OPTI_SIMD_NEON
#endif

// Warnings.
#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS
#endif

#ifndef OPTI_UNUSED
#	define OPTI_UNUSED(x) (void)sizeof(x)
#endif

// Warn on unused return values
#ifdef __GNUC__OPTI_UNUSED
#	define OPTI_WARN_UNUSED __attribute__((warn_unused_result))
#elif _MSC_VER
#	define OPTI_WARN_UNUSED _Check_return_
#else
#	define OPTI_WARN_UNUSED
#endif

#ifndef OPTI_BUILD
#	define OPTI_BUILD
#	define OPTI_BUILD_STANDALONE
#	define OPTI_BUILD_EXE
#endif

// DLL-stuff.
#if defined(_MSC_VER) || defined(__MINGW32__)
#	define OPTI_EXPORT __declspec(dllexport)
#elif defined(__GNUC__) || defined(__clang__)
#	define OPTI_EXPORT __attribute__((visibility("default")))
#else
#	define OPTI_EXPORT
#endif

// Autotools config.h MIGHT NOT BE USED
#ifdef HAVE_CONFIG_H
#	include <../config.h>
#	undef VERSION
#	ifdef WORDS_BIGENDIAN
#		undef OPTI_LITTLE_ENDIAN
#		define OPTI_BIG_ENDIAN 1
#	else
#		undef OPTI_BIG_ENDIAN
#		define OPTI_LITTLE_ENDIAN 1
#	endif
#else
#	define OPTI_ENABLE_DEBUG
#	define OPTI_ENABLE_UTEST
#endif

// Check we have a sane configuration
#if !defined(OPTI_WINDOWS) && !defined(OPTI_LINUX) && !defined(OPTI_IOS) && !defined(OPTI_MACOSX) && !defined(OPTI_ANDROID)
#	error Could not detect target platform
#endif
#if !defined(OPTI_LITTLE_ENDIAN) && !defined(OPTI_BIG_ENDIAN)
#	error Could not detect endianness
#endif

#endif // CONFIG_H
