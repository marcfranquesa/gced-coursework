import Utils

# Difference based on one attribute
# SELECT age FROM adult a1 WHERE native_country = "Italy"
# EXCEPT
# SELECT age FROM adult a2 WHERE native_country = "Ecuador"


def map(k, v):
    row = [k] + v.split(",")
    if Utils.get(row, "native_country") == "Italy":
        return [(Utils.get(row, "age"), "Italy")]
    if Utils.get(row, "native_country") == "Ecuador":
        return [(Utils.get(row, "age"), "Ecuador")]
    return []


def reduce(k, lv):
    if "Ecuador" not in lv:
        return [k]
    return []
