# calcpp - 高等学校数学対応CLI電卓

高性能なコマンドラインベースの計算機です。C++17で実装され、CASIO FX-JP500CW-Nと互換性を持つ機能を備えています。

## 特徴

### 📊 基本演算
- **四則演算**: `+`, `-`, `*`, `/`
- **べき乗・余り**: `^`（べき乗）、`%`（モジュロ）
- **科学記法**: `1.5e3`, `2e-4`, `1.23E+10` などのe記号表記に対応

### 🔢 数学関数

**三角関数**: `sin`, `cos`, `tan`, `asin`, `acos`, `atan`

**対数関数**: `log`（log10）, `log10`, `ln`, `exp`

**その他**: `sqrt`, `abs`, `floor`, `ceil`, `round`, `pow`

### 📈 数学定数（CASIO精度準拠）
- `pi` (π): 3.14159265358979323846...
- `e`: 2.71828182845904523536...
- `phi` (φ): 1.61803398874989484820...

### 🎯 CASIO互換機能

**分数計算**
- 分数形式での入力・計算対応
- 自動約分（最大公約数による簡約）
- 小数↔分数変換（`tofrac`コマンド）

### 💻 入力モード

1. **標準入力モード**: コマンドライン引数で直接計算
   ```bash
   calcpp "3 + 5 * 2"
   calcpp "sqrt(16)"
   ```

2. **対話型REPL モード**: 複数の計算を順序立てて実行
   ```bash
   calcpp
   > 3 + 5
   8
   > * 2
   16
   ```

### ⚙️ 高度な機能
- **変数保存**: `a = 5` で変数を定義し、後で使用
- **計算履歴**: `history` コマンドで計算履歴を表示
- **精度制御**: 小数点以下1～20桁で精度を調整
- **エラーハンドリング**: ゼロ除算などの不正な計算を検出

### 🐚 シェル統合
- **PowerShell**: ラッパー関数とTab補完対応
- **Nushell**: ネイティブ統合スクリプト提供
- **システムPATH登録**: インストール時に自動登録

## インストール

### Windows プレビルド版

実行ファイルは以下に インストールされています：
```
C:\Users\<ユーザー名>\AppData\Local\Programs\calcpp\calcpp.exe
```

システムPATHに自動登録されているため、どのディレクトリからでも使用できます。

### ソースからビルド

#### 必要な環境
- CMake 3.16 以上
- C++17対応コンパイラ
  - Visual Studio 2017以降（Windows）
  - GCC 7以上（Linux）
  - Clang 5以上（macOS）

#### ビルド手順

```bash
cd cli-calculator
mkdir build
cd build

# CMake設定
cmake .. -G "Visual Studio 17 2022"  # Windows
# または
cmake .. -G "Unix Makefiles"         # Linux/macOS

# ビルド
cmake --build . --config Release

# 実行ファイル
# Windows: build\Release\calcpp.exe
# Linux/macOS: build/calcpp
```

#### Linux/macOSへのインストール

```bash
sudo cmake --install . --prefix /usr/local
# 使用方法: calcpp "2+2"
```

## 使用方法

### 標準入力モード

コマンドライン引数として計算式を渡します：

```bash
calcpp "3 + 5 * 2"
# 出力: 13

calcpp "sqrt(16)"
# 出力: 4

calcpp "sin(pi/2)"
# 出力: 1

calcpp "pow(2, 10)"
# 出力: 1024

calcpp -p 10 "pi"
# 出力: 3.1415926536
```

### 対話型モード

引数なしで起動すると対話型モードになります：

```bash
calcpp
```

その後、プロンプトで計算式を入力します：

```
> 3 + 5
8
> * 2
16
> sqrt(100)
10
> precision 8
精度を 8 桁に設定しました
> pi
3.14159265
> a = 25
a = 25
> sqrt(a)
5
> history
[1] 3 + 5
[2] * 2
[3] sqrt(100)
[4] a = 25
[5] sqrt(a)
> exit
```

## コマンドラインオプション

- `-h, --help`: ヘルプメッセージを表示
- `-v, --version`: バージョン情報を表示
- `-p, --precision N`: 計算前に精度を設定（1～20桁）

## 対話型コマンド一覧

- `help` - 利用可能なコマンド一覧を表示
- `history` - 計算履歴を表示
- `clear` - 履歴をクリア
- `precision <n>` - 小数精度を設定（1～20）
- `tofrac` - 前回の計算結果を分数に変換（CASIO互換機能）
- `vars` - 定義済み変数を表示
- `clearVars` - すべての変数をクリア
- `exit` / `quit` - 電卓を終了

## 計算例

### 基本計算
```bash
calcpp "10 + 5"          # 15
calcpp "20 - 3"          # 17
calcpp "4 * 5"           # 20
calcpp "100 / 4"         # 25
```

