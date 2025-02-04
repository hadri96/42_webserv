<style>
table, tr, td {
	border: 1px solid #000;
	border-collapse: collapse;
}
</style>

<?php
if ($_SERVER['REQUEST_METHOD'] == 'POST')
{
	echo "<h1>Hi " . htmlspecialchars($_POST['firstname']) . " " . htmlspecialchars($_POST['lastname']) . "!</h1>";
	echo "<p>The request method is POST.</p>";
}
elseif ($_SERVER['REQUEST_METHOD'] == 'GET')
{
	echo "<h1>Hi " . htmlspecialchars($_GET['firstname']) . " " . htmlspecialchars($_GET['lastname']) . "!</h1>";
	echo "<p>The request method is GET.</p>";
} 
else 
{
	echo "<p>Unsupported request method.</p>";
}
?>
