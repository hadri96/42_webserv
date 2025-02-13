<?php
// Set unlimited execution time
set_time_limit(0);

// Infinite loop to test server
while (true) {
    // Log the current timestamp
    echo "Current Time: " . date("Y-m-d H:i:s") . "\n";
    
    // Flush the output buffer
    ob_flush();
    flush();
    
    // Sleep for 1 second to avoid overwhelming the server
    sleep(1);
}
?>
