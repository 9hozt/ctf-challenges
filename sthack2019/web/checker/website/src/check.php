<?php

require __DIR__ . "/vendor/autoload.php";
require_once("incs/db.php");
require_once("incs/errno.php");
require_once("classes/Ticket.php");

error_reporting(0);
if(isset($_POST['image']) && !empty($_POST['image'])){

	$image = $_POST['image'];
	$split = explode(',',$image);
	$ZbarDecoder = new RobbieP\ZbarQrdecoder\ZbarDecoder();
	$stream = $split[1];
	$tmp = tmpfile();
	fwrite($tmp,base64_decode($stream));
	try{
		$result = $ZbarDecoder->make(stream_get_meta_data($tmp)['uri']);
	}
	catch(Exception $e)
	{
		print_r($e);
	}

	$raw_data = json_decode($result);

	if(!is_object($raw_data)){
		die($errors[1]);
	}



	if(!property_exists($raw_data,"uid")){
		die($errors[2]);
	}

	$stmt = $bdd->query("SELECT * FROM POS WHERE POS_id = $raw_data->uid");

	if(!$stmt){
		die($errors[3]);
	}

	$POS = $stmt->fetch();

	// TODO : Send POS data through API for stats.
	//
	print "<!-- Ticket sold by POS s/n ".$POS['serial_number']." in ".$POS['location']." -->\n";	
	

	if(!property_exists($raw_data,"t_id") || !property_exists($raw_data,"object") || !property_exists($raw_data,"sign")){
		die($errors[4]);
	}

	$key = $bdd->query("SELECT cipher_key FROM cipher_keys LIMIT 1")->fetchColumn();

	$Signature = new Signature($raw_data->object, $raw_data->sign,$key);
	if(!$Signature->check()){
		die($errors[5]);
	}
	
	$Ticket = unserialize(base64_decode($raw_data->object));
	$Ticket->displayInfo();
	$Ticket->log();

}

else{
 die("No post data");
}



