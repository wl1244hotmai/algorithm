//С��n�������ĸ��������������
//������˹����ɸ��
//��i = 2��ʼ����i*i �� ��������Ϊ��������
//��һ��ѭ��ѡ����С��һ����������3���������ظ���
//��֪ѭ����sqrt(n);��Ϊ����sqrt(n)�������ı�����֮ǰ���Ѿ�����Ϊ�������ˡ�

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