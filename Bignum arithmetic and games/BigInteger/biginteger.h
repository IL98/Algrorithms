#include <iostream>
#include <vector>
#include <string>


class BigInteger {
    std::vector<int> digits_;
    bool positive_;
    bool isShiftedSubtractionPossible(const BigInteger& b, int shift) const {
        if (digits_.size() != b.digits_.size() + shift) {
            return digits_.size() < b.digits_.size() + shift;
        }
        for (int i = digits_.size() - 1; i >= 0; i--) {
            int d;
            if ((size_t)(i - shift) < digits_.size()) {
                d = b.digits_[i - shift];
            } else{
                d = 0;
            }
            if (digits_[i] != d)
                return digits_[i] < d;
        }
        return false;
    }
    BigInteger& shiftedSubtract(const BigInteger& b, int shift) {
        for (int i = 0; (size_t)i < digits_.size(); i++) {
            if ((size_t)(i - shift) < b.digits_.size()) {
                digits_[i] -= b.digits_[i - shift];
            }
        }
        BuildCorrect();
        return *this;
    }

    //обновляет содержимое digits_
    //приводит его в корректную форму
    void BuildCorrect(int begin = 0) {
        for (int i = begin; (size_t)i < digits_.size(); i++) {
            if (digits_[i] < 0) {
                --digits_[i + 1];
                digits_[i] += 10;
            } else {
                if (digits_[i] - 10 >= 0) {
                    if (digits_.size() == (size_t)i + 1) {
                        digits_.push_back(0);
                    }
                    digits_[i + 1] += digits_[i] / 10;
                    digits_[i] %= 10;
                }
            }
        }
        while (!digits_.empty() && !digits_.back()) {
            digits_.pop_back();
        }
        if (digits_.empty()) {
            positive_ = true;
        }
    }

    void reverse() {
        for (int i = 0; 2 * (size_t)i < digits_.size(); i++)
            std::swap(digits_[i], digits_[digits_.size() - i - 1]);
    }
public:
    BigInteger(): digits_(0), positive_(true){}


    BigInteger(int x) {
        positive_ = (x >= 0);
        x = abs(x);
        while(x > 0) {
            digits_.push_back(x % 10);
            x /= 10;
        }
    }

    BigInteger (const BigInteger &last) {
        digits_ = last.digits_;
        positive_  = last.positive_;
    }

    void setPositive(const bool& value) {
        positive_ = value;
    }

    void setDigitsBack(const int& value) {
        digits_.push_back(value);
    }

    bool isBigger(const BigInteger& b) const {
        if (digits_.size() != b.digits_.size()) {
            return digits_.size() < b.digits_.size();
        }
        for (int i = digits_.size() - 1; i >= 0; i--) {
            int d = b.digits_[i];
            if (digits_[i] != d)
                return digits_[i] < d;
        }
        return false;
    }

    explicit operator bool() const {
        return (!digits_.empty());
    }
    bool isPositive() const {
        return positive_;
    }

