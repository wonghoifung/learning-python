protoc --cpp_out=../spider_url_dispatcher/pb/ *.proto

protoc --python_out=../spider_url_producer/pb/ produce*.proto
protoc --python_out=../spider_url_producer/pb/ pingpong*.proto

protoc --python_out=../spider_url_consumer/pb/ consume*.proto
protoc --python_out=../spider_url_consumer/pb/ pingpong*.proto
