<?php

interface FindableContract {
  public function find($id);
}

trait ContextDumper {
  public function dumpContext() {
    print "# DIR    = " . __DIR__ . "\n";
    print "# FILE   = " . __FILE__ . "\n";
    print "# NS     = " . __NAMESPACE__ . "\n";
    print "# TRAIT  = " . __TRAIT__ . "\n";
    print "# CLASS  = " . __CLASS__ . "\n";
    print "# METHOD = " . __METHOD__ . "\n";
    print "# FN     = " . __FUNCTION__ . "\n";
    print "# LINE   = " . __LINE__ . "\n";
  }
}

trait MagicFindableTrait {
  public function find($id) {
    print __CLASS__ . '::' . __FUNCTION__ . "\n";
    return static::__call(__FUNCTION__, func_get_args()); 
  }
}

class MagicalParent {
  public function __call($method, $args) {
    if ($method == 'find') {
      return "\nUser " . $args[0] . " is a witch! May we burn her?!\n\n";
    }
  }
}

class User extends MagicalParent implements FindableContract {
  use ContextDumper;
  use MagicFindableTrait;
}

class NonmagicalUser implements FindableContract {
  public function find($id) {
    return "\nUser $id was found to be nonmagical.  Let's burn him anyway.\n\n";
  }
}

$user = new User;
$nmUser = new NonmagicalUser;

print $user->find(123);
print $user->dumpContext();


print $nmUser->find(321);
