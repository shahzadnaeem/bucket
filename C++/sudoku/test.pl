#!/usr/bin/perl

# ==============================================================================

use strict;
use warnings;

# ==============================================================================

my $solver = "./main";

# ==============================================================================

my $file = shift;

if ( ! defined( $file ) )
{
  die "No input test file supplied!";
}

if ( -r $file )
{
  if ( open( FH, "<$file" ) )
  {
    my @lines = <FH>;
    close( FH );

    my $tests    = 0;
    my $passes   = 0;
    my $failures = 0;

    foreach my $line ( @lines )
    {
      chomp( $line );

      $line =~ s/\./0/g;

      my $puzzle = join( ',', split( '', $line ) );

      $tests ++;

      my $result = qx/$solver $puzzle/;

      my $status = $? >> 8;

      if ( $status == 0 )
      {
        $passes ++;
      }
      else
      {
        $failures ++;
      }

      print $result . "\n";
    }

    print "TESTS = $tests, PASSES = $passes, FAILURES = $failures\n";

    if ( $failures > 1 )
    {
      $failures = 1;
    }

    exit( $failures );
  }
  else
  {
    die "Can't open '$file'";
  }
}
else
{
  die "Can't find '$file'";
}

# ==============================================================================
