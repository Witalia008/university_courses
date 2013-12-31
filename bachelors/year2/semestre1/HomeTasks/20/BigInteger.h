#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;

class BigInteger {
protected:
    char sign;
    vector<int> digits;

    void add_abs(const BigInteger&);
    void minus_abs(const BigInteger&);
    void multi_abs(const BigInteger&);
    void div_abs(const BigInteger&);
    int comp_abs(const BigInteger&) const;
    void delete_leading();
public:
    BigInteger();
    BigInteger(const std::string&) throw(exception);
    BigInteger(std::string&&) throw(exception);

    int length() const;
    std::string toString() const;

    BigInteger operator+(BigInteger) const;
    BigInteger operator-(BigInteger) const;
    BigInteger operator*(BigInteger) const;
    BigInteger operator/(BigInteger) const;

    bool operator<(BigInteger) const;
    void operator<<=(int cnt);

};

ostream & operator<<(ostream& out, BigInteger a);
/*BigInteger operator "" LONG(const char *s) {
    return BigInteger(string(s));
}*/