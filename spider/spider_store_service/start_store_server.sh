export LD_LIBRARY_PATH+="/usr/local/lib:../env/boost/lib/:../env/mysqlpp/lib/:../env/mysqlconnector/lib/:../env/libevent/lib/:../env/thrift/lib/:../env/jsoncpp/libs/linux-gcc-4.4.7/:"

if [ "$1"x = "clr"x ]; then
	rm -f *.log
fi

nohup ./store_server &

