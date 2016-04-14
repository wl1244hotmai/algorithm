/**
时间限制:10000ms单点时限:1000ms内存限制:256MB描述Little Hi runs a web server. Sometimes he has to deny access from a certain set of malicious IP addresses while his friends are still allow to access his server. To do this he writes N rules in the configuration file which look like:allow 1.2.3.4/30deny 1.1.1.1allow 127.0.0.1allow 123.234.12.23/3deny 0.0.0.0/0Each rule is in the form: allow | deny address or allow | deny address/mask.When there comes a request, the rules are checked in sequence until the first match is found. If no rule is matched the request will be allowed. Rule and request are matched if the request address is the same as the rule address or they share the same first mask digits when both written as 32bit binary number.For example IP "1.2.3.4" matches rule "allow 1.2.3.4" because the addresses are the same. And IP "128.127.8.125" matches rule "deny 128.127.4.100/20" because 10000000011111110000010001100100 (128.127.4.100 as binary number) shares the first 20 (mask) digits with 10000000011111110000100001111101 (128.127.8.125 as binary number).Now comes M access requests. Given their IP addresses, your task is to find out which ones are allowed and which ones are denied.输入Line 1: two integers N and M.Line 2-N+1: one rule on each line.Line N+2-N+M+1: one IP address on each line.All addresses are IPv4 addresses(0.0.0.0 - 255.255.255.255). 0 <= mask <= 32.For 40% of the data: 1 <= N, M <= 1000.For 100% of the data: 1 <= N, M <= 100000.输出For each request output "YES" or "NO" according to whether it is allowed.样例输入5 5allow 1.2.3.4/30deny 1.1.1.1allow 127.0.0.1allow 123.234.12.23/3deny 0.0.0.0/01.2.3.41.2.3.51.1.1.1100.100.100.100219.142.53.100样例输出YESYESNOYESNO*/

//Trie树实现AC
#include<iostream>
#include<vector>
#include<string>
#include<bitset>
#include<fstream>
using namespace std;
const int allow = 1;
const int deny = 2;
struct rule {
	string cmd;
	int addressArray[4];
	long long address;
	int mask;
};
struct request {
	int addressArray[4];
	long long address;
};
struct trie_node {
	trie_node* next[2];
	int action;
	int order;
};
long long getIpAddress(int* addressArray) {
	long long sum = 0;
	for (int i = 0; i < 4; i++)
	{
		sum = sum << 8;
		sum = sum + (*addressArray++);
	}
	return sum;
}
void generateTrie(trie_node * node, rule thisRule, int order) {
	trie_node* temp = node;
	long long netAddress = thisRule.address >> (32 - thisRule.mask);
	bitset<32> netAddBin(netAddress);
	for (int i = thisRule.mask; i >=0; i--) {
		if (i == 0 && temp->order == 0) {
			temp->order = order;
			if (thisRule.cmd == "allow") {
				temp->action = allow;
			}
			if (thisRule.cmd == "deny") {
				temp->action = deny;
			}
		}
		if (i == 0) break;
		if (temp->next[netAddBin[i-1]] == NULL)
			temp->next[netAddBin[i-1]] = new trie_node();
		temp = temp->next[netAddBin[i-1]];
	}
}
void queryRule(trie_node* root, request thisRequest) {
	int resultRule=allow;
	int resultOrder=0;
	trie_node* tempNode = root;
	bitset<32> requestAddBin(thisRequest.address);
	int index = 31;
	while (tempNode != NULL) {
		if (tempNode->order != 0 && (resultOrder == 0 || resultOrder>tempNode->order)) {
			resultRule = tempNode->action;
			resultOrder = tempNode->order;
		}
		if (index < 0) break;
		tempNode = tempNode->next[requestAddBin[index]];
		index--;
	}
	if (resultRule == allow)
		cout << "YES" << endl;
	if (resultRule == deny)
		cout << "NO" << endl;
	return;
}
int main(int argv, char* argc[]) {
	ifstream cin("cin.txt");
	int N, M;
	cin >> N >> M;
	vector<rule> rules(N);
	vector<request> requests(M);
	trie_node* root = NULL;
	root = new trie_node();
	for (int i = 0; i < N; i++) {
		char temp;
		cin >> rules[i].cmd
			>> rules[i].addressArray[0] >> temp
			>> rules[i].addressArray[1] >> temp
			>> rules[i].addressArray[2] >> temp
			>> rules[i].addressArray[3] >> temp;
		if (temp == '/') {
			cin >> rules[i].mask;
		}
		else {
			cin.putback(temp);
			rules[i].mask = 32;
		}
		rules[i].address = getIpAddress(rules[i].addressArray);
		generateTrie(root, rules[i],i+1);
	}
	for (int i = 0; i < M; i++) {
		char temp;
		cin >> requests[i].addressArray[0] >> temp
			>> requests[i].addressArray[1] >> temp
			>> requests[i].addressArray[2] >> temp
			>> requests[i].addressArray[3];
		requests[i].address = getIpAddress(requests[i].addressArray);
	}
	for (int i = 0; i < M; i++) {
		queryRule(root, requests[i]);
	}
	return 0;
}