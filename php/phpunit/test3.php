<?php

class CsvFileIterator implements Iterator
{
  protected $file;
  protected $key = 0;
  protected $current;

  public function __construct($file) {
    $this->file = fopen($file, 'r');
  }

  public function __destruct() {
    fclose($this->file);
  }

  public function rewind() {
    rewind($this->file);
    $this->current = $this->get();
    $this->key = 0;
  }

  public function valid() {
    return !feof($this->file);
  }

  public function key() {
    return $this->key;
  }
  
  public function current() {
    return $this->current;
  }

  public function next() {

    $this->current = $this->get();
    $this->key++;
  }

  private function isValidRow( $row ) {

    return ( is_array( $row ) && ( count( $row ) >= 1 ) && ( $row[0] !== null ) );
  }

  private function get() {
    $raw = fgetcsv($this->file);

    while ( ! $this->isValidRow( $raw ) && !feof( $this->file ) ) {
      $raw = fgetcsv($this->file);
    }

    $csv = array();

    if ( $this->isValidRow( $raw ) ) {
      foreach( $raw as $v ) {
        $v = preg_replace( '/\s+#.*$/', '', $v );
        $csv[] = $v;
      }
    }

    return $csv;
  }
}

class FileDataProviderTest extends PHPUnit_Framework_TestCase
{
  /**
  * @dataProvider provider
  */
  public function testAdd($a, $b, $c)
  {
    $this->assertEquals($c, $a + $b);
  }

  public function provider()
  {
    return new CsvFileIterator('data.csv');
  }
}
