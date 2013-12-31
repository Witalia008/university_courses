#include "BigInteger.h"

BigInteger::BigInteger() {
    sign = '+';
    digits.clear();
}

BigInteger::BigInteger(const string& s) throw(exception) {
    int pos = 0;
    sign = '+';
    if (s[0] == '-' || s[0] == '+') {
        sign = s[0];
        pos = 1;
    }
    for (int i = s.size() - 1; i >= pos; --i)
        if (!isdigit(s[i]))
            throw exception("not a number");
        else
            digits.push_back(s[i] - '0');
}

BigInteger::BigInteger(std::string&& s) throw(exception) {
    //To Be done...
    int pos = 0;
    sign = '+';
    if (s[0] == '-' || s[0] == '+') {
        sign = s[0];
        pos = 1;
    }
    for (int i = s.size() - 1; i >= pos; --i)
        if (!isdigit(s[i]))
            throw exception("not a number");
        else
            digits.push_back(s[i] - '0');
}


void BigInteger::add_abs(const BigInteger& a) {
    int carry = 0;
    for (int i = 0; i < max(a.length(), this->length()) || carry; ++i) {
        if (i == this->length())
            this->digits.push_back(0);
        int cur = (i < a.length() ? a.digits[i] : 0) + this->digits[i] + carry;
        carry = cur / 10;
        this->digits[i] = cur % 10;
    }
}

void BigInteger::minus_abs(const BigInteger& a) {
    if (this->comp_abs(a) < 0) return;
    int carry = 0;
    for (int i = 0; i < this->length(); ++i) {
        int cur = this->digits[i] - (i < a.length() ? a.digits[i] : 0) - carry;
        if (cur < 0) {
            cur += 10;
            carry = 1;
        } else carry = 0;
        this->digits[i] = cur;
    }
    this->delete_leading();
}

void BigInteger::multi_abs(const BigInteger& a) {
    BigInteger cp = *this;
    this->digits.assign(cp.length() + a.length() + 1, 0);
    for (int i = 0; i < cp.length(); ++i) {
        int carry = 0;
        for (int j = 0; j < a.length() || carry; ++j) {
            int cur = cp.digits[i] * (j < a.length() ? a.digits[j] : 0) + carry + this->digits[i + j];
            this->digits[i + j] = cur % 10;
            cur /= 10;
        }
    }
    this->delete_leading();
}

void BigInteger::div_abs(const BigInteger& a) {
    BigInteger cp;
    for (int i = this->length() - 1; i >= 0; --i) {
        cp <<= 1;
        cp.digits[0] = this->digits[i];
        this->digits[i] = 0;
        while (cp.comp_abs(a) >= 0) {
            cp.minus_abs(a);
            this->digits[i]++;
        }
    }
    this->delete_leading();
}


void BigInteger::delete_leading() {
    while (this->digits.back() == 0 && this->length() > 1)
        this->digits.pop_back();
}


int BigInteger::comp_abs(const BigInteger& a) const {
    if (this->length() != a.length())
        return this->length() < a.length() ? -1 : 1;
    int i;
    for (i = this->length() - 1; i > 0 && this->digits[i] == a.digits[i]; --i);
    return this->digits[i] == a.digits[i] ? 0 : (this->digits[i] < a.digits[i] ? -1 : 1);
}

int BigInteger::length() const {
    return this->digits.size();
}

string BigInteger::toString() const {
    string res = sign == '-' ? "-" : "";
    for (int i = this->length() - 1; i >= 0; --i)
        res += this->digits[i] + '0';
    return res;
}

BigInteger BigInteger::operator+(BigInteger a) const {
    BigInteger res = *this;
    if (res.sign == a.sign) {
        res.add_abs(a);
        return res;
    } else {
        if (res.comp_abs(a) < 0) {
            a.minus_abs(res);
            return a;
        } else {
            res.minus_abs(a);
            return res;
        }
    }
}

BigInteger BigInteger::operator-(BigInteger a) const {
    a.sign = (a.sign == '-' ? '+' : '-');
    return *this + a;
}

BigInteger BigInteger::operator*(BigInteger a) const {
    a.multi_abs(*this);
    a.sign = (a.sign == this->sign) ? '+' : '-';
    return a;
}

BigInteger BigInteger::operator/(BigInteger a) const {
    BigInteger res = *this;
    res.div_abs(a);
    res.sign = (a.sign == this->sign) ? '+' : '-';
    return res;
}


bool BigInteger::operator<(BigInteger a) const {
    if (this->sign != a.sign)
        return this->sign == '+';
    if (this->length() != a.length()) {
        if (this->sign == '+')
            return this->length() > a.length();
        return this->length() < a.length();
    }
    int i;
    for (i = this->length() - 1; i > 0 && this->digits[i] == a.digits[i]; --i);
    if (this->digits[i] == a.digits[i]) return true;
    if (this->digits[i] < a.digits[i])
        return this->sign == '-';
    return this->sign == '+';
}


void BigInteger::operator<<=(int cnt) {
    reverse(this->digits.begin(), this->digits.end());
    this->digits.resize(this->length() + cnt);
    reverse(this->digits.begin(), this->digits.end());
}


ostream & operator<<(ostream& out, BigInteger a) {
    out << a.toString();
    return out;
}