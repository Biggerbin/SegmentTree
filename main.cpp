#include <iostream>
#include <vector>
using namespace std;

class SegmentTree {
public:
	class SegmentNode {
	public:
		int count = 0;
		int left;
		int right;
	};
private:
	int m;
	vector<SegmentNode*> segment;

public:
	SegmentTree(int m) {
		this->m = m;
		segment.resize(4 * m);
		buildSegmentTree(1, m, 1);
	}

	void buildSegmentTree(int left, int right, int i) {
		segment[i] = new SegmentNode();
		segment[i]->left = left;
		segment[i]->right = right;
		if (left == right) return;
		int mid = left + (right - left) / 2;
		buildSegmentTree(left, mid, i * 2);
		buildSegmentTree(mid + 1, right, i * 2 + 1);
	}

	void insert(int data) {
		int left = 1, right = m;
		int i = 1;
		while (left != right) {
			segment[i]->count++;
			int mid = left + (right - left) / 2;
			if (data <= mid) {
				right = mid;
				i = i * 2;
			}
			else {
				left = mid + 1;
				i = i * 2 + 1;
			}
		}
		segment[i]->count++;
	}

	void erase(int data) {
		int left = 1, right = m;
		int i = 1;
		while (left != right) {
			int mid = left + (right - left) / 2;
			segment[i]->count--;
			if (data <= mid) {
				right = mid;
				i = i * 2;
			}
			else {
				left = mid + 1;
				i = i * 2 + 1;
			}
		}
		segment[i]->count--;
	}

	int count(int left, int right) {
		return countInternal(left, right, 1);
	}

	int countInternal(int left, int right, int i) {
		if (segment[i]->left == left && segment[i]->right == right) {
			return segment[i]->count;
		}
		int mid = segment[i]->left + (segment[i]->right - segment[i]->left) / 2;
		if (left > mid) {
			return countInternal(mid + 1, right, i * 2 + 1);
		}
		else if (right <= mid) {
			return countInternal(left, right, i * 2);
		}
		else {
			return countInternal(left, mid, i * 2) + countInternal(mid + 1, right, i * 2 + 1);
		}
	}
};

int main() {

	SegmentTree seg(51);

	vector<int> nums{ 1,2,3,4,5,6,2,2,7,8,9,0 };
	for (auto i : nums) {
		seg.insert(i);
	}
	cout << "----------------------insert end-------------------" << endl;
	cout << seg.count(2, 3) << endl;
	seg.erase(3);
	cout << seg.count(2, 3) << endl;

	return 0;
}