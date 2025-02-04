<?php
// Define the target directory for file uploads
$target_dir = "uploads/";

// Check if the directory exists, if not, create it
if (!file_exists($target_dir)) {
    mkdir($target_dir, 0777, true);
}

// Initialize variables
$uploadOk = 1;
$fileName = "";
$fileTmpName = "";
$fileType = "";

// Define the error log file
$error_log = 'upload_errors.log';

// Log function to write errors to the log file
function log_error($message) {
    global $error_log;
    $error_message = date('Y-m-d H:i:s') . " - ERROR: " . $message . "\n";
    file_put_contents($error_log, $error_message, FILE_APPEND);
}

// Check if the form is submitted
if ($_SERVER['REQUEST_METHOD'] == 'POST') {

    // Check if file was uploaded without errors
    if (!isset($_FILES['fileToUpload']) || $_FILES['fileToUpload']['error'] !== UPLOAD_ERR_OK) {
        $errorMsg = "File upload error: ";
        if (isset($_FILES['fileToUpload'])) {
            $errorCodes = array(
                UPLOAD_ERR_INI_SIZE => "File exceeds server's upload_max_filesize.",
                UPLOAD_ERR_FORM_SIZE => "File exceeds form's MAX_FILE_SIZE.",
                UPLOAD_ERR_PARTIAL => "File was only partially uploaded.",
                UPLOAD_ERR_NO_FILE => "No file was uploaded.",
                UPLOAD_ERR_NO_TMP_DIR => "Missing temporary directory.",
                UPLOAD_ERR_CANT_WRITE => "Failed to write file to disk.",
                UPLOAD_ERR_EXTENSION => "A PHP extension stopped the file upload."
            );
            $errorCode = $_FILES['fileToUpload']['error'];
            $errorMsg .= isset($errorCodes[$errorCode]) ? $errorCodes[$errorCode] : "Unknown error code: $errorCode";
        } else {
            $errorMsg .= "No file uploaded or form not submitted correctly.";
        }
        echo $errorMsg;
        log_error($errorMsg);
        exit;
    }

    // Get file info
    $fileName = basename($_FILES["fileToUpload"]["name"]);
    $fileTmpName = $_FILES["fileToUpload"]["tmp_name"];
    $fileType = strtolower(pathinfo($fileName, PATHINFO_EXTENSION));

    // Check if file already exists
    if (file_exists($target_dir . $fileName)) {
        echo "Sorry, file already exists.";
        log_error("File already exists: " . $fileName);
        $uploadOk = 0;
    }

    // Check file size (limit: 5MB)
    if ($_FILES["fileToUpload"]["size"] > 5000000) {
        echo "Sorry, your file is too large. Max file size is 5MB.";
        log_error("File too large: " . $fileName);
        $uploadOk = 0;
    }

    // Allow certain file formats
    $allowedTypes = array("jpg", "jpeg", "png", "gif", "pdf", "txt", "docx");
    if (!in_array($fileType, $allowedTypes)) {
        echo "Sorry, only JPG, JPEG, PNG, GIF, PDF, TXT, and DOCX files are allowed.";
        log_error("Invalid file type: " . $fileType . " for file: " . $fileName);
        $uploadOk = 0;
    }

    // Check if $uploadOk is set to 0 by an error
    if ($uploadOk == 0) {
        echo "Sorry, your file was not uploaded.";
        log_error("Upload failed for file: " . $fileName);
    } else {
        if (move_uploaded_file($fileTmpName, $target_dir . $fileName)) {
            echo "The file " . htmlspecialchars($fileName) . " has been uploaded successfully.";
        } else {
            $errorDetails = "Error moving file: $fileName. Temporary file: $fileTmpName. Target directory: " . realpath($target_dir);
            log_error($errorDetails);
            echo "Sorry, there was an error uploading your file. Please check permissions.";
        }
    }
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>File Upload</title>
</head>
<body>
    <h2>Upload a file</h2>
    <form action="upload.php" method="post" enctype="multipart/form-data">
        <label for="fileToUpload">Choose a file to upload:</label>
        <input type="file" name="fileToUpload" id="fileToUpload" required>
        <br><br>
        <button type="submit">Upload File</button>
    </form>
</body>
</html>