### べき乗と余り
```bash
calcpp "2^5"             # 32
calcpp "2 ^ 10"          # 1024
calcpp "17 % 5"          # 2
```

### 関数
```bash
calcpp "sqrt(25)"        # 5
calcpp "abs(-10)"        # 10
calcpp "floor(3.7)"      # 3
calcpp "ceil(3.2)"       # 4
calcpp "round(3.5)"      # 4
```

### 三角関数
```bash
calcpp "sin(pi/2)"       # 1
calcpp "cos(0)"          # 1
calcpp "tan(pi/4)"       # 1
```

### 対数関数
```bash
calcpp "log10(100)"      # 2
calcpp "ln(e)"           # 1
calcpp "exp(1)"          # 2.71828...
```

### 複雑な式
```bash
calcpp "(3 + 5) * 2"     # 16
calcpp "sqrt(4) + pow(2, 3)"  # 10
calcpp "pi * 5^2"        # 78.539...
```

### 科学記法
```bash
calcpp "1.5e3"           # 1500
calcpp "2e-4"            # 0.0002
calcpp "1.23e-10"        # 0.000000000123
calcpp "0.1 * 10^4"      # 1000
```

### CASIO互換：分数計算
```bash
calcpp "1/2 + 1/3"       # 0.833... (5/6)
calcpp "3/4 * 2/3"       # 0.5 (1/2)
calcpp "(1/2 + 1/3) * 2" # 1.666... (5/3)
```

## シェル統合

### PowerShell統合

お使いのPowerShellプロファイルに以下を追加してください：

```powershell
function calc {
    param(
        [Parameter(Position = 0, ValueFromPipeline = $true)]
        [string]$Expression,
        [int]$Precision = 15
    )
    
    $calcppPath = "C:\Users\$env:USERNAME\AppData\Local\Programs\calcpp\calcpp.exe"
    
    if (-not (Test-Path $calcppPath)) {
        Write-Error "calcppが見つかりません。インストールしてください。"
        return
    }
    
    if ($Precision -ne 15) {
        & $calcppPath -p $Precision $Expression
    } else {
        & $calcppPath $Expression
    }
}

Set-Alias -Name cc -Value calc -Scope Global -Force
```

使用方法：
```powershell
calc "sqrt(16)"
calc -Precision 10 "pi"
cc "2^10"
```

### Nushell統合

Nushell設定ファイル（`env.nu` または `config.nu`）に以下を追加してください：

```nushell
alias calc = C:\Users\$env.USERNAME\AppData\Local\Programs\calcpp\calcpp.exe

def calc [expr: string, --precision (-p): int = 15] {
    let calcpp_path = $"C:\Users\($env.USERNAME)\AppData\Local\Programs\calcpp\calcpp.exe"
    
    if ($precision != 15) {
        ^$calcpp_path -p $precision $expr
    } else {
        ^$calcpp_path $expr
    }
}
```

使用方法：
```nushell
calc "3 + 5 * 2"
calc -p 10 "pi"
```

## トラブルシューティング

### "calcpp: コマンドが見つかりません"

**解決方法**：
1. PATHを確認してください：
   ```powershell
   $env:PATH -split ';' | Select-String "calcpp"
   ```

2. 手動でPATHに追加：
   ```powershell
   $newPath = "$env:PATH;C:\Users\$env:USERNAME\AppData\Local\Programs\calcpp"
   [Environment]::SetEnvironmentVariable("Path", $newPath, "User")
   ```

3. シェルを再起動してください

### 精度オプションが機能しない

正しい構文を使用してください：
```bash
calcpp -p 10 "pi"       # 正しい
calc -Precision 10 "pi" # PowerShellラッパー経由
```

## 技術仕様

### 演算子の優先度（高い順）

1. 関数と括弧: `sin()`, `sqrt()`, `()`
2. べき乗: `^`
3. 単項マイナス: `-`
4. 乗算、除算、モジュロ: `*`, `/`, `%`
5. 加算、減算: `+`, `-`

### サポート型

- 倍精度浮動小数点数（IEEE 754 64ビット）
- 分数（GCD基づく自動約分）

## 対応プラットフォーム

- **Windows**: XP SP3 以降
- **Linux**: glibc 2.17以上（Ubuntu 14.04以降など）
- **macOS**: 10.9（Mavericks）以降

## パフォーマンス

- C++17を使用した高速実装
- 最適化コンパイル（-O2/-O3）
- ほとんどの計算は1ms未満で完了
- 最小限のメモリフットプリント（実行ファイル約76KB）

## ライセンス

MIT License

## 貢献

バグ報告や機能要求は、GitHubのIssueセクションでお願いします。

## 作成者

C++17で高等学校以上の数学計算に対応するCLI電卓として開発されました。

---

詳細については、`INSTALL.md` をご参照ください。
対話型モードで `help` を入力するとコマンド一覧が表示されます。
