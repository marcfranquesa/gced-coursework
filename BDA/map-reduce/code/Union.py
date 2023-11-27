import Utils

# SELECT capital_gain FROM adult a1 WHERE native_country = "Italy"
# UNION
# SELECT capital_loss FROM adult a2 WHERE native_country = "Ecuador"


def map(k, v):
    row = [k] + v.split(",")
    if Utils.get(row, "native_country") == "Italy":
        return [(Utils.get(row, "capital_gain"), 0)]
    elif Utils.get(row, "native_country") == "Ecuador":
        return [(Utils.get(row, "capital_loss"), 0)]
    return []


def reduce(k, lv):
    return [k]
