import streamlit as st
from vega_datasets import data
import altair as alt


def ex2():
    cars = data.cars.url
    return alt.Chart(cars).mark_bar().encode(
        x="Origin:N",
        y="max(Displacement):Q",
    )


def ex6():
    stocks = data.stocks.url
    return alt.Chart(stocks).mark_line().encode(
        x="year:N",
        y="mean(price):Q",
        color="symbol:N"
    ).transform_calculate(
        year="year(datum.date)"
    )


def helper():
    cars = data.cars.url
    main = alt.Chart(cars).mark_line().encode(
        x="Year:T",
        y="mean(Horsepower):Q",
        color="Origin:N"
    )
    ci = alt.Chart(cars).mark_area(opacity=0.5).encode( 
        x="Year:T",
        y="ci0(Horsepower):Q",
        y2="ci1(Horsepower):Q",
        color="Origin:N"
    )
    return main, ci


def ex14():
    main, ci = helper()
    return main & ci


def ex15():
    main, ci = helper()
    return main + ci


def main():
    st.title("Lab 3")
    st.altair_chart(ex2(), use_container_width=True)
    st.altair_chart(ex6(), use_container_width=True)
    st.altair_chart(ex14(), use_container_width=True)
    st.altair_chart(ex15(), use_container_width=True)


if __name__ == "__main__":
    main()