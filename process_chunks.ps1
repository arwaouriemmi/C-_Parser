# Define number of parallel jobs
$jobs = 8
$delay = 2

# Define input and output directory
$inputDir = "C:\Users\utilisateur\IEX_DEEP_HISTORICAL_DATA_PARSER\test_chunks"
$outputDir = "C:\Users\utilisateur\IEX_DEEP_HISTORICAL_DATA_PARSER\o"
$parserPath = "C:\Users\utilisateur\IEX_DEEP_HISTORICAL_DATA_PARSER\build\iex_deep_parser.exe"

# CD into input directory
Set-Location $inputDir

# Function to process a single file
function Process-File {
    param (
        [string]$file
    )

    $inputFile = Join-Path -Path $inputDir -ChildPath $file
    $outputFile = Join-Path -Path $outputDir -ChildPath $file

    # Execute the parser on the file
    & $parserPath $inputFile $outputFile
}

# Get list of files in the input directory
$files = Get-ChildItem -Path $inputDir

# Process files in parallel
for ($i = 0; $i -lt $files.Count; $i += $jobs) {
    $chunk = $files[$i..($i + $jobs - 1)]
    $chunk | ForEach-Object {
        Process-File $_.Name
    }
    Start-Sleep -Seconds $delay  # Introduce delay between chunks if needed
}



