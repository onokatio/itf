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
	arg1 = @cgi["arg1"]
	arg2 = @cgi["arg2"]
        sum = arg1.to_i() + arg2.to_i()
    	printf("arg1: [%s]\n", e(arg1))
    	printf("arg2: [%s]\n", e(arg2))
    	printf("sum: [%d]\n", sum)
	printf("</PRE></BODY></HTML>\n")
end

def e( str )
	return( str == nil ? "(null)" : CGI::escapeHTML(str) )
end

main()
