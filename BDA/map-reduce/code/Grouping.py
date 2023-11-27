import Utils

# SELECT native_country, list(capital_gain) FROM adult GROUP BY native_country


def map(k, v):
    row = [k] + v.split(",")
    return [(Utils.get(row, "native_country"), Utils.get(row, "capital_gain"))]


def reduce(k, lv):
    return [(k, list(lv))]
