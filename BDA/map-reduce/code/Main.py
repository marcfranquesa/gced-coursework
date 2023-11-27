import os
import sys

import Aggregation
import CrossProduct
import Difference
import Grouping
import Intersection
import Join
import Projection
import pyspark
import Selection
import Union
from pyspark import SparkConf
from pyspark.sql import SparkSession

# Path to the resources folder of the project, use the full path on Windows
HADOOP_HOME = "./resources/hadoop_home"
# Use the full path on Windows for PYSPARK_PYTHON and PYSPARK_DRIVER_PYTHON, for instance: r"C:\SOFT\Python3\python.exe"
PYSPARK_PYTHON = "python3"
PYSPARK_DRIVER_PYTHON = "python3"

if __name__ == "__main__":
    os.environ["HADOOP_HOME"] = HADOOP_HOME
    sys.path.append(HADOOP_HOME + "/bin")
    os.environ["PYSPARK_PYTHON"] = PYSPARK_PYTHON
    os.environ["PYSPARK_DRIVER_PYTHON"] = PYSPARK_DRIVER_PYTHON

    conf = SparkConf()  # create the configuration

    spark = (
        SparkSession.builder.config(conf=conf)
        .master("local")
        .appName("MapReduce")
        .getOrCreate()
    )

    sc = pyspark.SparkContext.getOrCreate()

    mr = None
    if sys.argv[1] == "Selection":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Selection.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Selection.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Projection":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Projection.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Projection.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "CrossProduct":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: CrossProduct.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: CrossProduct.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Grouping":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Grouping.map(t[0], t[1]))
            .groupByKey()
            .map(lambda t: Grouping.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Aggregation":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Aggregation.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Aggregation.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Union":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Union.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Union.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Intersection":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Intersection.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Intersection.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Difference":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Difference.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Difference.reduce(t[0], t[1]))
        )
    elif sys.argv[1] == "Join":
        mr = (
            sc.sequenceFile("resources/adult.1000.sf")
            .flatMap(lambda t: Join.map(t[0], t[1]))
            .groupByKey()
            .flatMap(lambda t: Join.reduce(t[0], t[1]))
        )

    for x in mr.collect():
        print(x)
