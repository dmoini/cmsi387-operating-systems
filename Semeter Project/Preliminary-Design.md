# Preliminary Design Document

Serena Zafiris, Donovan Moini, Ian Lizarda

## Description
A system call named `hog` that when called returns which process(es) is/are using the greatest percentage of the CPU.
`hog` also takes in a single argument *n*, where 1 ≤ *n* ≤ 20, which returns the top *n* processes using the greatest percentage of the CPU.

## Rationale
We can get such information with the command `ps -ev` and use a utility function(s) to parse through the data, but this is unnecessary work. A system call that just returns the process(es) utilizing the greatest percentage of the CPU would be more efficient and user-friendly.

Knowing which processes hog up the most CPU usage is useful to many users. For example, if our computer is running at high-fan speeds, we may want to grab the top 5 CPU processes that are causing our computer to go berserk. 

## Affected Modules
None

## New Modules
None