#!/usr/bin/perl

my $url = $ARGV[0];
my $method = $ARGV[1];
my $filename = $ARGV[2];
my $file_path = $ARGV[3];
my $error_page = $ARGV[4];

if (open (FH, $file_path)) {
    while (<FH>) {
        print $_;
    }
    close;
} else {
    if (open (FH, $error_page)) {
        while (<FH>) {
            print $_;
        }
        close;
    } else {
        print "<h1>ERROR: Could not find the specified file</h1>";
    }
}
