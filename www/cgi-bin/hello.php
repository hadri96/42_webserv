<?php
// Tell the browser the content type is HTML
header('Content-Type: text/html');

// Retrieve query parameters
$name = getenv("NAME") ? htmlspecialchars(getenv("NAME")) : 'World';
$content = getenv("CONTENT") ? htmlspecialchars(getenv("CONTENT")) : 'This is a default message.';

// Generate the dynamic HTML output
echo "<!DOCTYPE html>";
echo "<html>";
echo "<head>";
echo "    <title>PHP CGI Example</title>";
echo "</head>";
echo "<body>";
echo "    <h1>Hello, $name!</h1>";
echo "    <p>$content</p>";
echo "</body>";
echo "</html>";

?>