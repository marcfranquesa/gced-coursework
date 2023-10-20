from elasticsearch import Elasticsearch
from pprint import pprint

client = Elasticsearch("http://localhost:9200", request_timeout=1000)

index = 'scrapy'
info = client.cat.count(index=index, format = "json")[0]
print(f"Index: {index} with {info['count']} documents.")