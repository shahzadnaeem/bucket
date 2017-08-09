<?php

function expandToSQL( $sql, $inColumn, $inValues ) {

  $res = "";

  $res .= "$sql ";
  $res .= " where $inColumn in ( ";

  $sep="";

  foreach ( $inValues as $key => $value ) {
    $res .= "$sep?$inColumn-" . (++$key);

    $sep = ", ";
  }

  $res .= " );";

  return $res;
}

$ary = array( 1, 2, 3 );

print expandToSQL( "select * from customers", "customerid", $ary ) . PHP_EOL;

$ary["4 ); drop table students; --"] = "Johnny Tables";

print expandToSQL( "select * from customers", "customerid", $ary ) . PHP_EOL;


  