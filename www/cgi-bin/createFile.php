#!/usr/bin/php

<?php

// Output the correct Content-Type header
header('Content-Type: text/plain');

// Extract 'name' and 'message' from the POST data
$name = $_POST['name'] ?? '';
$message = $_POST['message'] ?? '';

$name = $_GET['name'] ?? '';
$message = $_GET['message'] ?? '';

// Pass the inputs to the C++ application
$cppOutput = shell_exec("/path/to/your_cpp_application " . escapeshellarg($name) . " " . escapeshellarg($message));

// Output the result from the C++ application
echo $cppOutput;
?>
