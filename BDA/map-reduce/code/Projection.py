import Utils

# SELECT DISTINCT age, relationship, native_country FROM adult


def map(k, v):
    tupl = k + "," + v
    return [
        (
            Utils.get(tupl.split(","), "age")
            + ","
            + Utils.get(tupl.split(","), "relationship")
            + ","
            + Utils.get(tupl.split(","), "native_country"),
            1,
        )
    ]


def reduce(k, lv):
    return [k]
