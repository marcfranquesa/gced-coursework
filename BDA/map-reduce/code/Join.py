import Utils

# SELECT external.*, internal.*
# FROM adult as internal INNER JOIN adult as external ON internal.marital_status = external.marital_status
# WHERE external.native_country = "Italy" AND internal.native_country = "Ecuador"


def map(k, v):
    row = [k] + v.split(",")
    if (
        Utils.get(row, "native_country") == "Italy"
        or Utils.get(row, "native_country") == "Ecuador"
    ):
        return [(Utils.get(row, "marital_status"), row)]
    return []


def reduce(k, lv):
    italy = [v for v in lv if Utils.get(v, "native_country") == "Italy"]
    ecuador = [v for v in lv if Utils.get(v, "native_country") == "Ecuador"]

    out = []
    for italian in italy:
        for ecuatorian in ecuador:
            out.append((italian, ecuatorian))

    return out
