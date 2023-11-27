import random

import Utils

# SELECT external.*, internal.*
# FROM adult as internal, adult as external
# WHERE external.native_country = "Italy" AND internal.native_country = "Ecuador"

N = 100


def map(k, v):
    tupl = k + "," + v
    if "Italy" in Utils.get(tupl.split(","), "native_country"):
        return [(random.randint(0, N), tupl)]
    elif "Ecuador" in Utils.get(tupl.split(","), "native_country"):
        retValue = []
        for i in range(N):
            retValue.append((i, tupl))
        return retValue
    return []


def reduce(k, lv):
    italy = []
    ecuador = []
    for v in lv:
        if "Italy" in Utils.get(v.split(","), "native_country"):
            italy.append(v)
        elif "Ecuador" in Utils.get(v.split(","), "native_country"):
            ecuador.append(v)
    retValue = []
    for x in italy:
        for y in ecuador:
            retValue.append(x + " <-> " + y)
    return retValue
