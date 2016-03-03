/home/albert/thrift-0.8.0/compiler/cpp/thrift -r -gen cpp store.thrift
/home/albert/thrift-0.8.0/compiler/cpp/thrift -r -gen py store.thrift

cp gen-cpp/* ../spider_store_service/
rm -f ../spider_store_service/store_service_server.skeleton.cpp

cp -R gen-py ../spider_url_consumer/

rm -rf gen-cpp
rm -rf gen-py

