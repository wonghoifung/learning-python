/home/albert/thrift-0.8.0/compiler/cpp/thrift -r -gen cpp store.thrift

cp gen-cpp/* ../spider_store_service/
rm -f ../spider_store_service/store_service_server.skeleton.cpp

rm -rf gen-cpp
