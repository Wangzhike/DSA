# 找零问题    

1. [零钱集合中元素使用次数不限](#1-零钱集合中元素使用次数不限)    
  1. [求次数最小的找零方案](#11-求次数最小的找零方案)    
  2. [求所有可行的找零方案](#12-求所有可行的找零方案)     
2. [零钱集合中元素使用次数有限](#2-零钱集合中元素使用次数有限)    
  1. [零钱集合中元素最多使用一次(01背包问题)](#21-零钱集合中元素最多使用一次01背包问题)    

## 1. 零钱集合中元素使用次数不限    

### 1.1 求次数最小的找零方案    
  [LeetCode 322. Coin Change](https://leetcode.com/problems/coin-change/description/)，题目描述：    
  > You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.    

  1. 做出一个选择，得到待解决的子问题    
    类似于贪心的思想，将零钱集合按照非降序排序，考虑零钱集合中的末尾元素即当前面额最大的零钱`C[k]`，选择或不选择会产生两个独立的子问题。如果将原问题描述为`F(Amount, C_k)`，则：    
	  1. 选择`C[k]`，对应的子问题为：`F(Amount-C[k], C_k)`    
	  2. 不选择`C[k]`，对应的子问题为：`F(Amount, C_(k-1))`    

  2. 组合子问题的最优解得到原问题的最优解    
    `F(Amount, C_k) = min[F(Amount, C_(k-1)), F(Amount-C[k], C_k)+1]`    

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
            for (int j = 1; j <= amount; ++j) {
            /* j的下标要从1开始，不能从coins[i-1]开始，否则1~coins[i-1]-1之间的值是amount+1，未被计算！ */
                n_change[i][j] = n_change[i-1][j];
                if (coins[i-1] <= j)
                    n_change[i][j] = min(n_change[i-1][j], n_change[i][j-coins[i-1]]+1);
            }
        return n_change[mostR+1][amount] == amount+1 ? -1 : n_change[mostR+1][amount];
    } 
  ```

  5. 空间优化O(n^2)->O(n)    
    根据最优子结构`F(Amount, C_k) = min[F(Amount, C_(k-1)), F(Amount-C[k], C_k)]`，如果以C_k作为行，能够看到原问题的最优解只依赖于当前行和上一行的子问题解，所以我们完全可以将原来O(n^2)空间的n_change，降维到O(n)。计算`F(j, i)`时，对应于此时要更新的`n_change[j]`；子问题`F(j, i-1)`对应已经计算过的`n_change[j]`；子问题`F(j-coins[i-1], i)`对应于当前行已经计算过的`n_change[j-coins[i-1]]`。空间优化后的代码如下：    
    
  ```cpp
    int coinChange(vector<int>& coins, int amount) {
        if (amount <= 0)
            return 0;
        vector<int> n_change(amount+1, amount+1);
        n_change[0] = 0;
        int mostR = coins.size() - 1;
        for (int i = mostR; i >= 0 && amount < coins[i]; --i)
            --mostR;
        for (int i = 0; i <= mostR; ++i)
            for (int j = coins[i]; j <= amount; ++j) {
            /* j的下标可以从coins[i]开始，因为对于j < coins[i]的值，
               j-coins[i]的值小于0，是非法的，所以n_change[j]的值就
               只能等于n_change[j]，而这个值就是当前已经计算过的n_change[j]，无须更新！ */
                n_change[j] = min(n_change[j], n_change[j-coins[i]]+1);
            }
        return n_change[amount] == amount + 1 ? -1 : n_change[amount];
    }
  ```

### 1.2 求所有可行的找零方案    
  链家2018校招技术类B卷：    
  > 你现在有5角、2角、1角的硬币很多(可以理解为要多少有多少)，请设计程序，对于某一数额的钱数，计算出共有多少种零钱拼凑方案。    
  例如：    
    6角钱有如下拼法：    
	  6个1角    
	  1个2角和4个1角    
	  3个2角    
	  1个5角和1个1角    
	  2个2角和2个1角    
    输出：共有5种拼凑方案。    

  类似于[1.1 求次数最小的找零方案](#11-求次数最小的找零方案)，最优子结构为：    
  `F(Amount, C_k) = F(Amount, C_(k-1)) + F(Amount-C[k], C_k)`    
  根据最优子结构，可以使用DP求解该问题，但是此问题的硬币集合已经给出且相对简单，故也可直接采用暴力枚举方法求解：还是类似于贪心思路，先使用面额最大5角钱，剩余的钱再使用2角钱拼凑，最后剩下的钱使用1角钱拼凑。该实现代码如下：    
  ```cpp
int NCoinComb(int x)
{
    int result = 0;
    int yuE5,yuE2;
    for(int Nof5=x/5; Nof5 >=0; --Nof5){
        yuE5 = x - 5*Nof5;
        for(int Nof2=yuE5/2; Nof2>=0; --Nof2){
            yuE2 = yuE5 - 2*Nof2;
			result++;
			cout << result << "\t:\t" << Nof5 << "*5J + " << Nof2 << "*2J + " << yuE2 << "*1J" << "\t" << (Nof5+Nof2+yuE2) <<endl;
        }
    }
    return result;
}     
  ```

  当然也可以从1角钱开始枚举，然后是2角钱，最后是5角钱，只不过这样子枚举过程要复杂些，还要做判断。这种方式实现代码如下：    
  ```cpp
int numOfCoinComb(int n) {
	int remE1, remE2;
	int num = 0;
	for (int n1 = 0; n1 <= n/1; ++n1) {
		remE1 = n - 1*n1;
		for (int n2 = 0; n2 <= remE1/2; ++n2) {
			remE2 = remE1 - 2*n2;
			for (int n5 = 0; n5 <= remE2/5; ++n5) {
				if (n1*1 +n2*2 + n5*5 == n) {
					cout << num << "\t:\t" << n1 << "*1J " << n2 << "*2J " << n5 << "*5J\t" << n1+n2+n5 << endl;
					++num;
				}
			}
		}
	}
	return num;
}  
  ```

  [LeetCode 518: Coin Change 2](https://leetcode.com/problems/coin-change-2/description/):    
  > You are given coins of different denominations and a total amount of money. Write a function to compute the number of combinations that make up that amount. You may assume that you have infinite number of each kind of coin.    

  如上所述，最优子结构为：`F(Amount, C_k) = F(Amount, C_(k-1)) + F(Amount-C[k], C_k)`。直接使用空间占用为O(n)的思路解决该问题，但是需要对初始值进行特别处理：具体而言，因为是两个子问题通过相加得到原问题的解，子问题`F(Amount, C_(k-1))`在此时为已经计算过(或初始化了的)F[Amount]，当硬币集合大小为空时，其取初始值，所以该初始值应为0；子问题`F(Amount-C[k], C_k)`此时为已经计算过的`F(Amount-C[k])`。特别的，此时对于`F(0)`，也就是`Amount=0`，同时零钱集合为空的情况，由于`F(Amount-C[k])`会取到该值`F(0)`，而既然能通过使用面额为`C[k]`的零钱，将`Amount`减小到0，此时就对应了一种合法的找零方案，所以`F(0)`应该取1，以上就是对初始化的处理。    
  代码实现如下：    
  ```cpp
  int change(int amount, vector<int>& coins) {
        int mostR = coins.size() - 1;
        for (int i = mostR; i >= 0 && amount < coins[i]; --i)
            --mostR;
        if (mostR < 0 && amount == 0)
            return 1;
        if (amount <= 0)
            return 0;
        // cout << mostR << endl;
        vector<int> num(amount+1, 0);
        num[0] = 1;
        for (int i = 0; i <= mostR ; ++i) {
            for (int j = coins[i]; j < amount+1; ++j) {
				/* 同上，j的下标从coins[i]开始！ */
                num[j] += num[j-coins[i]];
            }
        }
        return num[amount];
    } 
  ```

## 2. 零钱集合中元素使用次数有限    

### 2.1 零钱集合中元素最多使用一次(01背包问题)    
  算法导论上对**01背包问题**定义如下：    
  > 一个正在抢劫商店的小偷发现了n个商品，第i个商品价值vi美元，重wi磅，vi和wi都是整数。这个小偷希望拿走价值尽量高的商品，但是他的背包最多能容纳W磅重的商品，W是一个整数。他应该拿哪些商品呢？(我们称这个问题是0-1背包问题，因为对每个商品，小偷要么把它完整拿走，要么把它留下；他不能只拿走一个商品的一部分，或者把一个商品拿走多次。)    

  与上面分析类似，首先考虑对于商品集合的末尾元素`S[n]`，拿或不拿就会产生两个独立的子问题：拿走`S[k]`，则有子问题`F(W-S[n], S_(n-1))+v_n`；不拿`S[n]`，则有子问题`F(W, S_(n-1))`。可以证明这两个子问题都为各自的最优解，而选出两个子问题中价值更高的那个子问题，即为原问题的最优解，所以最优子结构为：`F(W, S_n) = max(F(W, S_(n-1)), F(W-S[n], S_(n-1))+v_n)`。    
  仍然使用O(n)空间的方法解决该问题，也需要对初始值进行特殊处理：由于是两个子问题中价值更高的那个，所以子问题`F(W, S_(n-1))`对应上一次已经计算过的`F(W)`，当商品集合为空时，其取初始值，该初始值应为0；子问题`F(W-S[n], S_(n-1))+v_n`此处对应于`F(W-S[n])+v_n`，但与之前不同的是，此处对应于零钱集合的规模为`n-1`，即`S_(n-1)`，而不是上面例子中的`n`，因为对于商品`S[n]`，只能使用一次，而不是无限次。所以这里`F(W-S[n], S_(n-1))+v_n`对应的`F(W-S[n])+v_n`，应该为内循环上一次循环已经计算过的`F(W-S[n])+v_n`，而不是上面的本次循环已经计算出的`F(W-S[n])+v_n`，所以内循环应该是倒序的！这样才能确保计算`F(W)`时用到的`F(W-S[n])+v_n`是内循环上一次循环计算出的。具体实现代码如下：    
  ```cpp
int oneZeroKnapsack(vector<vector<int>> &things, int weight) {
	int infval = 0;
	vector<int> kp(weight+1, infval);
	for (int i = 0; i < things.size(); ++i) {
		for (int j = weight; j >= things[i][0]; --j) {
			kp[j] = max(kp[j], kp[j-things[i][0]]+things[i][1]);
		}
	}
	return kp[weight];
}  
  ```

  再看一道南阳理工OJ的题目[860. 又见01背包](http://acm.nyist.edu.cn/JudgeOnline/problem.php?pid=860)：    
  > 有n个重量和价值分别为wi 和 vi 的 物品，从这些物品中选择总重量不超过 W 
的物品，求所有挑选方案中物品价值总和的最大值。    
　　1 <= n <=100    
　　1 <= wi <= 10^7    
　　1 <= vi <= 100    
　　1 <= W <= 10^9    

  由于背包可容纳重量`W`可能取到`10^9`这么大，如果直接以`W`作为维度，求价值最高的方案，经测试会出现内容超出限制。所以转变思路，以价值作为维度，求价值对应的最小重量的装包方案，价值的最大取值为`100*100=10^4`，相比于重量的最大值小了很多，然后从最大价值`10^4`开始，逆序寻找第一个重量小于等于`W`的方案对应的价格，即为原问题所求的最高价格。所以最优子结构为：`F(V, S_n) = min(F(V, S_(n-1)), F(V-v_n, S_(n-1))+w_n)`。同样的，也需要对初始值进行特殊处理：由于求两个子问题中的重量较小者，所以子问题`F(V, S_(n-1))`此处对应的`F(V)`，当商品集合为空时，其取初始值，该初始值应为一个很大的数，这个数的值要大于重量的最大值；子问题`F(V-v_n, S_(n-1))+w_n`此处对应`F(V-v_n)+w_n`，可能会取到值`F(0)`，即价值为0，且商品集合为空时的情况，此时对应的重量应为0。最后，由于`F(V-v_n, S_(n-1))+w_n`对应于商品集合的规模为`n-1`，所以内循环也应该是倒序的。具体代码实现如下：    
  ```cpp
int oneTwoKnapsackForMaxValue_inOn(vector<vector<int> > &things, int value, int weight) {
	int infval = 1e9+1;
	vector<int> kp(value+1, infval);
	kp[0] = 0;
	for (int i = 0; i < things.size(); ++i) {
		for (int j = value; j >= things[i][1]; --j) {
			kp[j] = min(kp[j], kp[j-things[i][1]]+things[i][0]);
		}
	}
	int maxValue = 0;
	for (int i = value; i >= 0; --i) {
		if (kp[i] <= weight) {
			maxValue = i;
			break;
		}
	}
	return maxValue;
}
  ```


