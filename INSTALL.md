# calcpp Installation and Setup Guide

## Quick Start

### Windows Installation (Automatic)

1. **Run the installer script** (if available):
   ```powershell
   .\install.ps1
   ```

2. **Manual Installation**:
   - Copy `calcpp.exe` to: `C:\Users\<YourUsername>\AppData\Local\Programs\calcpp\`
   - The PATH is automatically added to your system environment variables
   - Restart PowerShell/Nushell to refresh environment

### Verify Installation

```powershell
calcpp --version
calcpp "2 + 2"
```

## Shell Integration Setup

### PowerShell (Recommended for Windows)

1. **Open PowerShell** and run:
   ```powershell
   $PROFILE
   ```
   This shows your profile file location (usually `C:\Users\<username>\Documents\PowerShell\profile.ps1`)

2. **Open the file in your editor**:
   ```powershell
   notepad $PROFILE
   ```

3. **Add this content** to your profile:

```powershell
# calcpp Calculator Function
function calc {
    param(
        [Parameter(Position = 0, ValueFromPipeline = $true)]
        [string]$Expression,
        [int]$Precision = 15
    )
    
    $calcppPath = "C:\Users\$env:USERNAME\AppData\Local\Programs\calcpp\calcpp.exe"
    
    if (-not (Test-Path $calcppPath)) {
        Write-Error "calcpp not found. Please install calcpp first."
        return
    }
    
    if ($Precision -ne 15) {
        & $calcppPath -p $Precision $Expression
    } else {
        & $calcppPath $Expression
    }
}

# Quick alias
Set-Alias -Name cc -Value calc -Scope Global -Force

Write-Host "calcpp calculator ready. Use 'calc' or 'cc' to calculate." -ForegroundColor Cyan
```

4. **Save and restart PowerShell**

5. **Test it**:
   ```powershell
   calc "sqrt(16)"
   cc "2 ^ 10"
   calc -Precision 10 "pi"
   ```

### Nushell Integration

1. **Find your Nushell config** (usually one of):
   - `~\AppData\Roaming\nushell\env.nu`
   - `~\AppData\Roaming\nushell\config.nu`

2. **Add to your config**:

```nushell
# calcpp alias
alias calc = C:\Users\$env.USERNAME\AppData\Local\Programs\calcpp\calcpp.exe

# Enhanced calc with error handling
def calc [expr: string, --precision (-p): int = 15] {
    let calcpp_path = $"C:\Users\($env.USERNAME)\AppData\Local\Programs\calcpp\calcpp.exe"
    
    if ($precision != 15) {
        ^$calcpp_path -p $precision $expr
    } else {
        ^$calcpp_path $expr
    }
}
```

3. **Restart Nushell and test**:
   ```nushell
   calc "3 + 5 * 2"
   calc -p 10 "pi"
   ```

## Building from Source

### Requirements

- **CMake** 3.16 or later
- **C++17 compatible compiler**:
  - Visual Studio 2017+ (Windows)
  - GCC 7+ (Linux)
  - Clang 5+ (macOS/Linux)

### Build Steps

```bash
# Clone or download the repository
cd cli-calculator

# Create build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022"  # Windows
# or
cmake .. -G "Unix Makefiles"  # Linux/macOS

# Build
cmake --build . --config Release

# The executable is at:
# Windows: build\Release\calcpp.exe
# Linux/macOS: build/calcpp
```

### Install Built Binary

```bash
# Linux/macOS
sudo cmake --install . --prefix /usr/local

# Then use: calcpp "2+2"
```

## Troubleshooting

### "calcpp: command not found"

**Solution**: 
1. Check if PATH includes the calcpp directory:
   ```powershell
   $env:PATH -split ';' | Select-String "calcpp"
   ```

2. Manually add to PATH:
   ```powershell
   $newPath = "$env:PATH;C:\Users\$env:USERNAME\AppData\Local\Programs\calcpp"
   [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
   ```

3. Restart your shell

### Build Fails with "m.lib not found"

**Solution**: This is expected on Windows. The fix is in CMakeLists.txt (already applied).

### Precision Not Working

**Ensure you use the correct syntax**:
```powershell
calcpp -p 10 "pi"    # Correct
calc -Precision 10 "pi"   # Also works (PowerShell wrapper)
```

## Usage Examples

### Basic Calculations
```powershell
calc "10 + 5"
calc "20 * 3"
calc "100 / 4"
```

### Scientific Calculations
```powershell
calc "sqrt(16)"
calc "sin(pi/2)"
calc "log10(100)"
```

### High Precision
```powershell
calc -Precision 20 "pi"
calc -Precision 15 "e"
```

### Complex Expressions
```powershell
calc "(3 + 5) * sqrt(4)"
calc "pow(2, 10) + pow(3, 2)"
```

## Tips

- Use the **short alias** for faster typing:
  ```powershell
  cc "2 + 2"
  ```

- **Pipe support** in PowerShell:
  ```powershell
  1..5 | ForEach-Object { calc "$_ * 2" }
  ```

- **High precision mode** for mathematical constants:
  ```powershell
  calc -Precision 20 "pi"
  calc -Precision 20 "e"
  ```

## Support

For issues or questions, refer to:
- `calcpp --help` for command-line help
- `calcpp` then `help` for interactive mode help
- README.md for complete documentation

---

**Version**: 1.0.0  
**Built with**: C++17  
**License**: MIT
