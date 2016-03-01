
# pid=`lsof -i:8080|awk '{print $2}'|awk 'NR==2'`

# if [ ! -n "${pid}" ]; then
#   echo "no dispatcher:8080 found"
#   exit 1
# fi

# kill -9 ${pid}

dispatcher_pid=`cat ./server.pid | awk '{print $2}'`

if [ ! -n "${dispatcher_pid}" ]; then
  echo "no dispatcher found"
  exit 1
fi

kill -9 $dispatcher_pid
