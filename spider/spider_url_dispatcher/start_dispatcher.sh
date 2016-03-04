export LD_LIBRARY_PATH+="/usr/local/lib:../env/boost/lib/:../env/jsoncpp/libs/linux-gcc-4.4.7/:../env/hiredis/lib/:../env/protobuf/lib/:"

if [ "$1"x = "clr"x ]; then
	rm -f *.log
fi

nohup ./dispatcher &

