<!DOCTYPE html>
<html>
<head>
  <title>Upload your files</title>
</head>
<body>
  <form enctype="multipart/form-data" action="parser.php" method="POST">
    <p>Upload your file</p>
    <input type="file" name="uploaded_file"></input><br />
    <input type="submit" value="Upload"></input>
  </form>
</body>
</html>
<?php		

function generateRandomString($length = 10) {
    return substr(str_shuffle(str_repeat($x='0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ', ceil($length/strlen($x)) )),1,$length);
}

  if(!empty($_FILES['uploaded_file']))
  {
    $path = "/var/www/dev/uploads/";
    $path = $path . generateRandomString(32);

    if(move_uploaded_file($_FILES['uploaded_file']['tmp_name'], $path)) {
      echo "The file has been uploaded... <br />Analyzing ....<br />";
      echo "Result : <br />";

      system("/var/www/dev/png_analyzer $path");

      unlink($path);
     
    } else{
        echo "There was an error uploading the file, please try again!";
    }
  }
?>
