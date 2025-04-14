<?php
$serverName = "tcp:stircatalin-sql.database.windows.net,1433";
$database = "laborator";
$username = "student";
$password = "REDACTED_PASSWORD";

try {
    $conn = new PDO("sqlsrv:server=$serverName;Database=$database", $username, $password);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
} catch (PDOException $e) {
    die("Error connecting to SQL Server: " . $e->getMessage());
}

if ($_SERVER['REQUEST_METHOD'] == 'POST' && isset($_FILES['fileToUpload'])) {
    require 'vendor/autoload.php'; // Include Azure SDK
    use MicrosoftAzure\Storage\Blob\BlobRestProxy;
    use MicrosoftAzure\Storage\Blob\Models\CreateBlockBlobOptions;

    $blobClient = BlobRestProxy::createBlobService("Your_Azure_Storage_Connection_String");
    $containerName = "your-container-name";

    $fileName = basename($_FILES["fileToUpload"]["name"]);
    $fileTmpPath = $_FILES["fileToUpload"]["tmp_name"];
    $fileText = $_POST['fileText'] ?? '';

    $content = fopen($fileTmpPath, "r");
    $blobClient->createBlockBlob($containerName, $fileName, $content);

    unlink($fileTmpPath);
    
    $blobUrl = "https://yourstorageaccount.blob.core.windows.net/$containerName/$fileName";
    
    $sql = "INSERT INTO fileinfo (filename, blob_store_addr, file_text) VALUES (?, ?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->execute([$fileName, $blobUrl, $fileText]);
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>File Upload</title>
</head>
<body>
    <form action="" method="post" enctype="multipart/form-data">
        <label>Select file to upload:</label>
        <input type="file" name="fileToUpload" required>
        <input type="text" name="fileText" placeholder="Enter file description">
        <input type="submit" value="Upload File">
    </form>
    <h2>Uploaded Files</h2>
    <ul>
        <?php
        $sql = "SELECT blob_store_addr, file_text FROM fileinfo ORDER BY id DESC";
        foreach ($conn->query($sql) as $row) {
            echo "<li><a href='{$row['blob_store_addr']}' target='_blank'>{$row['blob_store_addr']}</a> - {$row['file_text']}</li>";
        }
        ?>
    </ul>
</body>
</html>
