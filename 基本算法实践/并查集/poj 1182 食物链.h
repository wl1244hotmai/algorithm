#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
//#define INPUT
/**
Problem:1182 - ʳ������NOI2001
Begin Time:4th/Mar/2012 1:00 p.m.
End Time:4th/Mar/2012 6:47 p.m.
Cost Time:����࣬���ı��˵Ľ��ⱨ��AC��
Reference:http://apps.hi.baidu.com/share/detail/16059767
�������ݣ�
http://poj.org/showmessage?message_id=93058
�����
�Ϸ���
��ѵ��
WAһ�Σ�û������ȸ��¸��ڵ�relation���Ǹ��µ�ǰ�ڵ�relation�Ĺ�ϵ������
������������������ˣ���
˼·��
���Ӿ���Ҫдһ�������������ģ�����ϸ�Ľ��ⱨ�档
����˼·�Ǵ�Ȩ���鼯�����Ǵ��ʼ����

Part I  - Ȩֵ(relation)��ȷ����
���Ǹ������⣬ɭ������3�ֶ��A��B��B��C��C��A��
���ǻ�Ҫʹ�ò��鼯����ô�����Ǿ��Զ���֮��Ĺ�ϵ����Ϊ���鼯ÿ���ڵ��
Ȩֵ��
ע�⣬���ǲ�֪�������Ķ����Ŀ˵�ˣ�����ֻ����ţ����������ࡣ
���ԣ����ǿ����ö���֮�䡰��ԡ��Ĺ�ϵ��ȷ��һ�����鼯��
0 - ����ڵ������ĸ��ڵ���ͬ��
1 - ����ڵ㱻���ĸ��ڵ��
2 - ����ڵ�����ĸ��ڵ㡣

ע�⣬���0,1,2����������岻������ƶ��ģ����ǿ���Ŀ�е�Ҫ��
˵����ʱ�򣬵�һ�����֣������У���Ϊd��ָ���˺������ֶ���Ĺ�ϵ��
1 - X��Yͬ��
2 - X��Y

����ע�⵽���� d = 1��ʱ��( d - 1 ) = 0��Ҳ���������ƶ�������
�� d = 2��ʱ��( d - 1 ) = 1������Y��X�ԣ�Ҳ������ָ�������塣
���ԣ����0,1,2�������ѡ��


Part II - ·��ѹ�����Լ��ڵ���ϵȷ��
ȷ����Ȩֵ֮������Ҫȷ���йصĲ�����
���ǰ����еĶ���ȫ��ʼ����
struct Animal
{
int num; //�ýڵ㣨node���ı��
int parent; //��node�ĸ���
int relation; //��node�븸�ڵ�Ĺ�ϵ��0ͬ�࣬1�����ڵ�ԣ�2�Ը��ڵ�
}; Animal ani[50010];
��ʼ��Ϊ
For i = 0 to N do
ani[i].num = i;
ani[i].parent = i;
ani[i].relation = 0 ; //�Լ����Լ���ͬ��
End For

(1)·��ѹ��ʱ�Ľڵ��㷨
������A,B,C���Ｏ�����£���Ϊ���Ժ���ھ�����
A = { 1 , 2 , 3 ,4 ,5 }
B = { 6 , 7 , 8 ,9 ,10}
C = { 11, 12, 13,14,15}
���������Ѿ�����һ�����ϣ��ֱ���3��Ԫ��
SET1 = {1,2}�����ǹ涨�����е�һ��Ԫ��Ϊ���鼯�ġ�����
������������䣺
2 2 6
����һ���滰
2��6�ĸ���
ani[6].parent = 2;
ani[6].relation = 1;
��ô��6��1�Ĺ�ϵ����أ�
ani[2].parent = 1;
ani[2].relation = 0;
���ǿ��Է���6��2�Ĺ�ϵ�� 1.
ͨ��������ǿ��Է���
ani[now].parent = ani[ani[now].parent].parent;
ani[now].relation = ( ani[now].relation + ani[now.parent].relation ) % 3;
���·��ѹ���㷨����ȷ��
�������·��ѹ���㷨������һ����Ҫע��ĵط�������һ����̸
ע�⣬���ݵ�ǰ�ڵ��relation�͵�ǰ�ڵ㸸�ڵ��relation�Ƴ�
��ǰ�ڵ����丸�ڵ�ĸ��ڵ��relation�����ʽʮ����Ҫ����
���Ʋ��������涼��ⲻ�ˣ����Լ�����ٷ���һ�£�
�ðɣ�Ϊ�˷������ֵ����Ҹ�����ٹ���
i      j
үү  ����  ����  ������үү
0      0       (i + j)%3 = 0
0      1       (i + j)%3 = 1
0      2       (i + j)%3 = 2
1      0       (i + j)%3 = 1
1      1       (i + j)%3 = 2
1      2       (i + j)%3 = 0
2      0       (i + j)%3 = 2
2      1       (i + j)%3 = 0
2      2       (i + j)%3 = 1
�ţ��������Կ�����( ����relation + ����relation ) % 3 = ���Ӷ�үү��relation
�����·��ѹ���Ľڵ��㷨
(2) ���ϼ��ϵ��ȷ��
�ڳ�ʼ����ʱ�����ǿ�����ÿ�����϶���һ��Ԫ�أ�����������
��ʱ��ÿ�����϶�����Ǣ�ģ�������ÿ��Ԫ�ض���Υ����Ŀ�Ĺ涨��
ע�⣬����ʹ�ò��鼯��Ŀ�ľ��Ǿ����İ�·��ѹ����ʹ֮�߶Ⱦ�����
���������Ѿ���һ������
set1 = {1,2,7,10}
set2 = {11,4,8,13},ÿ��������������ּ�����
set3 = {12,5,4,9}
������һ�仰
2 13 2
����һ���滰,X = 13,Y = 2
����Ҫ�����������Ϻϲ���һ�����ϡ�
ֱ��
int a = findParent(ani[X]);
int b = findParent(ani[Y]);
ani[b].parent = a;
���ǰ�Y���ڼ��ϵĸ��ڵ�ĸ������ó�X���ڼ��ϵĸ��ڵ㡣
���ǣ����ǣ�������
Y���ڼ��ϵĸ������X���ڼ��ϵĸ��ڵ�Ĺ�ϵ������Ҫ��ôȷ���أ�
������X,Y���϶���·��ѹ�����ģ��߶�ֻ��2��
�����ȸ�������Ĺ�ʽ
ani[b].relation = ( 3 - ani[Y].relation + ( d - 1 ) + ani[X].relation) % 3;
�����ʽ���Ƿ������֣���ô�Ƴ�����
��һ���֣�������һ���֣�
( d - 1 ) :����X��Y֮���relation��X��Y�ĸ��ڵ�ʱ��Y��relation�������
3 - ani[Y].relation = ����Y����ڵ�Ĺ�ϵ�����Ƹ��ڵ���Y�Ĺ�ϵ
�ⲿ��Ҳ����ٷ��Ƴ����ģ����Ǿ�����
j
��         ��������ӵ�relation�����������Ǹ��ĸ��ڵ㣬��ô����relationӦ����ʲô����Ϊ�������Ǹ��ڵ㣬���Ը�.relation = 0������ֻ�ܸ��ݸ����ӽڵ㷴���Ӹ����ڵ�Ĺ�ϵ��
0             ( 3 - 0 ) % 3 = 0
1�������ӣ�   ( 3 - 1 ) % 3 = 2 //������
2���ӳԸ�)    ( 3 - 2 ) % 3 = 1 //�ӳԸ���һ����Ŷ��
������������������������������������������������������������������������������������������������������������
���ǵĹ����������ģ�
��ani[Y]�������ӵ�ani[X]�ϣ��ٰ�ani[Y]�ĸ��ڵ��ƶ���ani[X]�ϣ���󣬰�ani[Y]�ĸ��ڵ��ƶ���ani[X]�ĸ��ڵ��ϣ�������relation��
���ǵ�ô�����������һ�����ϣ�ѹ��·����ʱ���ӹ�ϵ����ôȷ����
ani[үү].relation = ( ani[����].relation + ani[����].relation ) % 3
������֪��,( d - 1 )����X��Y��relation��
�� (3 - ani[Y].relation)���� ��YΪ���ڵ�ʱ�����ĸ��׵�relation
��ô
���Ǽ����Y�ӵ�X�ϣ�Ҳ��˵������X��Y�ĸ��ף�Yԭ���ĸ��ڵ�������Y�Ķ���
Y��relation   +     ani[Y]���ڵ������ani[Y]��relation
( ( d - 1 )         +    ( 3 - ani[Y].relation) ) % 3
����ani[Y]�ĸ��׽ڵ���ani[X]��relation�ˣ�

��ô�����ѵõ���ani[Y]�ĸ��ڵ���ani[X]���ڵ�Ĺ�ϵ�ǣ�
( ( d - 1 ) + ( 3 - ani[Y].relation) + ani[X].relation ) % 3 ->Ӧ����ͬ�ඨ��
ע�⣬��������м��϶��ǳ�ʼ��״̬��ʱ��Ҳ����Ŷ
�������ͷ���Ǹ����������ϣ��ֱ�����������֣�Ϊ��
2 1 6
���빫ʽ
ani[6].relation = ( ( 2 - 1 ) + ( 3 - 0 ) + 0 ) % 3 = 1
Ҳ���ǣ�6��1��
Part III - �㷨��ȷ�Ե�֤��
���ȣ�������Ǣ�ļ��ϣ��ϲ��Ժ���Ȼ����Ǣ��
���������ɣ���ѧ���и�ʲô�Գ��Զ����������ġ�
�����ⲻ�ˣ�����ô�룡��
��set1��set2�ϲ�֮��set2�ĸ��ڵ�õ����Լ�����set1���ڵ��
��ȷrelationֵ�������set1���ڵ�Ķ��ӣ���ô
set2�����ж���ֻҪ��
( ani[X].relation + ani[Y].relation ) % 3���ܵõ��Լ���ȷ��relationֵ��
����˵����Բ���ͬһ���ϵ�����Ԫ�صĻ�������Υ���ˣ�2���ͣ�3����������Զ�����
��������仰˵����ʲô�����Ƕ����Ը�������X,Y�Ƴ������ӽڵ�֮��Ӧ�еĹ�ϵ�������ϵһȷ�������ж��ӵĹ�ϵ������ȷ����

��ʵ���еĲ�ͬ���ϵ���󶼻ᱻ�ϲ���һ�����ϵġ�
����ֻҪ��һ������������Щ�ٻ��Ϳ����ˡ�
���ȣ�����ж�
1 X Y�ǲ��Ǽٻ���//��ʱ d = 1
if ( X �� Y ����ͬһ����)
Union(x,y,xroot,yroot,d)
else
if x.relation != y.relation  ->�ٻ�
��Σ�����ж�
2 X Y�ǲ��Ǽٻ� //��ʱd = 2
if ( X �� Y ����ͬһ���ϣ�
Union(x,y,xroot,yroot,d)
else
(ani[y].relation + 3 - ani[x].relation ) % 3 != 1 ->�ٻ�
�����ʽ����ô���ģ�
3 - ani[x].relation�õ��˸��ڵ����x��relation
ani[y] + 3 - ani[x].relation�õ���y����x��relation
���ԣ�ֻҪy����x��relation����1������y����x�ԵĻ�����仰�϶��Ǽٻ���

(2)·��ѹ��Ҫ�ر�ע���һ�㣨�������Ҫ�����Լ���
·��ѹ����ʱ�򣬼ǵ�Ҫ
��findParent���ٸ���ǰ�ڵ��relation��ֵ��
�����п�����Ϊ��ǰ�ڵ�ĸ��ڵ��relation����ȷ�����´��ϡ�ﻩ����
���ӣ�
set1 = {1,2,7,10}
set2 = {3,4,8,11}
set3 = {12,5,14,9}
Union(1,3,1,3,1)
Union(3,12,3,12,2)
1 5 1
��5��relation
������ȸ���parent��relation�������Ӧ����
( 3 - 0 + 0 + 1 ) % 3 = 1��5��1�ԣ���Ȼ����
�����棬+ 0���Ǹ�0��ָ���ڵ� 12 ��relation��δ���£������0��ָ12��11��relation��
����������˵Ļ���Ӧ����
( 3 - 0 + 2 + 1 ) % 3 = 0 ,5��1��ͬһ���֣�����
������� 2 �Ǹ��½ڵ�12��relation��12��1��relation��
��ǣ�
��������⣬�������������������ⱨ�棬���Ƕ���˸��ʣ���Ŵ�Ҷ�����
���Լ���������Ƴ����Ĺ�ʽд�����Ϲ�����ѧϰ����ʡʱ��ɡ�
�Ҿ�����ô�����ã��Գ�ѧ�����ײ�������Ӱ�죬ACM���ֻ��һ��С�ڻ���Ȧ�ӣ���
����̫û��˼�ˡ�
�����ҾͰ����Լ��ܽ�������ľ�����˳�����ϣ�����԰�õ����
�Լ��ܽ�ģ��Դ�Ҳ��֪�������������ǡ���Ǣ���ģ�^ ^
��л��ƪ���ĵĲ�����Ҳ��лgzm,lqy��λѧ����ָ����
c0de4fun


*/
using namespace std;
const int c0de4fun = 50010;//������������ֵ
						   ///ָ�����ڵ����Լ��Ĺ�ϵ��0ͬ�࣬1���ԣ�2�Ը�
