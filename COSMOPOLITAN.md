# Building MIR with Cosmopolitan Libc

[Cosmopolitan Libc](https://github.com/jart/cosmopolitan) allows building C programs
into "fat binaries" that can run natively on multiple operating systems (Linux, macOS,
Windows, FreeBSD, OpenBSD, NetBSD) without modification.

## Prerequisites

1. Download and install the Cosmopolitan toolchain from https://cosmo.zip/pub/cosmocc/

   ```bash
   mkdir -p cosmocc && cd cosmocc
   wget https://cosmo.zip/pub/cosmocc/cosmocc.zip
   unzip cosmocc.zip
   export PATH="$PWD/bin:$PATH"
   ```

2. Verify the installation:
   ```bash
   cosmocc --version
   ```

## Building MIR

Use the provided Cosmopolitan-specific Makefile:

```bash
make -f GNUmakefile.cosmo
```

This will create the following executables in `build-cosmo/`:

- `c2m` - C to MIR compiler
- `mir-bin-run` - MIR binary runner
- `m2b` - MIR text to binary converter
- `b2m` - MIR binary to text converter
- `b2ctab` - MIR binary to C table converter

## Testing

Run the basic tests with:

```bash
make -f GNUmakefile.cosmo test
```

## Using the Fat Binaries

The resulting binaries can run on any supported platform without modification:

```bash
# On Linux
./build-cosmo/c2m -v sieve.c -ei

# On macOS (same binary!)
./build-cosmo/c2m -v sieve.c -ei

# On Windows (same binary, may need .exe extension or Wine)
./build-cosmo/c2m -v sieve.c -ei
```

## Architecture Support

MIR with Cosmopolitan currently supports:
- x86_64 (AMD64) - Full support
- aarch64 (ARM64) - Full support

When running on a supported architecture, MIR will automatically detect and use
the appropriate code generator at runtime.

## Limitations

1. **JIT Compilation**: MIR generates machine code at runtime for the current
   architecture. While the `c2m` compiler binary itself is portable across OSes,
   the generated machine code is specific to the architecture it runs on.

2. **Platform-specific Features**: Some platform-specific features may not be
   available through the Cosmopolitan abstraction layer.

3. **Shared Libraries**: Cosmopolitan builds produce statically linked binaries.
   The shared library (`libmir.so`) is not available in Cosmopolitan builds.

## Build Options

The `GNUmakefile.cosmo` supports the following variables:

- `PREFIX` - Installation prefix (default: `/usr/local`)
- `BUILD_DIR` - Build output directory (default: `build-cosmo`)
- `SRC_DIR` - Source directory (default: `.`)

Example:

```bash
make -f GNUmakefile.cosmo PREFIX=/opt/mir BUILD_DIR=my-build
```

## Integration with binfmt_misc

On Linux, you can register the fat binary MIR runner with `binfmt_misc` to
transparently run MIR binaries:

```bash
line=:mir:M::MIR::$(pwd)/build-cosmo/mir-bin-run:P
echo $line | sudo tee /proc/sys/fs/binfmt_misc/register
```

Then compile and run C programs via MIR:

```bash
./build-cosmo/c2m your-file.c -o your-file
chmod +x your-file
./your-file your args
```

## Troubleshooting

### "cosmocc not found"

Ensure the Cosmopolitan toolchain is in your PATH:
```bash
export PATH="/path/to/cosmocc/bin:$PATH"
```

### Compilation errors related to system headers

Cosmopolitan provides its own system headers. Ensure you're using `cosmocc` and
not accidentally mixing with the system compiler.

### Runtime errors on unsupported platforms

Check that you're running on a supported architecture:
- x86_64: Intel/AMD 64-bit processors
- aarch64: ARM 64-bit processors (Apple Silicon, Raspberry Pi 4, etc.)

## Further Information

- [Cosmopolitan Libc Documentation](https://justine.lol/cosmopolitan/)
- [MIR Project](https://github.com/vnmakarov/mir)
- [APE Binary Format](https://justine.lol/ape.html)
