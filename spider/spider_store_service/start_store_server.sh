export LD_LIBRARY_PATH+="/usr/local/lib:/home/albert/env/boost/lib/:/home/albert/env/mysqlpp/lib/:/home/albert/env/mysqlconnector/lib/:/home/albert/env/libevent/lib/:/home/albert/env/thrift/lib/:/home/albert/env/jsoncpp/libs/linux-gcc-4.4.7/:"

if [ "$1"x = "clr"x ]; then
	rm -f *.log
fi

nohup ./store_server &

