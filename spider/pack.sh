#!/bin/bash

if [ $# != 1 ]; then
	echo "usage: ./pack.sh [version]"
	exit 1
fi

version=$1
bin="./spider"
System="CentOS"
datetag=`date '+%m%d%H%M'`
rm -fr $bin.$System.*.tar.gz
echo ${datetag}
packet="${bin}.${System}.${datetag}.${version}.tar.gz"

################ lib
boost_lib=`echo ./env/boost/lib/*`
hiredis_lib=`echo ./env/hiredis/lib/*`
jsoncpp_lib=`echo ./env/jsoncpp/libs/linux-gcc-4.4.7/*`
mysqlconnector_lib=`echo ./env/mysqlconnector/lib/*`
mysqlpp_lib=`echo ./env/mysqlpp/lib/*`
libevent_lib=`echo ./env/libevent/lib/*`
protobuf_lib=`echo ./env/protobuf/lib/*`
thrift_lib=`echo ./env/thrift/lib/*`

echo "ln -s libmysql.so.16 libmysqlclient.so.16" > README

################ bin
dispatcher="./spider_url_dispatcher/dispatcher"
dispatcher_script=`echo ./spider_url_dispatcher/*.sh`
dispatcher_md5=${dispatcher}'.md5'
md5sum -b ${dispatcher} > ${dispatcher_md5}

store_server="./spider_store_service/store_server"
store_server_script=`echo ./spider_store_service/*.sh`
store_server_md5=${store_server}'.md5'
md5sum -b ${store_server} > ${store_server_md5}

producer_script=`echo ./spider_url_producer/*`
producer_shell_script=`echo ./spider_url_producer/*.sh`

consumer_script=`echo ./spider_url_consumer/*`
consumer_shell_script=`echo ./spider_url_consumer/*.sh`

################ cfg
cfgfile="./config/config.xml"

tar -czf ${packet} ${boost_lib} ${hiredis_lib} ${jsoncpp_lib} \
${mysqlconnector_lib} ${mysqlpp_lib} ${libevent_lib} ${protobuf_lib} \
${thrift_lib} README \
${dispatcher} ${dispatcher_script} ${dispatcher_md5} \
${store_server} ${store_server_script} ${store_server_md5} \
${producer_script} ${consumer_script} \
${producer_shell_script} ${consumer_shell_script} \
${cfgfile}

rm -rf README
rm -rf ${dispatcher_md5} 
rm -rf ${store_server_md5}
