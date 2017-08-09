<?php

$shortOpts = "";
$longOpts = array( 'from::', 'to::' );

$from = 3;
$to   = 1000;

$options = getopt( $shortOpts, $longOpts );
                   
if ( $options !== false ) {

  $from = isset( $options['from'] ) ? $options['from'] : $from;
  $to   = isset( $options['to'] ) ? $options['to'] : $to;

  print "Looking for Charmichael numbers in: $from .. $to" . PHP_EOL;

  for ( $num = $from; $num <= $to; $num ++ ) {

    if ( isCharmichaelNum( $num ) ) {
      print "$num is a Charmichael number" . PHP_EOL;
    }
  }
} else {
  die( "Bad options!" );
}

function isCharmichaelNum( $num ) {

  if ( gmp_prob_prime( $num ) != 0 ) return false;

  $n = $num;

  for ( $b = 2; $b < $num; $b ++ ) {

    $exp = gmp_pow( $b, $n );
    $mod = gmp_mod( $exp, $n );

    if ( $mod != $b ) return false;
  }

  return true;
}