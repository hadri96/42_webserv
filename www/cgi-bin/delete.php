<?php
// delete.php
// This script deletes a file from the uploads directory.
// It expects a POST parameter named "filename".

// Define the uploads directory (relative to this script)
$uploadDir = __DIR__ . '/uploads/';

// Ensure the uploads directory exists
if (!is_dir($uploadDir)) {
    echo "error:uploads directory does not exist";
    exit(1);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['filename'])) {
    // Use basename() to prevent directory traversal
    $filename = basename($_POST['filename']);
    // Build the full file path
    $filePath = realpath($uploadDir . DIRECTORY_SEPARATOR . $filename);

    // Verify the file is within the uploads directory and that it exists
    if ($filePath && strpos($filePath, realpath($uploadDir)) === 0 && is_file($filePath)) {
        if (unlink($filePath)) {
            echo "ok";
            exit(0);
        } else {
            echo "error:failed to delete file";
            exit(1);
        }
    } else {
        echo "error:file not found";
        exit(1);
    }
} else {
    echo "error:invalid request";
    exit(1);
}
?>
