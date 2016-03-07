
if [ "$1"x = "clr"x ]; then
	rm -f *.log
fi

nohup python ./producer.py &

