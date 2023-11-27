attributes = [
    "id",
    "age",
    "workclass",
    "fnlwgt",
    "education",
    "education_num",
    "marital_status",
    "relationship",
    "race",
    "sex",
    "capital_gain",
    "capital_loss",
    "hours_per_week",
    "native_country",
]


def get(row, attribute):
    for i, att in enumerate(attributes):
        if att == attribute:
            return row[i]
    return None
