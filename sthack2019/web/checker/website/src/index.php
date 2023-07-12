<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600,700' rel='stylesheet' type='text/css'>
    <link rel="stylesheet" type="text/css" href="Font-Awesome-4.7/css/font-awesome.min.css">
    <link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
    <link rel="stylesheet" type="text/css" href="css/templatemo-style.css">
     <script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.3.1/jquery.min.js"></script>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/webcamjs/1.0.25/webcam.min.js"></script>


    
    <title>Automated ticket checker</title>
</head>

<body>
    
    <div class="container">

       <section class="col-md-12 content padding tm-equal-col-container" id="home">
        <div class="col-lg-6 col-md-6 col-sm-12 content-item tm-black-translucent-bg tm-services-section-padding">
          <h2 class="main-title text-center dark-blue-text">Cinéma - Le Français</h2>
           <p>Bienvenue au cinéma Le Français. Veuillez scanner votre ticket pour accèder à la salle.</p>
           <!-- <button type="button" class="btn btn-big pull-right tm-btn-primary">Read More</button> -->
       </div>
        <div class="col-lg-6 col-md-6 col-sm-12 content-item tm-black-translucent-bg tm-services-section-padding">
	<h2 class="main-title text-center dark-blue-text">Scan your ticket !
          </h2>
            <form method="POST" action="check.php" id="formscan">
        <div class="row">
            <div class="col-md-6">
                <div id="my_camera"></div>
                <br/>
                <button type="button" class="btn btn-big pull-right tm-btn-primary" onclick=take_snapshot()>Scan</button>
                <input type="hidden" name="image" class="image-tag">
            </div>

        </div>
    </form>

       </div>

      </section>

     
   
</div>

<div class="text-center footer">
	<div class="container">
		Copyleft &copy; Sthack 2019

    </div>
</div>
<script language="JavaScript">
    Webcam.set({
        width: 490,
        height: 390,
        image_format: 'jpeg',
        jpeg_quality: 90
    });

    Webcam.attach( '#my_camera' );

    function take_snapshot() {
        Webcam.snap( function(data_uri) {
            $(".image-tag").val(data_uri);
            document.getElementById('formscan').submit();
        } );
    }
</script>


</body>
</html>
