dispatcher_pid=`cat ./server.pid | awk '{print $2}'`

if [ ! -n "${dispatcher_pid}" ]; then
  echo "no dispatcher found"
  exit 1
fi

kill -USR1 $dispatcher_pid
