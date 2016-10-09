//小于n的质数的个数（或者输出）
//埃拉托斯特尼筛法
//从i = 2开始，把i*i 到 最大的数置为非质数；
//下一次循环选择最小的一个质数（如3），继续重复；
//已知循环到sqrt(n);因为大于sqrt(n)的质数的倍数，之前都已经被标为非质数了。

int countPrimes(int n){
   bool isPrime[n];
   for(int i = 2; i < n; i++){
      isPrime[i] = true;
   }
   for(int i = 2; i*i < n; i++){
      if (!isPrime[i])
        continue;
      for(int j = i * i; j < n; j += i){
         isPrime[j] = false;
      }
   }
   int count = 0;
   for (int i = 2; i < n; i++) {
      if (isPrime[i]) count++;
   }
   return count;
}