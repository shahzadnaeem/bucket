<?php

require( "./base32.php" );

function join2nums( $num1, $num2 ) {

  return pack( "NN", $num1, $num2 );
}

function showNumHexAndDec( $numName, $num ) {

  echo "$numName = 0x" . dechex( $num ) . " == $num" . PHP_EOL;
}

function showValAndLen( $valName, $val ) {

  echo "$valName = $val (len=" . strlen( $val ) . ")" . PHP_EOL;

}

function show2numsjoin( $num1, $num2 ) {

  $bin2nums = join2nums( $num1, $num2 );
  $hex2nums = bin2hex( $bin2nums );
  $b32hex   = Base32::encodeByteStrToHex( $bin2nums, true );
  $dec2nums = hexdec( $hex2nums );

  showValAndLen( '$bin2nums', $bin2nums );
  showValAndLen( '$hex2nums', $hex2nums );
  showValAndLen( '$b32hex', $b32hex );
  showValAndLen( '$dec2nums', $dec2nums );

  $gmpNum = gmp_init( $hex2nums, 16 );
  $gmpStr = gmp_strval( $gmpNum, 10 );

  showValAndLen( '$gmpStr', $gmpStr );
  echo PHP_EOL;
}

show2numsjoin( 0x1, 0x0 );
show2numsjoin( 0x80000000, 0x0 );

$checkMaskBits  = 24;
$checkMask      = ( 0x1 << $checkMaskBits ) - 1;

$checkId    = 0x12987654;
$topBits    = ( $checkId & ( ~ $checkMask ) ) >> 24;
$bottomBits = ( $checkId & $checkMask );

showNumHexAndDec( '$checkId', $checkId );
showNumHexAndDec( '$topBits', $topBits );
showNumHexAndDec( '$bottomBits', $bottomBits );

$territory = 3;

$fixedTimestamp = 0x11111100;

$highNum = $fixedTimestamp | $topBits;
$lowNum  = ( $territory << 24 ) | $bottomBits;

show2numsjoin( $highNum, $lowNum );

