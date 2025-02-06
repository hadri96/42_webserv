<?php
// Define the target directory for deletions
$target_dir = "uploads/";

// Define the error log file
$error_log = 'delete_errors.log';

// Log function to write errors to the log file
function log_error($message) 
{
    global $error_log;
    $error_message = date('Y-m-d H:i:s') . " - ERROR: " . $message . "\n";
    file_put_contents($error_log, $error_message, FILE_APPEND);
}

// Function to prevent directory traversal attacks
function sanitizeFilename($filename) 
{
    // Remove any leading/trailing spaces and null bytes
    $filename = trim($filename);
    
    // Prevent directory traversal attacks by removing "../" or similar sequences
    $filename = basename($filename);

    return $filename;
}

// Check if request method is POST
if ($_SERVER['REQUEST_METHOD'] === 'POST') 
{
    if (!isset($_POST['filename']) || empty($_POST['filename'])) 
    {
        echo "Error: No filename provided.";
        log_error("No filename provided in delete request.");
        exit;
    }

    // Sanitize filename
    $fileName = sanitizeFilename($_POST['filename']);
    $filePath = realpath($target_dir . $fileName);

    // Ensure file exists and is within the uploads directory
    if (!$filePath || strpos($filePath, realpath($target_dir)) !== 0 || !is_file($filePath)) 
    {
        echo "Error: Invalid file.";
        log_error("Attempted deletion of invalid or unsafe file: " . $_POST['filename']);
        exit;
    }

    // Attempt to delete the file
    if (unlink($filePath)) 
    {
        echo "File '$fileName' has been successfully deleted.";
    } 
    else 
    {
        echo "Error: Could not delete the file.";
        log_error("Failed to delete file: " . $fileName);
    }
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Delete a File</title>
</head>
<body>
    <h2>Delete a file</h2>
    <form action="delete.php" method="post">
        <label for="filename">Enter the file name to delete:</label>
        <input type="text" name="filename" id="filename" required>
        <input type="hidden" name="_method" id="DELETE" value="DELETE" required>
        <br><br>
        <button type="submit">Delete File</button>
    </form>
</body>
</html>
