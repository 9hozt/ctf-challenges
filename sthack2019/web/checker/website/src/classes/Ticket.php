<?php

/**
 *
 * Class History
 * 
 * Log a scanned ticket in order to avoid duplicate tickets
 *
 *
 */
class History{ 

	public $filename;
	public $data;

	public function __construct(){
		$this->filename = "/history/".time()."_".rand().".png";
		$this->data = $data;
	}

	public function LogTicket(){

		system("qrencode $this->data -o $this->filename");
	}

}


/**
 *
 * Class Signature
 *
 * Sign and verify ticket data
 *
 */
class Signature{

	public $hash;
	public $data;
	protected $key;

	public function __construct($data, $sign,$key){

		$this->data = $data;
		$this->hash = $sign;
		$this->key = $key;
	}

	private function _sign(){
		return hash_hmac("gost",$this->data,$this->key);	
	}



	public function check(){
		$re_sign = $this->_sign();
		$re_sign === $this->hash ? $ret = true : $ret = false;
		return $ret;
	}

}

class Ticket{

	public $History;
	public $movie;
	public $room;

	public function __construct(){
	}


	public function displayInfo(){
		print "Welcome ! Your movie $this->movie will be displayed in room $this->room";
	}
		
	public function log(){
		$History = $this->History;
		$History->data = "{'date':'".time()."','data':'".$room."|".$moovie."'}";
		$History->LogTicket();

	}
}


