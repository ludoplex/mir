/* This file is a part of MIR project.
   Copyright (C) 2018-2024 Vladimir Makarov <vmakarov.gcc@gmail.com>.
   
   Cosmopolitan Libc support for MIR.
   
   This header provides architecture identification utilities when building
   with Cosmopolitan Libc to create fat binaries that run on multiple
   platforms and architectures (x86_64 and aarch64).
   
   Note: Cosmopolitan fat binaries contain separate code sections for each
   architecture. The APE (Actually Portable Executable) loader selects the
   correct code section at runtime. Therefore, the preprocessor macros 
   (__x86_64__, __aarch64__, etc.) correctly identify the architecture for
   the code section being compiled, and this code runs only on that architecture.
*/

#ifndef MIR_COSMO_H
#define MIR_COSMO_H

#ifdef MIR_COSMO

/* MIR_ARCH enum for architecture identification */
typedef enum {
  MIR_ARCH_X86_64,
  MIR_ARCH_AARCH64,
  MIR_ARCH_PPC64,
  MIR_ARCH_S390X,
  MIR_ARCH_RISCV64,
  MIR_ARCH_UNKNOWN
} MIR_arch_t;

/* Get the architecture of the currently running code section.
   In a Cosmopolitan fat binary, this returns the architecture for
   which this code section was compiled, which is the same as the
   architecture the binary is currently running on (due to APE loader). */
static inline MIR_arch_t mir_get_arch(void) {
#if defined(__x86_64__) || defined(_M_AMD64)
  return MIR_ARCH_X86_64;
#elif defined(__aarch64__)
  return MIR_ARCH_AARCH64;
#elif defined(__PPC64__)
  return MIR_ARCH_PPC64;
#elif defined(__s390x__)
  return MIR_ARCH_S390X;
#elif defined(__riscv) && __riscv_xlen == 64 && __riscv_flen >= 64 && \
      __riscv_float_abi_double && __riscv_mul && __riscv_div && __riscv_compressed
  /* Only 64-bit RISC-V with at least rv64imafdc is supported */
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