    BigInteger& operator=(const BigInteger& c) {
        digits_ = c.digits_;
        positive_ = c.positive_;
        return *this;
    }
    const BigInteger operator-() const {
        BigInteger res = *this;
        res.positive_ ^= 1;
        return res;
    }
    BigInteger& operator +=(const BigInteger& c) {
        if (positive_ == c.positive_) {
            if (digits_.size() < c.digits_.size()) {
                digits_.resize(c.digits_.size());
            }
            for (int i = 0; (size_t)i < c.digits_.size(); i++) {
                digits_[i] += c.digits_[i];
            }
        } else {
            BigInteger c1;
            c1=c;
            if (isBigger(c1)) {
                positive_ ^= 1;
                std ::swap(this->digits_, c1.digits_);
                std::swap(this->positive_, c1.positive_);
            }
            for (int i = 0; (size_t)i < c1.digits_.size(); i++) {
                digits_[i] -= c1.digits_[i];
            }
        }
        BuildCorrect();
        return *this;
    }
    BigInteger& operator ++() {
        return *this += 1;
    }
    const BigInteger operator ++ (int) {
        const BigInteger result = *this;
        ++*this;
        return result;
    }
    BigInteger& operator-=(const BigInteger c) {
        return (*this += (-c));
    }
    BigInteger& operator--() {
        return *this -= 1;
    }
    const BigInteger operator-- (int) {
        const BigInteger result = *this;
        --(*this);
        return result;
    }
    BigInteger& operator *=(BigInteger b) {
        positive_ = !(positive_ ^ b.isPositive());
        BigInteger current = *this;
        digits_.clear();
        digits_.resize(current.digits_.size() + b.digits_.size() - 1, 0);
        for (int i = 0; (size_t)i < current.digits_.size(); i++) {
            for (size_t j = 0; j < b.digits_.size(); ++j) {
                digits_[i + j] += current.digits_[i] * b.digits_[j];
            }
        }
        BuildCorrect();
        return *this;
    }
    BigInteger& operator /=(const BigInteger& b) {
        if (b.digits_.size() == 0) {
            return *this;
        }
        if (digits_.size() < b.digits_.size()) {
            digits_.clear();
            positive_ = true;
            return *this;
        }
        if (&b == this) {
            return *this = 1;
        }
        BigInteger current;
        current = *this;
        positive_ = !(current.positive_ ^ b.positive_);
        digits_.clear();
        for (int i = current.digits_.size() - b.digits_.size(); i >= 0; i--) {
            digits_.push_back(0);
            while (!current.isShiftedSubtractionPossible(b, i)) {
                current.shiftedSubtract(b, i);
                ++digits_.back();
            }
        }
        reverse();
        BuildCorrect();
        return *this;
    }
    BigInteger& operator%=(const BigInteger& b) {
        if (&b == this) {
            return *this = 0;
        }
        if (b.digits_.size() > digits_.size()) {
            return *this;
        }
        for (int i = digits_.size() - b.digits_.size(); i >= 0; i--) {
            while (!isShiftedSubtractionPossible(b, i)) {
                shiftedSubtract(b, i);
            }
        }
        positive_ = !(b.isPositive() ^ positive_);
        return *this;
    }
    const std::string toString() const {
        if (digits_.size() == 0) {
            return "0";
        }
        std::string resultString = ((!isPositive()) ? "-" : "");

        for(int i = digits_.size(); i > 0; i--) {
            resultString += (char) (digits_[i - 1] + '0');
        }
        return resultString;
    }
};


bool operator<(const BigInteger& b1, const BigInteger& b2) {
    if (b1.isPositive() ^ b2.isPositive()) {
        return b2.isPositive();
    }
    return b1.isPositive() ? b1.isBigger(b2) : b2.isBigger(b1);
}
bool operator>(const BigInteger& b1, const BigInteger& b2) {
    return b2 < b1;
}
bool operator==(const BigInteger& b1, const BigInteger& b2) {
    return !(b1 < b2 || b2 < b1);
}
bool operator!=(const BigInteger& b1, const BigInteger& b2) {
    return b1 < b2 || b2 < b1;
}
bool operator<=(const BigInteger& b1, const BigInteger& b2) {
    return !(b2 < b1);
}
bool operator>=(const BigInteger& b1, const BigInteger& b2) {
    return !(b1 < b2);
}


const BigInteger operator%(const BigInteger& b1, const BigInteger& b2) {
    return BigInteger(b1) %= b2;
}
const BigInteger operator*(const BigInteger& b1, const BigInteger& b2) {
    return BigInteger(b1) *= b2;
}
const BigInteger operator/(const BigInteger& b1, const BigInteger& b2) {
    return BigInteger(b1) /= b2;
}

const BigInteger operator+(const BigInteger& b1, const BigInteger& b2) {
    return BigInteger(b1) += b2 ;
}
const BigInteger operator-(const BigInteger& b1, const BigInteger& b2) {
    return BigInteger(b1) -= b2;
}


std::ostream& operator<<(std::ostream& out, const BigInteger& b) {
    return out << b.toString();
}

std::istream& operator>>(std::istream& in, BigInteger& b) {
    b = 0;
    std::string stringRes;
    in >> stringRes;

    b = BigInteger();

    int sign = 0;
    if (stringRes.empty() || stringRes == "0" || stringRes == "-0") {
        return in;
    }
    if (stringRes[0] == '-') {
        b.setPositive(false);
        sign = 1;
    }
    for (int i = stringRes.size() - 1; sign ? i > 0 : i >= 0; --i) {
        b.setDigitsBack(stringRes[i] - '0');
    }

    return in;
}

