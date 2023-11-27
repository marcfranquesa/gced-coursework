import Utils

# SELECT * FROM adult WHERE workclass = "Private"


def map(k, v):
    row = [k] + v.split(",")
    if Utils.get(row, "workclass") == "Private":
        return [(k, v)]
    return []


def reduce(k, lv):
    return [(k, list(lv)[0])]
