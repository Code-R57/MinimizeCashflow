# Minimize Cashflow
The motive of the project is to find the minimum cashflow between **n** friends, considering the cases with and without a given priority order. This group project was made as a part of the evaluation component for the course CS F211 - Data Structures & Algorithms of the **[BITS Pilani, Hyderabad Campus](https://www.bits-pilani.ac.in/hyderabad/)**.

## Problem Statement
Given **n number of friends** who have taken money from each other. They all need to pay back the amount; they decide to settle the returns in a way that involves minimizing the cash flow among them.\
There may also be a case where there is **some priority order** by which they need to pay. For example, a friend might require the money immediately as one is leaving, whereas others can wait.\
Our rationale for this problem is to use an *efficient algorithm* to solve the problem with and without a priority order.

## Solution Description
Algorithmic paradigm: **Greedy**\
We calculate the net difference between the total amount that needs to be paid and received by each friend. The transaction at each step involves the friend with the maximum negative net difference paying the amount to the one having the maximum positive net difference.\
In case of some priority order specified, we first calculate all the transactions involving each friend leaving in a sequential manner, then calculate the minimum cash flow for the remaining friends.

## Group Members
- **[Ritvik](https://github.com/Code-R57)**
- **[Ansh Gupta](https://github.com/anshgupta25)**
- **[Ishaan Srivastava](https://github.com/Ec5tacy)**
