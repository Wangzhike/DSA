# 找零问题    

## 1. 零钱集合中元素使用次数不限    

### 1.1 求所有可行的找零方案    

### 1.2 求次数最小的找零方案    
  [LeetCode 322. Coin Change](https://leetcode.com/problems/coin-change/description/)，题目描述：    
  > You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.    

  1. 做出一个选择，得到待解决的子问题    
    类似与贪心的思想，将零钱集合按照非降序排序，考虑零钱集合中的末尾元素即当前面额最大的零钱`C[k]`，选择或不选择会产生两个独立的子问题。如果将原问题描述为`F(Amount, C_k)`，则：    
	1. 选择`C[k]`，对应的子问题为：`F(Amount-C[k], C_k)`    
	2. 不选择`C[k]`，对应的子问题为：`F(Amount, C_(k-1))`    

  2. 组合子问题的最优解得到原问题的最优解    
    `F(Amount, C_k) = min[F(Amount, C_(k-1)), F(Amount-C[k], C_k)]`    

  3. 证明
    1. 子问题的解为它本身的最优解    
	  1. 选择`C[k]`    
	    剩余钱数为`Amount-C[k]`，可用的零钱集合为`C_k`，所以子问题最优解可描述为`F(Amount-C[k], C_k)+1`    
	  2. 不选择`C[k]`    
	    钱数仍为`Amount`，可用的零钱集合为`C_(k-1)`，所以子问题的最优解可描述为`F(Amount, C_(k-1))`    
	
	2. 组合子问题的最优解可得到原问题的最优解    
	  原问题的最优解必然从两种选择对应的子问题中产生，而且是其中找零次数最小的选择。选择`C[k]`，意味着已经找零了一次，所以子问题的最优解为`F(Amount-C[k], C_k)+1`。对两个子问题的最优解取较小的，即原问题的最优解。    

  4. 存在重叠子问题    
    应该存在:)    

  代码实现：    
  ```cpp
  int coinChange(vector<int>& coins, int amount) {
  		if (amount <= 0)
            return 0;
        vector<vector<int>> n_change(coins.size()+1, vector<int>(amount+1, amount+1));
        /* 
		   只将amount=0那列置为0，而C_0那行保持初始值amount+1，这样才能保证
		   n_change[i][j]判断min(n_change[i-1][j], n_change[i][j-coins[i-1]]+1)时，
		   n_change[i-1][j]值的合法性
		*/
		for (int i = 0; i < coins.size()+1; ++i)
            n_change[i][0] = 0;
        int mostR = coins.size() - 1;
        for (int i = mostR; 0 <= i && amount < coins[i]; --i)
            --mostR;
        for (int i = 1; i <= mostR+1; ++i)
            for (int j = 1; j <= amount; ++j) {		//j的下标要从1开始，不能从coins[i-1]开始，否则1~coins[i-1]-1之间的值未计算！
                n_change[i][j] = n_change[i-1][j];
                if (coins[i-1] <= j)
                    n_change[i][j] = min(n_change[i-1][j], n_change[i][j-coins[i-1]]+1);
            }
        return n_change[mostR+1][amount] == amount+1 ? -1 : n_change[mostR+1][amount];
    } 
  ```
