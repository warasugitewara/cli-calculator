# PowerShell Profile Integration for calcpp
# Add this to your $PROFILE

function calc {
    <#
    .SYNOPSIS
    Wrapper function for calcpp calculator
    
    .DESCRIPTION
    High-performance CLI calculator for mathematical expressions
    
    .PARAMETER Expression
    Mathematical expression to evaluate
    
    .PARAMETER Precision
    Number of decimal places (1-20)
    
    .EXAMPLE
    calc "3 + 5 * 2"
    calc "sqrt(16)"
    calc -Precision 10 "pi"
    #>
    
    param(
        [Parameter(Position = 0, ValueFromPipeline = $true)]
        [string]$Expression,
        
        [int]$Precision = 15
    )
    
    $calcppPath = "C:\Users\$env:USERNAME\AppData\Local\Programs\calcpp\calcpp.exe"
    
    if (-not (Test-Path $calcppPath)) {
        Write-Error "calcpp not found at $calcppPath"
        return
    }
    
    if ($Precision -ne 15) {
        & $calcppPath -p $Precision $Expression
    } else {
        & $calcppPath $Expression
    }
}

# Tab completion for calc function
$__calcppCompleter = {
    param($wordToComplete, $commandAst, $cursorPosition)
    
    $functions = @(
        'sin', 'cos', 'tan', 'asin', 'acos', 'atan',
        'log', 'log10', 'ln', 'exp',
        'sqrt', 'abs', 'floor', 'ceil', 'round', 'pow'
    )
    
    $constants = @('pi', 'e', 'phi')
    
    $keywords = @('precision', 'history', 'clear', 'vars', 'clearVars', 'help', 'exit', 'quit')
    
    $allSuggestions = @($functions + $constants + $keywords)
    
    $allSuggestions | Where-Object { $_ -like "$wordToComplete*" } | ForEach-Object {
        [System.Management.Automation.CompletionResult]::new($_, $_, 'ParameterValue', $_)
    }
}

# Register completion
if (Get-Command Register-ArgumentCompleter -ErrorAction SilentlyContinue) {
    Register-ArgumentCompleter -CommandName calc -ScriptBlock $__calcppCompleter
}

# Alias for quick access
Set-Alias -Name cc -Value calc -Scope Global -Force

Write-Host "calcpp calculator loaded. Use 'calc <expression>' or 'cc <expression>'" -ForegroundColor Green
