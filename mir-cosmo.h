/* This file is a part of MIR project.
   Copyright (C) 2018-2024 Vladimir Makarov <vmakarov.gcc@gmail.com>.
   
   Cosmopolitan Libc support for MIR.
   
   This header provides runtime architecture detection when building
   with Cosmopolitan Libc to create fat binaries that run on multiple
   platforms and architectures (x86_64 and aarch64).
*/

#ifndef MIR_COSMO_H
#define MIR_COSMO_H

#ifdef MIR_COSMO

/* Cosmopolitan provides these architecture detection macros at runtime */
#if defined(__COSMOPOLITAN__)
#include <libc/runtime/runtime.h>
#endif

/* MIR_ARCH enum for runtime architecture selection */
typedef enum {
  MIR_ARCH_X86_64,
  MIR_ARCH_AARCH64,
  MIR_ARCH_PPC64,
  MIR_ARCH_S390X,
  MIR_ARCH_RISCV64,
  MIR_ARCH_UNKNOWN
} MIR_arch_t;

/* Runtime architecture detection function */
static inline MIR_arch_t mir_get_arch(void) {
#if defined(__x86_64__) || defined(_M_AMD64)
  return MIR_ARCH_X86_64;
#elif defined(__aarch64__)
  return MIR_ARCH_AARCH64;
#elif defined(__PPC64__)
  return MIR_ARCH_PPC64;
#elif defined(__s390x__)
  return MIR_ARCH_S390X;
#elif defined(__riscv)
  return MIR_ARCH_RISCV64;
#else
  return MIR_ARCH_UNKNOWN;
#endif
}

/* Architecture name for logging/debugging */
static inline const char *mir_get_arch_name(void) {
  switch (mir_get_arch()) {
    case MIR_ARCH_X86_64:  return "x86_64";
    case MIR_ARCH_AARCH64: return "aarch64";
    case MIR_ARCH_PPC64:   return "ppc64";
    case MIR_ARCH_S390X:   return "s390x";
    case MIR_ARCH_RISCV64: return "riscv64";
    default:               return "unknown";
  }
}

/* Check if running on a supported architecture */
static inline int mir_arch_supported(void) {
  return mir_get_arch() != MIR_ARCH_UNKNOWN;
}

#endif /* MIR_COSMO */

#endif /* MIR_COSMO_H */
