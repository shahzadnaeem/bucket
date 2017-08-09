<?php

//
// Tried with PHP 7
//
//    64bit server, 4GB memory limit
//
//    $ php mem1.php 1000 100 0 1
// PHP version 7.0.21
// Memory limit 4096M
//
// Items     = 1000
// Size      = 100
// Self Ref  = false
// GC Cycles = true
//
// Size of MemClass ( 0.10MB x 1000 ) = 8.32MB
// GC Memory decreased by 4134.59MB from 4142.91MB to 8.32MB
// GC Memory decreased by 4142.88MB from 4151.20MB to 8.32MB
// Initial Memory     = 0.38MB
// Max Memory Used    = 4151.20MB
// Min Memory Used    = 4142.91MB
// Mem Decrease Count = 0
//
//    $ php mem1.php 1000 100 0
// 
// PHP version 7.0.21
// Memory limit 4096M
// 
// Items     = 1000
// Size      = 100
// Self Ref  = false
// GC Cycles = false
// 
// Size of MemClass ( 0.10MB x 1000 ) = 8.32MB
// PHP Fatal error:  Allowed memory size of 4294967296 bytes exhausted (tried to allocate 8192 bytes) in /home/shahzad/php/memory/mem1.php on line 24
// PHP Stack trace:
// PHP   1. {main}() /home/shahzad/php/memory/mem1.php:0
// PHP   2. MemClass->__construct() /home/shahzad/php/memory/mem1.php:75
// PHP   3. range() /home/shahzad/php/memory/mem1.php:24

class MemClass {

  private $items;

  public function __construct( $numItems, $eachSize, $selfReference = false ) {

    //$this->items = array();

    //foreach ( range( 1, $numItems ) as $i ) {
    //  $this->items[ $i ] = str_repeat( "x-", $eachSize / 2 );
    //}

    $this->items = range( 1, $numItems );

    foreach ( $this->items as $i ) {
      $this->items[ $i ] = range( 1, $eachSize );
    }

    if ( $selfReference ) {
      $this->self = array( 'this' => $this );
      $this->that = &$this->self;
    }
  }
}

function formatMemory( $size ) {
  return sprintf( "%3.2fMB", $size / 1000000 );
}

$numItems = 100;
$itemSize = 100;
$selfRef  = false;
$gcCycles = false;

if ( $argc > 1 ) {
  $numItems = $argv[1];
}

if ( $argc > 2 ) {
  $itemSize = $argv[2];
}

if ( $argc > 3 ) {
  $selfRef = $argv[3];
}

if ( $argc > 4 ) {
  $gcCycles = $argv[4];
}

echo PHP_EOL . "PHP version " . phpversion() . PHP_EOL;
echo "Memory limit " . ini_get( 'memory_limit' ) . PHP_EOL . PHP_EOL;

echo "Items     = $numItems" . PHP_EOL;
echo "Size      = $itemSize" . PHP_EOL;
echo "Self Ref  = " . ( $selfRef ? "true" : "false" ) . PHP_EOL;
echo "GC Cycles = " . ( $gcCycles ? "true" : "false" ) . PHP_EOL;

$initialMemory     = memory_get_usage();
$memUsed           = 0;
$minMemUsed        = 1000000000000;
$maxMemUsed        = 0;
$memDecreasedCount = 0;

foreach( range( 1, $numItems ) as $i ) {

  $o = new MemClass( $numItems, $itemSize, true );

  if ( $i == 1 ) {
    $oneItemSize = memory_get_usage();

    echo PHP_EOL . "Size of MemClass ( " . formatMemory( $numItems * $itemSize ) . " x $numItems ) = " . formatMemory( $oneItemSize - $initialMemory ) . PHP_EOL;
  }

  if ( $i % 500 === 0 ) {

    //xdebug_debug_zval( 'o' );

    $newMemUsed = memory_get_usage() - $initialMemory;

    if ( $gcCycles ) {
      gc_collect_cycles();

      $postGCMemUsed = memory_get_usage() - $initialMemory;

      if ( $postGCMemUsed < $newMemUsed ) {
        echo "GC Memory decreased by " . formatMemory( $newMemUsed - $postGCMemUsed ) . " from " . formatMemory( $newMemUsed ) . " to " . formatMemory( $postGCMemUsed ) . PHP_EOL;
      }
    }

    if ( $newMemUsed < $memUsed ) {
      $memDecreasedCount ++;
      echo "Memory decreased by " . formatMemory( $memUsed - $newMemUsed ) . " from " . formatMemory( $memUsed ) . " to " . formatMemory( $newMemUsed ) . PHP_EOL;
    }

    if ( $newMemUsed > $maxMemUsed ) {
      $maxMemUsed = $newMemUsed;
    }

    $memUsed = $newMemUsed;

    if ( $memUsed < $minMemUsed ) {
      $minMemUsed = $memUsed;
    }
  }
}

echo "Initial Memory     = " . formatMemory( $initialMemory ) . PHP_EOL;
echo "Max Memory Used    = " . formatMemory( $maxMemUsed ) . PHP_EOL;
echo "Min Memory Used    = " . formatMemory( $minMemUsed ) . PHP_EOL;
echo "Mem Decrease Count = $memDecreasedCount" . PHP_EOL;
