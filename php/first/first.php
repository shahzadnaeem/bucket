#!/usr/bin/php
<?php
interface IGreet {

  function hello( $who );

}

class Greeter implements IGreet {

  function hello( $who ) { return "Hello '" . $who . "', how are you?"; }

}

$g = new Greeter;

echo $g->hello( "Sailor" ) . "\n";
