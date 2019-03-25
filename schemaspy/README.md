# Schemaspy

## URLs

- http://schemaspy.org/ Schemaspy 6.0.0
- https://downloads.mariadb.org/connector-java/2.4.1/ MariaDB Connector


### Running

$ java -jar bin/schemaspy-6.0.0.jar -host localhost -port 3306 -db wikidb -s wikidb -o output/wikidb -t mariadb -dp bin -u wikiuser -p <PASSWORD> -debug

\# output/wikidb/index.html

#### Notes

-s is schema (same as -db for MySQL and variants)

--help gives what you'd expect :)

$ java -jar bin/schemaspy-6.0.0.jar --help

```
INFO  - Starting Main v6.0.0 on fastbox.localdomain with PID 13335 (/home/shahzad/projects/bucket/schemaspy/bin/schemaspy-6.0.0.jar started by shahzad in /home/shahzad/projects/bucket/schemaspy)
INFO  - The following profiles are active: default
INFO  - Started Main in 1.059 seconds (JVM running for 1.443)
INFO  - Usage: java -jar /home/shahzad/projects/bucket/schemaspy/bin/schemaspy-6.0.0.jar [options]
  Options:
    ?, -?, /?, -h, help, -help, --help
      show general usage and available options
    -dbHelp, -dbhelp, --dbHelp, --dbhelp
      Show built-in database types and their required connection parameters
    -l, --license
      Print license, it will first print GPL and then LGPL (LGPL is addition to GPL)
    -cat, --catalog, catalog, schemaspy.cat, schemaspy.catalog
      catalog
    -db, -database-name, schemaspy.db, schemaspy.database-name
      Name of database to connect to
    -t, --database-type, database-type, schemaspy.t, schemaspy.database-type
      type of database
      Default: ora
    -debug, --debug, debug, schemaspy.debug
      Enable debug logging
      Default: false
    -dp, --driverPath, driverPath, schemaspy.dp, schemaspy.driverPath
      path to look for JDBC drivers overrides driverPath in [databaseType].properties, supports directory, will add 
      directory and recurse to add all content. Supports multiple paths using os dependent pathSeparator.
    -o, --outputDirectory, outputDirectory, schemaspy.o, schemaspy.outputDirectory
      directory to place the generated output in
    -port, --port, port, schemaspy.port

    -s, --schema, schema, schemaspy.s, schemaspy.schema
      name of the schema to analyze (defaults to the specified user)
    -sso, --single-sign-on, schemaspy.sso, schemaspy.single-sign-on
      Remove requirement for user
      Default: false
    -u, --user, user, schemaspy.u, schemaspy.user
      connect to the database with this user id

Go to http://schemaspy.org for a complete list/description of additional parameters.
```