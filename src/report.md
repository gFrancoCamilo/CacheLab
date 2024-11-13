# Report

Comparing the LRU, Random, and Tree LRU, we can see that the LRU performs slightly better than the other two options, while Random performs the worst. That happens because random replacement chooses a block at random without taking into consideration important stats, such as access frequency. LRU, on the other hand, does the exact opposite, replacing blocks that are least used. Finally, TreeLRU does not outperform LRU because it is an approximate value of frequency, while LRU stores the frequency directly.
