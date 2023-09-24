# Lab 2

Using docker to run elastic search, find a guide on the commands inside the Dockerfile [here](https://www.elastic.co/guide/en/elasticsearch/reference/7.17/deb.html) and another Dockerfile example [here](https://gist.github.com/rluvaton/3a8d5953e1ad8236e8953c2e7691e5de). 

Some commands:
* `docker build -t elastic_search .`, create image
* `docker run -p 9200:9200 elastic_search`, run elastic search