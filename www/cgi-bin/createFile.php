#!/usr/bin/php
<?php

$name = getenv('NAME') ?: 'default_name';
$content = getenv('CONTENT') ?: 'default_content';

$filename = "./" . $name . ".txt";

if (file_put_contents($filename, $content) === false) 
{
    echo "Failed to write to file '$filename'. Check permissions or path.\n";
    exit(1);
}

echo "File '$filename' created with content: $content\n";

?>
