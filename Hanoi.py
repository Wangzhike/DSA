#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#move(n, a, b, c)
#n表示柱子a上的盘子数量
#a, b, c表示把a上的所有盘子借助b移动到c
def move(n, a, b, c):
	if(n == 1):
		#只有一个盘子时，可以直接从a移动到c
		print('%c-->%c' %(a,c))
	else:#通过分布减而治之
		#先把a上面的n-1个盘子借助c移动到b上
		move(n-1,a,c,b)
		#再把a上最下面的盘子移动到c
		move(1,a,b,c)
		#再把b上的n-1个盘子借助a移动到c上
		move(n-1,b,a,c)
