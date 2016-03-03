pid=`cat ./server.pid | awk '{print $2}'`

if [ ! -n "${pid}" ]; then
  echo "no pid in server.pid found"
  exit 1
fi

ps mp $pid -o THREAD,tid