const int SAME = 0;
const int ENEMY = 1;
const int FOOD = 2;
struct Animal
{
	int parent;
	int num;
	int relation;
};
Animal ani[c0de4fun];
long ans;
int findParent(Animal* node)
{
	///Wrong Answer ��Ϊ�������д����
	///����������ǡ���Ǣ�ġ�
	///����˵���ñ�֤ÿ��Ԫ�صĸ��׵�relation�ǶԵ�
	///�����Լ���relation
	///��Ϊ�Լ���relation�͸��׵�relation�й�
	///�����ΪʲôҪ��findParent��relation���µ�ԭ��
	int tmp;
	if (node->parent == node->num)
		return node->parent;
	tmp = node->parent;
#ifdef DBG
	printf("Animal %d s Parent is %d\n", node->num, node->parent);
#endif
	// node->relation = ( ani[node->parent].relation + node->relation ) % 3;
	node->parent = findParent(&ani[node->parent]);
	node->relation = (ani[tmp].relation + node->relation) % 3;
	return node->parent;
}
void Union(int x, int y, int a, int b, int d)
{
	ani[b].parent = a;
	///rootY.parent = rootX.parent;
	ani[b].relation = ((3 - ani[y].relation) + (d - 1) + ani[x].relation) % 3;
}

void init_Animal(int n)
{
	for (int i = 1; i <= n; i++)
	{
		ani[i].num = i;
		ani[i].parent = i;
		ani[i].relation = SAME;
	}
}
void func_food_chain()
{
	int N, K;
	int d, X, Y;
#ifdef INPUT
	freopen("b:\\acm\\poj1182\\input.txt", "r", stdin);
#endif
	scanf_s("%d%d", &N, &K);
	init_Animal(N);
	for (int i = 0; i < K; i++)
	{
		scanf_s("%d%d%d", &d, &X, &Y);
		if (X > N || Y > N)
			ans++;
		else
		{
			if (d == 2 && X == Y)
				ans++;
			else
			{
				int a = findParent(&ani[X]);
				int b = findParent(&ani[Y]);
				if (a != b)
				{
					///x��y����ͬһ������
					Union(X, Y, a, b, d);
				}
				else
				{
					switch (d)
					{
					case 1:
						if (ani[X].relation != ani[Y].relation)
							ans++;
						break;
					case 2:
						if (((ani[Y].relation + 3 - ani[X].relation) % 3) != 1)
							ans++;
						break;
					}
				}
			}
		}
	}
	printf("%d\n", ans);
	return ;
}
