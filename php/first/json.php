<?php

$json = '{ "a": [1,2,"3","four"], "bee": { "name": "Shaz" } }';

echo "json_decode( \$j )" . PHP_EOL;
$dj = json_decode( $json );
print_r( $dj ) . PHP_EOL;

echo "\$dj->bee" . PHP_EOL;
print_r( $dj->bee ) . PHP_EOL;

echo "json_decode( \$j, true )" . PHP_EOL;
$dj = json_decode( $json, true );
print_r( $dj ) . PHP_EOL;

echo "\$dj['bee']" . PHP_EOL;
print_r( $dj['bee'] ) . PHP_EOL;
