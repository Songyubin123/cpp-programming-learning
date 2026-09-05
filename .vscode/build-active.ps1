param(
    [Parameter(Mandatory = $true)][string]$SourceFile,
    [Parameter(Mandatory = $true)][string]$Workspace
)
$ErrorActionPreference = 'Stop'
try {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio\Installer\vswhere.exe'
    $installation = & $vswhere -latest -products '*' -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $installation) { throw 'MSVC C++ Build Tools were not found.' }
    $devcmd = Join-Path $installation 'Common7\Tools\VsDevCmd.bat'
    $environment = & $env:ComSpec /d /c "call `"$devcmd`" -no_logo -arch=x64 -host_arch=x64 >nul && set"
    if ($LASTEXITCODE -ne 0) { throw 'Failed to initialize the MSVC environment.' }
    foreach ($entry in $environment) {
        if ($entry -match '^([^=]+)=(.*)$') {
            [Environment]::SetEnvironmentVariable($Matches[1], $Matches[2], 'Process')
        }
    }
    $source = Get-Item -LiteralPath $SourceFile
    $build = Join-Path $Workspace 'build\active'
    New-Item -ItemType Directory -Force -Path $build | Out-Null
    $output = Join-Path $build $source.BaseName
    & cl.exe /Zi /EHsc /nologo /utf-8 "/Fo$output.obj" "/Fd$output.compiler.pdb" "/Fe$output.exe" $source.FullName /link /INCREMENTAL:NO "/PDB:$output.pdb"
    exit $LASTEXITCODE
} catch {
    Write-Error $_ -ErrorAction Continue
    exit 1
}
