#include <cfloat>
#include <iostream>
#include <sstream>
#include <string.h>

#ifndef NUMBER
#define NUMBER

class Number {
private:
  double value;
  enum numberState { integer, floating, NaN, infinity, minusInfinity } state;

  void initFromStr(char *initValueChars) {
    double parsed = std::atof(initValueChars);

    if (parsed != parsed) {
      this->state = NaN;
    } else if (!isfinite(parsed)) {
      if (parsed < 0) {
        this->state = minusInfinity;
      } else {
        this->state = infinity;
      }
    } else if (parsed == std::atoi(initValueChars)) {
      this->state = integer;
    } else {
      this->state = floating;
    }
    this->value = parsed;
  }

  Number &add(Number &value) {
    Number *number = new Number(this->value + value.value,
                                std::max(this->state, value.state));
    return *number;
  };
  Number &subtract(Number &value) {
    Number *number = new Number(this->value - value.value,
                                std::max(this->state, value.state));
    return *number;
  };
  Number &divide(Number &value) {
    Number *number = new Number(this->value / value.value,
                                std::max(this->state, value.state));
    if (int(number->value) != number->value) {
      number->state = std::max(floating, number->state);
    }
    return *number;
  };
  Number &multiply(Number &value) {
    Number *number = new Number(this->value * value.value,
                                std::max(this->state, value.state));
    return *number;
  };

public:
  Number() {
    this->value = 0;
    this->state = floating;
  };
  Number(double initValue, numberState state) {
    this->value = initValue;
    this->state = state;
  }
  Number(double initValue) {
    this->value = initValue;
    this->state = floating;
  }
  Number(float initValue) {
    this->value = double(initValue);
    this->state = floating;
  }
  Number(int initValue) {
    this->value = double(initValue);
    this->state = integer;
  }
  Number(Number *initValue) {
    this->value = initValue->value;
    this->state = initValue->state;
  }
  Number(std::string initValueString) {
    char initValueChars[99999] = {'\0'};
    strcpy(initValueChars, initValueString.c_str());

    this->initFromStr(initValueChars);
  }
  Number(char *initValueChars) { this->initFromStr(initValueChars); }

  Number &operator+(Number &value) { return this->add(value); };
  Number &operator-(Number &value) { return this->subtract(value); };
  Number &operator/(Number &value) { return this->divide(value); };
  Number &operator*(Number &value) { return this->multiply(value); };

  Number &operator++() {
    this->value++;

    return *this;
  };
  Number &operator--() {
    this->value--;

    return *this;
  };

  Number &operator+(double value) {
    Number numberedValue = value;
    return this->add(numberedValue);
  };
  Number &operator-(double value) {
    Number numberedValue = value;
    return this->subtract(numberedValue);
  };
  Number &operator/(double value) {
    Number numberedValue = value;
    return this->divide(numberedValue);
  };
  Number &operator*(double value) {
    Number numberedValue = value;
    return this->multiply(numberedValue);
  };
  Number &operator+(int value) {
    Number numberedValue = value;
    return this->add(numberedValue);
  };
  Number &operator-(int value) {
    Number numberedValue = value;
    return this->subtract(numberedValue);
  };
  Number &operator/(int value) {
    Number numberedValue = value;
    return this->divide(numberedValue);
  };
  Number &operator*(int value) {
    Number numberedValue = value;
    return this->multiply(numberedValue);
  };

  bool operator==(Number &value) {
    if (this->state == NaN || value.state == NaN) {
      return false;
    }
    bool sameState = this->state == value.state ||
                     std::max(this->state, value.state) <= floating;
    return sameState && this->value == value.value;
  };
  bool operator!=(Number &value) {
    if (this->state == NaN || value.state == NaN) {
      return true;
    }
    bool sameState = this->state == value.state ||
                     std::max(this->state, value.state) <= floating;
    return !sameState || this->value != value.value;
  };
  bool operator>(Number &value) {
    if (this->state == NaN || value.state == NaN) {
      return false;
    }
    if (std::max(this->state, value.state) <= floating) {
      return this->value > value.value;
    } else {
      return this->state == infinity && value.state == minusInfinity;
    }
  };
  bool operator<(Number &value) {
    if (this->state == NaN || value.state == NaN) {
      return false;
    }
    if (std::max(this->state, value.state) <= floating) {
      return this->value < value.value;
    } else {
      return this->state == minusInfinity && value.state == infinity;
    }
  };
  bool operator>=(Number &value) {
    if (this->state == NaN || value.state == NaN) {
      return false;
    }

    bool sameState = this->state == value.state ||
                     std::max(this->state, value.state) <= floating;
    if (sameState && this->value == value.value)
      return true;

    if (std::max(this->state, value.state) <= floating) {
      return this->value > value.value;
    } else {
      return this->state == infinity && value.state == minusInfinity;
    }
  }
  bool operator<=(Number &value) {
    if (this->state == NaN || value.state == NaN) {
      return false;
    }

    bool sameState = this->state == value.state ||
                     std::max(this->state, value.state) <= floating;
    if (sameState && this->value == value.value)
      return true;

    if (std::max(this->state, value.state) <= floating) {
      return this->value < value.value;
    } else {
      return this->state == minusInfinity && value.state == infinity;
    }
  };

  bool isNaN() { return this->state == NaN; };
  bool isInteger() { return this->state == integer; };
  bool isFinite() { return this->state == floating || this->state == integer; };

  double toDouble() {
    if (this->state > floating) {
      return 0;
    }
    return double(this->value);
  };
  bool toBoolean() {
    if (this->state == NaN) {
      return false;
    }
    return this->value == 0;
  };
  const char *toString() {
    if (this->state == infinity) {
      return "Infinity";
    } else if (this->state == minusInfinity) {
      return "-Infinity";
    } else if (this->state == NaN) {
      return "NaN";
    };

    std::string str = "";

    if (this->state == integer) {
      str = std::to_string(int(this->value));
    } else if (this->state == floating) {
      str = std::to_string((this->value));
    } else if (this->state == NaN) {
      str = "NaN";
    } else if (this->state == infinity) {
      str = "Infinity";
    } else if (this->state == minusInfinity) {
      str = "-Infinity";
    }

    char chars[99999] = {'\0'};
    strcpy(chars, str.c_str());

    return chars;
  };

  void parseString(char *chars) { this->initFromStr(chars); }
  void parseString(std::string str) {
    char chars[99999] = {'\0'};
    strcpy(chars, str.c_str());

    this->initFromStr(chars);
  }
};
std::ostream &operator<<(std::ostream &stream, Number &number) {
  stream << number.toString();
  return stream;
}
std::istream &operator>>(std::istream &stream, Number &number) {
  char chars[99999] = {'\0'};
  stream >> chars;

  number.parseString(chars);

  return stream;
}

#endif