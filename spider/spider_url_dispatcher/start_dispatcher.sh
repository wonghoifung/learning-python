export LD_LIBRARY_PATH+="/usr/local/lib:/home/albert/env/boost/lib/:/home/albert/env/jsoncpp/libs/linux-gcc-4.4.7/:/home/albert/env/hiredis/lib/:/home/albert/env/protobuf/lib/:"

if [ "$1"x = "clr"x ]; then
	rm -f *.log
fi

nohup ./dispatcher &

