import Utils

# SELECT native_country, SUM(capital_gain) FROM adult GROUP BY native_country


def map(k, v):
    row = [k] + v.split(",")
    return [(Utils.get(row, "native_country"), int(Utils.get(row, "capital_gain")))]


def reduce(k, lv):
    return [(k, sum(lv))]
