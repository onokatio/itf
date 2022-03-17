#!/usr/bin/ruby
# -*- coding: utf-8 -*-
# cgi-arg1arg2-ruby.cgi -- CGI プログラムに対する引数 arg1 と arg2 を表示するプログラム
# ~yas/syspro/www/cgi-arg1arg2-ruby.cgi

require "cgi"

def main()
	@cgi = CGI.new()
	print_header()
	print_content()
	exit( 0 )
end

def print_header()
	printf("Content-Type: text/html\n")
	printf("\n")
end

def print_content()
	printf("<HTML><HEAD></HEAD><BODY><PRE>\n")
	$stdout.flush()
	month = @cgi["month"]
	year = @cgi["year"]
        cal = %x(cal #{month} #{year})
    	printf("%s\n", cal)
	printf("</PRE></BODY></HTML>\n")
end

def e( str )
	return( str == nil ? "(null)" : CGI::escapeHTML(str) )
end

main()
