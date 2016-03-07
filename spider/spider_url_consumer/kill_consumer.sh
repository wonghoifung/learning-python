

pid=`cat ./server.pid | awk '{print $2}'`

if [ ! -n "${pid}" ]; then
  echo "no consumer found"
  exit 1
fi

kill -9 $pid
