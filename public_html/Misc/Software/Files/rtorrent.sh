#!/bin/sh

case "$1" in
  start)
        echo -n "Starting rtorrent"
        su - root -c "screen -A -m -d -S rtorrent /usr/local/bin/rtorrent" &
        echo "."
        ;;
  stop)
        echo -n "Stopping rtorrent"
        ppid=`ps ax | grep "/usr/local/bin/rtorrent" | grep -v grep | grep -v screen | awk '{ print $1 }'`
        kill ${ppid}
        echo "."
        ;;
  restart)

        echo -n "Restarting rtorrent"
        ppid=`ps ax | grep "/usr/local/bin/rtorrent" | grep -v grep | grep -v screen | awk '{ print $1 }'`
        kill ${ppid}
        sleep 1
        su - root -c "screen -A -m -d -S rtorrent /usr/local/bin/rtorrent" &
        echo "."
        ;;
  *)
        echo "Usage: {start|stop|restart}" >&2
        exit 1
        ;;
esac

exit 0