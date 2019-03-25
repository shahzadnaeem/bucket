#!/usr/bin/perl

# ==============================================================================

use strict;

use POSIX qw(strftime);
use Time::HiRes qw( gettimeofday );
use File::stat;

use File::Copy;
use DBI;
use DirHandle;

# ==============================================================================

# Needs some option parsing for db/host/user/pass/table

# ==============================================================================

sub db_connect
{
  my $dbname = shift;

  my $user     = "shahzad";
  my $password = "shahzad";

  my $dbh = DBI->connect( "dbi:mysql:$dbname:localhost", $user, $password );

  return $dbh;
}

# ==============================================================================

sub gen_checksum_query
{
  my ( $db, $tbl ) = @_;

  my $dbh = db_connect( $db );

  if ( defined $dbh )
  {
    my $ddl = ($dbh->selectrow_array("show create table $db.$tbl"))[1];

    my ( $type ) = $ddl =~ m/^\) (?:ENGINE|TYPE)=(\S+)/m;
    my $cols  = join( ', ', $ddl =~ m/^\s+(`[^`]+`)/gm ); #`;
    my $index = $ddl =~ m/PRIMARY KEY/ ? ' USE INDEX(PRIMARY)' : '';

    my $query = 'set @crc = \'\'; set @cnt = 0; SELECT MIN(LEAST(0, LENGTH(@crc := SHA1('
      . 'CONCAT_WS("#", @crc, SHA1(CONCAT_WS("#", ' . $cols . '))))),'
      . '@cnt := @cnt + 1)) AS len FROM ' . "`$db`.`$tbl` $index;";

    $dbh->disconnect();

    my $create = $ddl;

    return ( $create, $type, $query );
  }
  else
  {
    print "ERROR: DBI->connect() failed\n";
    exit(1);
  }
}

# ==============================================================================

my $db = "employees";
my $table = "employees";

my ( $ddl, $type, $query ) = gen_checksum_query( $db, $table );

print "$db.$table:\n$ddl\n\n";
print "type = $type\n";
print "query = \n$query\n";

# ==============================================================================
