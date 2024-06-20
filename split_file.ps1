# Define paths and chunk size
$largeFilePath = "C:\Users\utilisateur\IEX_DEEP_HISTORICAL_DATA_PARSER\extracted_payload.txt"
$outputDir = "C:\Users\utilisateur\IEX_DEEP_HISTORICAL_DATA_PARSER\output_chunks"
$chunkSize = 1000000  # Number of lines per chunk

# Create output directory if it doesn't exist
if (-Not (Test-Path $outputDir)) {
    Write-Host "Creating output directory: $outputDir"
    New-Item -ItemType Directory -Path $outputDir
}

# Initialize variables
$chunkNumber = 0
$lineBuffer = New-Object System.Collections.ArrayList

# Function to write buffer to file and clear buffer
function Write-Chunk {
    param (
        [System.Collections.ArrayList]$buffer,
        [int]$chunkNum,
        [string]$outputDirectory
    )
    $chunkFilePath = Join-Path -Path $outputDirectory -ChildPath ("chunk_{0}.txt" -f $chunkNum)
    Write-Host "Creating chunk file: $chunkFilePath"
    $buffer | Set-Content -Path $chunkFilePath
    $buffer.Clear()
}

# Read the large file line by line and split into chunks
Write-Host "Starting to process file: $largeFilePath"
Get-Content $largeFilePath -ReadCount $chunkSize | ForEach-Object {
    $lineBuffer.AddRange($_)
    Write-Chunk -buffer $lineBuffer -chunkNum $chunkNumber -outputDirectory $outputDir
    $chunkNumber++
}

# Write remaining lines to the last chunk
if ($lineBuffer.Count -gt 0) {
    Write-Chunk -buffer $lineBuffer -chunkNum $chunkNumber -outputDirectory $outputDir
}

Write-Host "Chunk creation completed."

