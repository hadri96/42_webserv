<style>
table, tr, td {
    border: 1px solid #000;
    border-collapse: collapse;
}
</style>

<h1>Hello <?= htmlspecialchars($_GET['firstname']) ?> <?= htmlspecialchars($_GET['lastname']) ?>!</h1>

<table>

<tr><td>$_SERVER['QUERY_STRING']</td><td><?= htmlspecialchars($_SERVER['QUERY_STRING']) ?></td></tr>
<tr><td>$_GET['firstname'] </td><td><?= htmlspecialchars($_GET['firstname']) ?></td></tr>
<tr><td>$_GET['lastname'] </td><td><?= htmlspecialchars($_GET['lastname']) ?></td></tr>

</table>