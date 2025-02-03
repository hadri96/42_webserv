<?php
// upload.php
// This script handles file uploads to the uploads directory.
// It expects a POST request with an uploaded file in the "file" field.

$uploadDir = __DIR__ . '/uploads/';

// If the uploads directory does not exist, try to create it.
if (!is_dir($uploadDir)) {
    if (!mkdir($uploadDir, 0755, true)) {
        echo "error:failed to create uploads directory";
        exit(1);
    }
}

// Verify the uploads directory is writable.
if (!is_writable($uploadDir)) {
    echo "error:uploads directory is not writable";
    exit(1);
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['file'])) {
    // Use basename() for security.
    $filename = basename($_FILES['file']['name']);
    $targetPath = $uploadDir . DIRECTORY_SEPARATOR . $filename;
    
    if (move_uploaded_file($_FILES['file']['tmp_name'], $targetPath)) {
        echo "ok";
        exit(0);
    } else {
        echo "error:failed to upload file";
        exit(1);
    }
} else {
    echo "error:invalid upload request";
    exit(1);
}
?>
