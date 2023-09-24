FROM ubuntu:bionic-20220531

# Must be root to install the packages
USER root

# Install required deps
RUN apt update
RUN apt -y install wget gpg apt-transport-https

# Import Elasticsearch GPG Key
RUN wget -qO - https://artifacts.elastic.co/GPG-KEY-elasticsearch | gpg --dearmor -o /usr/share/keyrings/elasticsearch-keyring.gpg

# Add Elasticsearch 7.x APT repository
RUN echo "deb [signed-by=/usr/share/keyrings/elasticsearch-keyring.gpg] https://artifacts.elastic.co/packages/7.x/apt stable main" | tee /etc/apt/sources.list.d/elastic-7.x.list

# update after elastic-search repo added
RUN apt-get update

# Install Elasticsearch 7.x
RUN apt-get -y install elasticsearch

# the user was created when installed the elasticsearch
# Must not be root:
# org.elasticsearch.bootstrap.StartupException: java.lang.RuntimeException: can not run elasticsearch as root
USER elasticsearch

WORKDIR /usr/share/elasticsearch

# Append the custom conf
RUN echo "network.host: 0.0.0.0" >> /etc/elasticsearch/elasticsearch.yml
RUN echo "discovery.type: single-node" >> /etc/elasticsearch/elasticsearch.yml
RUN echo "action.auto_create_index: true" >> /etc/elasticsearch/elasticsearch.yml

EXPOSE 9200

ENTRYPOINT [ "./bin/elasticsearch" ]