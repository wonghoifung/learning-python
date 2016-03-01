git rm -f ../spider_url_dispatcher/pb/*
git rm -f ../spider_url_producer/pb/*
git rm -f ../spider_url_consumer/pb/*

mkdir ../spider_url_dispatcher/pb
mkdir ../spider_url_producer/pb
mkdir ../spider_url_consumer/pb

/home/albert/env/protobuf/bin/protoc --cpp_out=../spider_url_dispatcher/pb/ *.proto

/home/albert/env/protobuf/bin/protoc --python_out=../spider_url_producer/pb/ produce*.proto
/home/albert/env/protobuf/bin/protoc --python_out=../spider_url_producer/pb/ pingpong*.proto

/home/albert/env/protobuf/bin/protoc --python_out=../spider_url_consumer/pb/ consume*.proto
/home/albert/env/protobuf/bin/protoc --python_out=../spider_url_consumer/pb/ pingpong*.proto

git add ../spider_url_dispatcher/pb/*
git add ../spider_url_producer/pb/*
git add ../spider_url_consumer/pb/*
