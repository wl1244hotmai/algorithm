///*��������
//��ĳͼ�β���ϵͳ��, �� N ������, ÿ�����ڶ���һ��������������ֱ�ƽ�еľ������򡣴��ڵı߽��ϵĵ�Ҳ���ڸô��ڡ�����֮���в�ε�����, �ڶ���һ�������ص���������, ֻ����ʾλ�ڶ���Ĵ���������ݡ�
//��������Ļ��һ�����ʱ��, ���ѡ���˴��ڱ����λ�õ���㴰��, ����������ھͻᱻ�Ƶ����д��ڵ����, ��ʣ��Ĵ��ڵĲ��˳�򲻱䡣���������λ�ò������κδ���, ��ϵͳ���������ε����
//��������ϣ����дһ������ģ�������ڵĹ��̡�
//�����ʽ
//����ĵ�һ��������������, �� N �� M��(1 �� N �� 10, 1 �� M �� 10)
//������ N �а��մ����²㵽����˳����� N �����ڵ�λ�á� ÿ�а����ĸ��Ǹ����� x1, y1, x2, y2, ��ʾ�ô��ڵ�һ�Զ�������ֱ�Ϊ(x1, y1) ��(x2, y2)����֤ x1 < x2, y1 2��
//	������ M ��ÿ�а��������Ǹ����� x, y, ��ʾһ������������ꡣ
//	��Ŀ���漰�������е�;��εĶ���� x, y ����ֱ𲻳��� 2559 �͡���1439��
//	�����ʽ
//	������� M ��, ÿһ�б�ʾһ��������Ľ��������ô������ѡ����һ������, �����������ڵı��(���ڰ��������е�˳��� 1 ��ŵ� N); ���û��, �����"IGNORED"(����˫����)��
//	��������
//	3 4
//	0 0 4 4
//	1 1 5 5
//	2 2 6 6
//	1 1
//	0 0
//	4 4
//	0 5
//	�������
//	2
//	1
//	1
//	IGNORED
//	����˵��
//	��һ�ε����λ��ͬʱ���ڵ� 1 �͵� 2 ������, �������ڵ� 2 ������������, ����ѡ���ұ����ڶ��㡣
//	�ڶ��ε����λ��ֻ���ڵ� 1 ������, ��˸ôε��ѡ���˴˴��ڲ��������ڶ��㡣���ڵ��������ڵĲ�ι�ϵ���ʼ״̬ǡ���෴�ˡ�
//	�����ε����λ��ͬʱ�����������ڵķ�Χ, �����������ڵ� 1 �����ڴ��ڶ���, ����ѡ��
//	�������(0, 5) �������κδ��ڡ�
//	*/
//#include<iostream>
//#include<vector>
//using namespace std;
//struct mouseOperator {
//	int x;
//	int y;
//};
//class window {
//private:
//	int widthStart;
//	int widthEnd;
//	int heightStart;
//	int heightEnd;
//	int orderNum;
//public:
//	friend void swapWindow(window a, window b);
//	int getOrderNum() {
//		return orderNum;
//	}
//	void getPosition(int orderNum) {
//		cin >> widthStart >> heightStart >> widthEnd >> heightEnd;
//		this->orderNum = orderNum;
//	}
//	bool isInWindow(mouseOperator op) {
//		if (op.x >= widthStart
//			&& op.x <= widthEnd
//			&& op.y >= heightStart
//			&& op.y <= heightEnd) {
//			return true;
//		}
//		else
//			return false;
//	}
//};
//
//void swapWindow(window a, window b) {
//	swap(a.heightStart, b.heightStart);
//	swap(a.heightEnd, b.heightEnd);
//	swap(a.widthStart, b.widthStart);
//	swap(a.widthEnd, b.widthEnd);
//};
//int main(int argv, char* argc[]) {
//	int N, M;
//	cin >> N >> M;
//	vector<window> windows(N); 
//	vector<mouseOperator> operators(M);
//	for (int i = 0; i < N; i++) {
//		windows[i].getPosition(i+1);
//	}
//	for (int i = 0; i < M; i++) {
//		cin >> operators[i].x >> operators[i].y;
//	}
//	for (int i = 0; i < (int)operators.size(); i++) {
//		bool flag = false;
//		for (int j = windows.size()-1; j >= 0; j--) {
//			if (windows[j].isInWindow(operators[i])) {
//				cout << windows[j].getOrderNum() << endl;
//				swap(windows[j], windows[windows.size() - 1]);
//				flag = true;
//				break;
//			}
//		}
//		if (!flag) {
//			cout << "IGNORED" << endl;
//		}
//	}
//	return 0;
//}