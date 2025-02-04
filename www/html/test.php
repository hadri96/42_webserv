<?php
// Display the current date and time
echo "<h1>PHP Test Page</h1>";
echo "<p>Current Date and Time: " . date("Y-m-d H:i:s") . "</p>";

// Display server information
echo "<h2>Server Information</h2>";
echo "<pre>";
print_r($_SERVER);
echo "</pre>";

// Display PHP information (useful for debugging PHP settings)
echo "<h2>PHP Info</h2>";
phpinfo();
?>
