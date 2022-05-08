#include <bits/stdc++.h>
using namespace std;

const int mod = 433;

struct ploy {
	vector<int> bit;

	ploy(int val = 0) {
		while(val) {
			bit.push_back(val&1);
			val >>= 1;
		}
	}

	int& operator[](int b) {
		return bit[b];
	}

	int deg() {
		return bit.size() - 1;
	}
	
	void resize(int n) {
		bit.resize(n);
	}

	int toint() {
		int res = 0;
		for(int i = this->deg(); i >= 0; --i) if((*this)[i]) {
			res |= (1<<i);
		}
		return res;
	}

	ploy operator+(ploy b) {
		return ploy(this->toint() ^ b.toint());
	}

	ploy operator-(ploy b) {
		return *this+b;
	}

	ploy operator*(ploy b) {
		ploy mul;
		mul.resize(this->deg() + b.deg() + 1);
		for(int i = 0; i <= mul.deg(); ++i) mul[i] = 0;
		for(int i = 0; i <= this->deg(); ++i) if((*this)[i]) {
			for(int j = 0; j <= b.deg(); ++j) if(b[j]) {
				mul[i + j] ^= 1;
			}
		}
		ploy pmod = mod, res = 0;
		for(int i = mul.deg(); i >= pmod.deg(); --i) if(mul[i]) {
			for(int j = 0; j <= pmod.deg(); ++j) if(pmod[j]) mul[i - pmod.deg() + j] ^= 1;
		}
		return ploy(mul.toint());
	}

	ploy operator/(ploy b) {
		int quo = 0, rem = this->toint();
		for(int i = this->deg(); i >= b.deg(); --i) if(rem>>i&1) {
			quo |= 1<<(i-b.deg());
			for(int j = 0; j <= b.deg(); ++j) if(b[j]) {
				rem ^= 1<<(i-b.deg()+j);
			}
		}
		return ploy(quo);
	}

	ploy operator%(ploy b) {
		int quo = 0, rem = this->toint();
		for(int i = this->deg(); i >= b.deg(); --i) if(rem>>i&1) {
			quo |= 1<<(i-b.deg());
			for(int j = 0; j <= b.deg(); ++j) if(b[j]) {
				rem ^= 1<<(i-b.deg()+j);
			}
		}
		return ploy(rem);
	}

	ploy exgcd(ploy a, ploy b, ploy &x, ploy &y) {
		if(b.deg() + 1 == 0) {
			x = 1, y = 0;
			return a;
		}
		ploy d = exgcd(b, a % b, x, y);
		ploy z = x;
		x = y;
		y = z - a / b * y;
		return d;
	}

	ploy inv() {
		if((*this).toint() == 0) return 0;
		ploy x = 0, y = 0;
		exgcd(*this, mod, x, y);
		return x;
	}
};

int c[8] = {1, 1, 0, 0, 0, 1, 1, 0};

int subBytes(int n) {
	int inv = ploy(n).inv().toint();
	int a[8]; for(int i = 0; i < 8; ++i) a[i] = inv>>i&1;
	int ans = 0;
	for(int i = 0, b; i < 8; ++i) {
		b = (a[i] + a[(i + 4) % 8] + a[(i + 5) % 8] + a[(i + 6) % 8] + a[(i + 7) % 8] + c[i]) % 2;
		if(b) ans |= 1<<i;
	}
	return ans;
}

int main() {
	int a = 8*16+3;
	printf("%02X\n", subBytes(a));
	/*for(int i = 0; i < 16; ++i) {
		for(int j = 0; j < 16; ++j) {
			printf("%02x%c", subBytes((i<<4) + j), j == 15 ? '\n' : ' ');
		}
	}*/
	return 0;
}
