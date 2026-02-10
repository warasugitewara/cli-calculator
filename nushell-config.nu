# Nushell Integration for calcpp
# Add this to your env.nu or config.nu

# Define calc alias/function
alias calc = C:\Users\$env.USERNAME\AppData\Local\Programs\calcpp\calcpp.exe

# Enhanced calc function with error handling
def calc [expr: string, --precision (-p): int = 15] {
    let calcpp_path = $"C:\Users\($env.USERNAME)\AppData\Local\Programs\calcpp\calcpp.exe"
    
    if ($precision != 15) {
        ^$calcpp_path -p $precision $expr
    } else {
        ^$calcpp_path $expr
    }
}

# Examples:
# calc "3 + 5 * 2"
# calc "sqrt(16)"
# calc -p 10 "pi"

# Pipe-friendly wrapper
def math-pipe [] {
    each { calc $in }
}

# Example: [1, 2, 3, 4, 5] | each { $"$in ^ 2" } | math-pipe
