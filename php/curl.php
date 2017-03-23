<?php
$value = $_POST['value'];
$from = $_POST['from'];
$ip = $_SERVER['REMOTE_ADDR'];
echo "Your value = ".$value." from = ".$from." And your ip address is ".$ip."\n";
$today=date("Y-m-d H:i:s");
$file="curltest.log";	//the log file name
if(file_exists($file)){
	$fp=fopen($file, "a");	//open file in the appending mode
}
else{
	$fp=fopen($file, "w");	//open file in the writtng mode
}
$record=$today . "," . $from . "," . $ip . "," . $value . "\n";
fwrite($fp, $record);
fclose($fp);
?>